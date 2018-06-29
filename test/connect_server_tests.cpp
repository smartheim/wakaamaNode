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
#include "lwm2m/c_connect.h"
#include "lwm2m/server.h"
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"
#include "wakaama_server_debug.h"
#include "lwm2m/network.h"
#include "../src/internal.h"
#include "../src/network/network_common.h"
#include "with_lwip/lwip_tap_helper.h"
#include "memory.h"

#include "lwm2mObjects/3311.h"

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

// Server thread Type (we need an own deleter for the unique ptr)
using deleted_unique_ptr = std::unique_ptr<std::thread,std::function<void(std::thread*)>>;

class ConnectServerTests : public testing::Test {
public:
    lwm2m_client_context_t client_context{};
    lwm2m_object_t * securityObj = nullptr;
    lwm2m_object_t * serverObj = nullptr;
    lwm2m_context_t * server_context = nullptr;
    std::string dm_received_json;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";
    int client_updated;
    int client_bound_sockets;
    volatile bool server_running = false;
 protected:
    virtual void TearDown() {
        if(server_context) {
            lwm2m_network_close(server_context);
            lwm2m_close (server_context);
            lwm2m_free(server_context);
            server_context = nullptr;
        }
        ASSERT_TRUE(client_context.context.userData);
        lwm2m_client_close(&client_context);

        std::for_each(memoryObserver.memAreas.begin (),memoryObserver.memAreas.end(),
                      [](MemoryObserver::MemAreas::value_type it){
            GTEST_FATAL_FAILURE_(it.second.c_str ());
        });
    }

    virtual void SetUp() {
        memoryObserver.reset();
        dm_received_json.clear ();

        client_bound_sockets =lwm2m_client_init(&client_context, client_name);
        ASSERT_GE(client_bound_sockets, 1);
        ASSERT_TRUE(client_context.context.userData);

        securityObj = &client_context.securityObject;
        ASSERT_EQ(securityObj->objID, 0);
        ASSERT_TRUE(securityObj);
        serverObj   = securityObj->next;
        ASSERT_TRUE(serverObj);
        ASSERT_EQ(serverObj->objID, 1);

        lwm2m_object_meta_information_t* metaP = (lwm2m_object_meta_information_t*)serverObj;

        for(unsigned i=0;i<metaP->ressources_len;++i)  {
            ASSERT_TRUE(metaP->ressources[i].struct_member_offset) << "Resource " << metaP->ressources[i].ressource_id;
        }

        server_context = nullptr;
    }

    void runTest(bool useDtls);
    void testServerResRequest(std::mutex& mutex);
    void testDeregister(std::mutex& mutex);
    void testUpdateRegister(std::mutex& mutex);
    int testHandshake(std::mutex& mutex, bool useDtls);
};

static void prv_monitor_callback(uint16_t clientID,
                                 lwm2m_uri_t * uriP,
                                 int status,
                                 lwm2m_media_type_t format,
                                 uint8_t * data,
                                 int dataLength,
                                 void * userData)
{
    (void)uriP; (void)format; (void)data; (void)dataLength;
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

void ConnectServerTests::testServerResRequest(std::mutex& mutex) {
    // Check server for detected objects/instances
    lwm2m_uri_t testURI{LWM2M_URI_FLAG_OBJECT_ID|LWM2M_URI_FLAG_INSTANCE_ID|LWM2M_URI_FLAG_RESOURCE_ID,
                3311,0,(uint16_t)KnownObjects::id3311::RESID::OnOff};
    lwm2m_dm_read (server_context,server_context->clientList->internalID,&testURI,
                   [](uint16_t clientID, lwm2m_uri_t * uriP, int status, lwm2m_media_type_t format,
                   uint8_t * data, int dataLength, void * userData){
        (void)clientID;
        (void)status;
        (void)format;
        if (uriP->instanceId == 0 && uriP->resourceId == KnownObjects::id3311::RESID::OnOff) {
            ((ConnectServerTests*) userData)->dm_received_json = std::string((char*)data, (size_t)dataLength);
        }
    },this);

    int steps=0;
    while (steps++ < 15) {
        struct timeval next_event = {0,500*1000};
        {
            std::lock_guard<std::mutex> guard(mutex);
            lwm2m_process (CTX(client_context),&next_event);
        }
        lwm2m_block_wait(CTX(client_context),next_event);
        if (!dm_received_json.empty ()) break;
    }

    ASSERT_STREQ ("{\"bn\":\"/3311/0/5850/\",\"e\":[{\"n\":\"5850\",\"bv\":true}]}", dm_received_json.c_str ());
}

void ConnectServerTests::testDeregister(std::mutex& mutex) {
    security_instance_t* instances = reinterpret_cast<security_instance_t*>(securityObj->instanceList);
    ASSERT_TRUE(lwm2m_unregister_server(CTX(client_context), instances->instanceId));

    // One network_step_blocking is necessary to send/receive the unregister request
    // All further steps make sure, the result does not change.
    int steps = 0;
    while (steps++ < 10) {
        int result;
        struct timeval next_event = {0,500*1000};
        {
            std::lock_guard<std::mutex> guard(mutex);
            result = lwm2m_process (CTX(client_context),&next_event);
        }
        lwm2m_block_wait(CTX(client_context),next_event);
        if (result == COAP_503_SERVICE_UNAVAILABLE) {
            if (CTX(client_context)->state == STATE_BOOTSTRAP_REQUIRED)
                break;
        } else {
            prv_print_error(result);
            print_state(CTX(client_context));
            ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);
        }
    }

    lwm2m_remove_unregistered_servers(CTX(client_context));
    steps = 0;
    int result;
    struct timeval next_event = {0,500*1000};
    {
        std::lock_guard<std::mutex> guard(mutex);
        result = lwm2m_process (CTX(client_context),&next_event);
    }

    ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);
    ASSERT_EQ(STATE_BOOTSTRAP_REQUIRED, CTX(client_context)->state);
}


void ConnectServerTests::testUpdateRegister(std::mutex& mutex) {
    security_instance_t* instances = reinterpret_cast<security_instance_t*>(securityObj->instanceList);
    ASSERT_EQ(STATE_REGISTERED, client_context.context.serverList->status);
    ASSERT_EQ (COAP_NO_ERROR, lwm2m_update_registration (CTX(client_context), instances->shortID, false));
    ASSERT_EQ(STATE_REG_UPDATE_NEEDED, client_context.context.serverList->status);

    // One network_step_blocking is necessary to send/receive the update request
    // All further steps make sure, the result does not change.
    int steps = 0;
    while (1) {
        int result;
        struct timeval next_event = {0,500*1000};
        {
            std::lock_guard<std::mutex> guard(mutex);
            result = lwm2m_process (CTX(client_context),&next_event);
        }
        lwm2m_block_wait(CTX(client_context),next_event);
        if (result != COAP_NO_ERROR) {
            prv_print_error(result);
            print_state(CTX(client_context));
            FAIL() << "Unexpected state";
            break;
        } else if (++steps>3) {
            break;
        }
    }

    ASSERT_EQ(STATE_REGISTERED, client_context.context.serverList->status);
    ASSERT_EQ(STATE_READY, CTX(client_context)->state);
}

int ConnectServerTests::testHandshake(std::mutex& mutex, bool useDtls) {
    // Client and server threads are doing network_step_blocking() in sequence for easier
    // step debugging if necessary
    int steps = 0;
    int result;
    while (steps++ < 15) {
        struct timeval next_event = {0,500*1000};
        {
            std::lock_guard<std::mutex> guard(mutex);
            result = lwm2m_process (CTX(client_context),&next_event);
        }
        lwm2m_block_wait(CTX(client_context),next_event);
        if (result == COAP_NO_ERROR) {
            if (useDtls) {
                network_t* network = static_cast<network_t*>(CTX(client_context)->userData);
                // Not in handshake and state is READY -> exit the loop
                if (!network->inHandshake && CTX(client_context)->state == STATE_READY)
                        break;
            } else if (CTX(client_context)->state == STATE_READY)
                    break;
        } else {
            prv_print_error(result);
            print_state(CTX(client_context));
        }
    }
    return result;
}

void ConnectServerTests::runTest(bool useDtls) {
    const char PSK[] = "psk";
    const char PUBLICID[] = "publicid";

    std::mutex mutex;

    int server_bound_sockets;

    //// init server thread ////
    server_context = lwm2m_init(nullptr);
    server_context->state = STATE_READY;
    ASSERT_TRUE(server_context);

    // Install a monitoring callback for the server lwm2m context.
    // We check for the COAP_201_CREATED and COAP_202_DELETED events
    lwm2m_set_monitoring_callback(server_context, prv_monitor_callback, this);
    server_bound_sockets = lwm2m_network_init(server_context,
                                              useDtls ? LWM2M_DEFAULT_SECURE_SERVER_PORT : LWM2M_DEFAULT_SERVER_PORT);
    ASSERT_LE(1, server_bound_sockets);
    ASSERT_TRUE(server_context->userData!=NULL);

    //// If DTLS: Set server public ID and preshared key
    if (useDtls)
        lwm2m_server_dtls_psk(server_context,PUBLICID,PSK,sizeof(PSK));

    client_updated = 0;
    connected_client_name = nullptr;
    server_running = true;
    #ifdef TAP_SERVER_ADDR //lwip
    // listen on the second lwip network interface for the server
    server_bound_sockets = 1;
    lwm2m_network_force_interface(server_context, lwip_network_get_interface(server_bound_sockets));
    #endif

    // Start server thread with custom unique ptr deleter that joins the thread again
    deleted_unique_ptr serverThread = deleted_unique_ptr( new std::thread([this,&mutex]() {
        while (server_running) {
            struct timeval next_event = {0,50*1000};
            {
                std::lock_guard<std::mutex> guard(mutex);
                lwm2m_process (server_context,&next_event);
            }
            lwm2m_block_wait(server_context,next_event);
        }
        int last10 = 10;
        while (last10--) {
            struct timeval next_event = {0,5000};
            {
                std::lock_guard<std::mutex> guard(mutex);
                lwm2m_process (server_context,&next_event);
            }
            lwm2m_block_wait(server_context,next_event);
        }
    }),[this](std::thread* t){
        server_running=false;
        t->join();
    });

    // Client: Add a test object with some resources
    KnownObjects::id3311::object testO;
    KnownObjects::id3311::instance testI;
    testO.addInstance (CTX(client_context), &testI);
    testO.registerObject(CTX(client_context), false);
    testI.OnOff = true;

    //// client: add server and register ////
    ASSERT_TRUE(lwm2m_add_server(CTX(client_context), 123,
                                 useDtls ? LWM2M_SERVER_ADDR_SEC : LWM2M_SERVER_ADDR, 100, false));

    //// client: set dtls psk ////
    if (useDtls) {
        lwm2m_use_dtls_psk(CTX(client_context), 123,PUBLICID,PSK,sizeof(PSK));
    }

    #ifdef TAP_SERVER_ADDR //lwip
    client_bound_sockets = 0; // use the first lwip network interface for the client
    lwm2m_network_force_interface(CTX(client_context), lwip_network_get_interface(client_bound_sockets));
    #endif

    int result = testHandshake(mutex, useDtls);

    // If everything went well, we have passed the DTLS handshake and coap/lwm2m handshake
    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_READY, CTX(client_context)->state);
    ASSERT_STREQ(connected_client_name, client_name);

    testServerResRequest(mutex);
    testUpdateRegister (mutex);
    testDeregister(mutex);

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
