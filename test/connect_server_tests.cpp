/*******************************************************************************
 * Copyright (c) 2016  MSc. David Graeff <david.graeff@web.de>
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
#include "wakaama_simple_client.h"
#include "wakaama_object_utils.h"
#include "wakaama_client_debug.h"
#include "wakaama_server_debug.h"
#include "wakaama_network.h"
#include "wakaama_client_internal.h"
#include "network_helper.h"

#ifdef TAP_SERVER_ADDR
#define LWM2M_SERVER_ADDR "coap://" TAP_SERVER_ADDR
#else
#define LWM2M_SERVER_ADDR "coap://127.0.0.1"
#endif

#include <stdint.h>
#include <stdio.h>

#include <thread>
#include <memory>

extern "C" {
#include "internals.h"
}


class ConnectServerTests : public testing::Test {
public:
    lwm2m_context_t * client_context;
    lwm2m_object_t * securityObj;
    lwm2m_object_t * serverObj;
    std::unique_ptr<std::thread> serverThread;
    volatile bool server_running = false;

    lwm2m_context_t * server_context;
    int client_bound_sockets;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";
    int client_updated;

 protected:
    virtual void TearDown() {
        lwm2m_network_close(client_context);
        lwm2m_client_close();

        server_running = false;
        if (serverThread)
            serverThread->join();

        if (server_context)
        {
            lwm2m_network_close(server_context);
            lwm2m_close(server_context);
            server_context = nullptr;
        }

        network_close();
    }

    virtual void SetUp() {
        network_init();
        client_context = lwm2m_client_init(client_name);
        ASSERT_TRUE(client_context) << "Failed to initialize wakaama\r\n";

        securityObj = client_context->objectList;
        ASSERT_EQ(securityObj->objID, 0);
        ASSERT_TRUE(securityObj);
        serverObj   = securityObj->next;
        ASSERT_TRUE(serverObj);
        ASSERT_EQ(serverObj->objID, 1);

        // The meta data pointer is not an official member of the lwm2m_object_t struct.
        lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)serverObj)->meta;

        for(unsigned i=0;i<metaP->ressources_len;++i)
        {
            lwm2m_object_res_item_t* resP = &(metaP->ressources[i]);
            if ((resP->type_and_access & O_RES_E))
                continue;
            ASSERT_TRUE(resP->struct_member_offset);
        }

        client_bound_sockets = lwm2m_network_init(client_context, NULL);
        ASSERT_GE(client_bound_sockets, 1);

        server_context = nullptr;
    }
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

TEST_F(ConnectServerTests, ConnectServer) {
    int server_bound_sockets;

    //// init server thread ////
    server_context = lwm2m_init(NULL);
    server_context->state = STATE_READY;
    ASSERT_TRUE(server_context);

    lwm2m_set_monitoring_callback(server_context, prv_monitor_callback, this);
    server_bound_sockets = lwm2m_network_init(server_context, LWM2M_DEFAULT_SERVER_PORT);
    ASSERT_GE(server_bound_sockets, 1);

    client_updated = 0;
    connected_client_name = nullptr;
    server_running = true;
    #ifdef TAP_SERVER_ADDR //lwip
    // listen on the second lwip network interface for the server
    server_bound_sockets = 1;
    lwm2m_network_force_interface(server_context, network_get_interface(server_bound_sockets));
    #endif
    serverThread = std::unique_ptr<std::thread>(new std::thread([this,server_bound_sockets]() {
        while (server_running) {
            network_step_blocking(server_context,server_bound_sockets);
        }
    }));

    //// client: add server and register ////
    uint8_t s = lwm2m_add_server(123,LWM2M_SERVER_ADDR, 100, false, NULL, NULL, 0);
    ASSERT_EQ(s, COAP_205_CONTENT);

    uint8_t steps = 0;
    uint8_t result;

    #ifdef TAP_SERVER_ADDR //lwip
    client_bound_sockets = 0; // use the first lwip network interface for the server
    lwm2m_network_force_interface(client_context, network_get_interface(client_bound_sockets));
    #endif

    while (steps++ < 10) {
        result = network_step_blocking(client_context,client_bound_sockets);
        if (result == COAP_NO_ERROR) {
            if (client_context->state == STATE_READY)
                break;
        } else {
            #ifdef WITH_LOGS
            print_status(result);
            print_state(client_context);
            #endif
        }
    }

    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_READY, client_context->state);
    ASSERT_STREQ(connected_client_name, client_name);

    //// client: deregister from server ////
    security_instance_t* instances = (security_instance_t*)securityObj->instanceList;
    lwm2m_unregister_server(instances->instanceId);

    steps = 0;
    while (steps++ < 10) {
        result = network_step_blocking(client_context,client_bound_sockets);
        lwm2m_remove_unregistered_servers();
        if (result == COAP_503_SERVICE_UNAVAILABLE) {
            if (client_context->state == STATE_BOOTSTRAP_REQUIRED)
                break;
        } else {
            print_status(result);
            print_state(client_context);
        }
    }

    ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);
    ASSERT_EQ(STATE_BOOTSTRAP_REQUIRED, client_context->state);
    ASSERT_EQ(nullptr, connected_client_name);
}
