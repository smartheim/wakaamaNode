/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */

#include <gtest/gtest.h>
#include "lwm2m/connect.h"
#include "lwm2m/server.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"
#include "wakaama_server_debug.h"
#include "lwm2m/network.h"
#include "../src/internal.h"
#include "../src/network/network_common.h"
#include "network_helper.h"
#include "memory.h"

#ifdef TAP_SERVER_ADDR
#define LWM2M_SERVER_ADDR "coap://" TAP_SERVER_ADDR
#define LWM2M_SERVER_ADDR_SEC "coaps://" TAP_SERVER_ADDR
#else
#define LWM2M_SERVER_ADDR "coap://127.0.0.1"
#define LWM2M_SERVER_ADDR_SEC "coaps://127.0.0.1"
#endif

#include <stdint.h>
#include <stdio.h>

#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <algorithm>

extern "C" {
#include "internals.h"
}


class ConnectServerTests : public testing::Test {
public:
    lwm2m_context_t * client_context = nullptr;
    lwm2m_object_t * securityObj = nullptr;
    lwm2m_object_t * serverObj = nullptr;
    volatile bool server_running = false;

    lwm2m_context_t * server_context;
    int client_bound_sockets;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";
    int client_updated;

 protected:
    virtual void TearDown() {
        if(server_context) {
            lwm2m_network_close(server_context);
            lwm2m_close (server_context);
            server_context = nullptr;
        }
        if (!client_context) return;
        ASSERT_TRUE(client_context->userData);
        lwm2m_client_close();
        test_network_close();

        std::for_each(memoryObserver.memAreas.begin (),memoryObserver.memAreas.end(),
                      [](MemoryObserver::MemAreas::value_type it){
            GTEST_FATAL_FAILURE_(it.second.c_str ());
        });
    }

    virtual void SetUp() {
        memoryObserver.reset();

        ASSERT_TRUE(test_network_init());
        client_context = lwm2m_client_init(client_name);
        ASSERT_TRUE(client_context) << "Failed to initialize wakaama\r\n";

        securityObj = client_context->objectList;
        ASSERT_EQ(securityObj->objID, 0);
        ASSERT_TRUE(securityObj);
        serverObj   = securityObj->next;
        ASSERT_TRUE(serverObj);
        ASSERT_EQ(serverObj->objID, 1);

        lwm2m_object_meta_information_t* metaP = (lwm2m_object_meta_information_t*)serverObj;

        for(unsigned i=0;i<metaP->ressources_len;++i)
        {
            lwm2m_object_res_item_t* resP = &(metaP->ressources[i]);
            if (resP->access & O_RES_E)
                continue;
            ASSERT_TRUE(resP->struct_member_offset);
        }

        server_context = nullptr;
    }

    void runTest(bool useDtls);
};

static void prv_monitor_callback(uint16_t clientID,
                                 lwm2m_uri_t * uriP,
                                 int status,
                                 lwm2m_media_type_t format,
                                 uint8_t * data,
                                 int dataLength,
                                 void * userData)
{
    ConnectServerTests* t = (ConnectServerTests*) userData;
    lwm2m_context_t * lwm2mH = t->server_context;
    lwm2m_client_t * targetP;

    switch (status)
    {
    case COAP_201_CREATED:
        targetP = (lwm2m_client_t *)lwm2m_list_find((lwm2m_list_t *)lwm2mH->clientList, clientID);
        t->connected_client_name = targetP->name;
        //prv_dump_client(targetP);
        break;

    case COAP_202_DELETED:
        t->connected_client_name = nullptr;
        break;

    case COAP_204_CHANGED:
        ++t->client_updated;
        //prv_dump_client(targetP);
        break;

    default:
        break;
    }
}

void ConnectServerTests::runTest(bool useDtls) {
    const char PSK[] = "psk";
    const char PUBLICID[] = "publicid";

    std::mutex mutex;

    using deleted_unique_ptr = std::unique_ptr<std::thread,std::function<void(std::thread*)>>;
    deleted_unique_ptr serverThread;

    client_bound_sockets = lwm2m_network_init(client_context, nullptr, useDtls);
    ASSERT_GE(client_bound_sockets, 1);
    ASSERT_TRUE(client_context->userData);

    int server_bound_sockets;

    //// init server thread ////
    server_context = lwm2m_init(nullptr);
    server_context->state = STATE_READY;
    ASSERT_TRUE(server_context);

    // Install a monitoring callback for the server lwm2m context.
    // We check for the COAP_201_CREATED and COAP_202_DELETED events
    lwm2m_set_monitoring_callback(server_context, prv_monitor_callback, this);
    server_bound_sockets = lwm2m_network_init(server_context,
                                              useDtls ? LWM2M_DEFAULT_SECURE_SERVER_PORT : LWM2M_DEFAULT_SERVER_PORT,
                                              useDtls);
    ASSERT_LE(1, server_bound_sockets);
    ASSERT_TRUE(server_context->userData);

    //// If DTLS: Set server public ID and preshared key
    if (useDtls)
        lwm2m_server_dtls_psk(server_context,PUBLICID,PSK,sizeof(PSK));

    client_updated = 0;
    connected_client_name = nullptr;
    server_running = true;
    #ifdef TAP_SERVER_ADDR //lwip
    // listen on the second lwip network interface for the server
    server_bound_sockets = 1;
    lwm2m_network_force_interface(server_context, network_get_interface(server_bound_sockets));
    #endif

    // Start server thread with custom unique ptr deleter that joins the thread again
    serverThread =deleted_unique_ptr( new std::thread([this,&mutex,server_bound_sockets]() {
        while (server_running) {
            usleep(1000);
            std::lock_guard<std::mutex> guard(mutex);
            network_step_blocking(server_context,server_bound_sockets);
        }
        int last10 = 10;
        while (last10--) {
            usleep(1000);
            std::lock_guard<std::mutex> guard(mutex);
            network_step_blocking(server_context,server_bound_sockets);
        }
    }),[this](std::thread* t){
        server_running=false;
        t->join();
    });

    //// client: add server and register ////
    ASSERT_TRUE(lwm2m_add_server(123, useDtls ? LWM2M_SERVER_ADDR_SEC : LWM2M_SERVER_ADDR, 100, false));

    //// client: set dtls psk ////
    if (useDtls) {
        lwm2m_security_use_preshared(123,PUBLICID,PSK,sizeof(PSK));
    }

    uint8_t steps = 0;
    uint8_t result;

    #ifdef TAP_SERVER_ADDR //lwip
    client_bound_sockets = 0; // use the first lwip network interface for the client
    lwm2m_network_force_interface(client_context, network_get_interface(client_bound_sockets));
    #endif

    // Client and server threads are doing network_step_blocking() in sequence for easier
    // step debugging if necessary
    while (steps++ < 15) {
        usleep(1000);
        std::lock_guard<std::mutex> guard(mutex);
        result = network_step_blocking(client_context,client_bound_sockets);
        if (result == COAP_NO_ERROR) {
            if (useDtls) {
                network_t* network = (network_t*)client_context->userData;
                connection_t* c = network->connection_list;
                bool inHandshake = false;
                while (c) {
                    inHandshake |= c->dtls && c->ssl.state!=MBEDTLS_SSL_HANDSHAKE_OVER;
                    c = c->next;
                }
                if (!inHandshake)
                    if(client_context->state == STATE_READY)
                        break;
            } else if (client_context->state == STATE_READY)
                    break;
        } else {
            prv_print_error(result);
            // print_status(result);
            print_state(client_context);
        }
    }

    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_READY, client_context->state);
    ASSERT_STREQ(connected_client_name, client_name);

    //// client: deregister from server ////
    security_instance_t* instances = (security_instance_t*)securityObj->instanceList;
    ASSERT_TRUE(lwm2m_unregister_server(instances->instanceId));

    // One network_step_blocking is necessary to send/receive the unregister request
    // All further steps make sure, the result does not change.
    steps = 0;
    while (steps++ < 10) {
        usleep(1000);
        std::lock_guard<std::mutex> guard(mutex);
        result = network_step_blocking(client_context,client_bound_sockets);
        if (result == COAP_503_SERVICE_UNAVAILABLE) {
            if (client_context->state == STATE_BOOTSTRAP_REQUIRED)
                break;
        } else {
            prv_print_error(result);
            print_state(client_context);
            ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);
        }
        usleep(1000*20);
    }

    lwm2m_remove_unregistered_servers();
    result = network_step_blocking(client_context,client_bound_sockets);

    ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);
    ASSERT_EQ(STATE_BOOTSTRAP_REQUIRED, client_context->state);

    if (serverThread){
       serverThread.reset();
    }
    ASSERT_EQ(nullptr, connected_client_name);
}

TEST_F(ConnectServerTests, ConnectServer) {
    runTest(false);
}

#if defined(LWM2M_WITH_DTLS) && defined(LWM2M_SERVER_MODE)
TEST_F(ConnectServerTests, ConnectServerDtlsPSK) {
    runTest(true);
}
#endif
