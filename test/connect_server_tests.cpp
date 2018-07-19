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
#include "test_debug.h"
#include "server.h"
#include "lwm2m/network.h"
#include "../src/network/network_common.h"
#include "with_lwip/lwip_tap_helper.h"
#include "memory.h"

#include "lwm2mObjects/3311.h"

#ifdef TAP_SERVER_ADDR
#define LWM2M_SERVER_ADDR "coap://" TAP_SERVER_ADDR
#define LWM2M_SERVER_ADDR_SEC "coaps://" TAP_SERVER_ADDR
#define STEP_FACTOR 10
#else
#define LWM2M_SERVER_ADDR "coap://127.0.0.1"
#define LWM2M_SERVER_ADDR_SEC "coaps://127.0.0.1"
#define STEP_FACTOR 1
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
    lwm2m_client_context_t client_context{};
    lwm2m_object_t * securityObj = nullptr;
    lwm2m_object_t * serverObj = nullptr;
    std::string dm_received_json;
    std::unique_ptr<Lwm2mServer> server;

    // Client name and connected client name
    const char* client_name = "testClient";
    int client_bound_sockets;
 protected:
    virtual void TearDown() {
        if (server)
            server->release ();
        ASSERT_TRUE(client_context.context.userData);
        lwm2m_client_close(&client_context);

        lwip_network_close();

        MEMEVAL(FAIL());
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

        // Necessary for lwip to initialize the memory module
        ASSERT_TRUE(lwip_network_init());
    }

    void runTest(bool useDtls);
    void testServerResRequest(std::mutex& mutex);
    void testDeregister(std::mutex& mutex);
    void testUpdateRegister(std::mutex& mutex);
    void testHandshake(std::mutex& mutex, bool useDtls);
};

void ConnectServerTests::testServerResRequest(std::mutex& mutex) {
    // Check server for detected objects/instances
    lwm2m_uri_t testURI{LWM2M_URI_FLAG_OBJECT_ID|LWM2M_URI_FLAG_INSTANCE_ID|LWM2M_URI_FLAG_RESOURCE_ID,
                3311,0,(uint16_t)KnownObjects::id3311::RESID::OnOff};
    lwm2m_dm_read (server->server_context,server->server_context->clientList->internalID,&testURI,
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
    while (steps++ < 15*STEP_FACTOR) {
        {
            std::lock_guard<std::mutex> guard(mutex);
            lwm2m_process (CTX(client_context));
        }
        lwm2m_block_wait(CTX(client_context),500);
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
    while (steps++ < 10*STEP_FACTOR) {
        {
            std::lock_guard<std::mutex> guard(mutex);
            lwm2m_process (CTX(client_context));
        }
        lwm2m_block_wait(CTX(client_context),500);
        if (lwm2m_state(CTX(client_context)) == STATE_BOOTSTRAP_REQUIRED) {
            break;
        } else {
            print_state(CTX(client_context));
        }
    }

    lwm2m_remove_unregistered_servers(CTX(client_context));
    steps = 0;
    {
        std::lock_guard<std::mutex> guard(mutex);
        lwm2m_process (CTX(client_context));
    }

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
        {
            std::lock_guard<std::mutex> guard(mutex);
            lwm2m_process (CTX(client_context));
        }
        lwm2m_block_wait(CTX(client_context),500);
        if (CTX(client_context)->lastStepError != COAP_NO_ERROR) {
            prv_print_error(CTX(client_context));
            print_state(CTX(client_context));
            FAIL() << "Unexpected state";
            break;
        } else if (++steps>3*STEP_FACTOR) {
            break;
        }
    }

    ASSERT_EQ(STATE_REGISTERED, client_context.context.serverList->status);
    ASSERT_EQ(STATE_READY, CTX(client_context)->state);
}

void ConnectServerTests::testHandshake(std::mutex& mutex, bool useDtls) {
    // Client and server threads are doing network_step_blocking() in sequence for easier
    // step debugging if necessary
    int steps = 0;
    while (steps++ < 20*STEP_FACTOR) {
        {
            std::lock_guard<std::mutex> guard(mutex);
            lwm2m_process (CTX(client_context));
        }
        lwm2m_block_wait(CTX(client_context), 500);
        if (CTX(client_context)->lastStepError == COAP_NO_ERROR) {
            if (useDtls) {
                network_t* network = static_cast<network_t*>(CTX(client_context)->userData);
                // Not in handshake and state is READY -> exit the loop
                if (network->handshakeState==DTLS_NO_HANDSHAKE_IN_PROGRESS &&
                        CTX(client_context)->state == STATE_READY)
                        break;
            } else if (CTX(client_context)->state == STATE_READY)
                    break;
        } else {
            prv_print_error(CTX(client_context));
            print_state(CTX(client_context));
        }
    }
    ASSERT_EQ(COAP_NO_ERROR, CTX(client_context)->lastStepError);
}

void ConnectServerTests::runTest(bool useDtls) {
    std::mutex mutex;

    server = std::unique_ptr<Lwm2mServer>(new Lwm2mServer(&mutex));
    server->init (useDtls);

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
        lwm2m_use_dtls_psk(CTX(client_context), 123,Lwm2mServer::PUBLICID,Lwm2mServer::PSK,
                           Lwm2mServer::PSK_LEN);
    }

    testHandshake(mutex, useDtls);

    // If everything went well, we have passed the DTLS handshake and coap/lwm2m handshake
    ASSERT_EQ(STATE_READY, CTX(client_context)->state);
    ASSERT_STREQ(server->getConnectClientName ().c_str (), client_name);

    testServerResRequest(mutex);
    testUpdateRegister (mutex);
    testDeregister(mutex);

    server->release ();
    ASSERT_FALSE(server->getConnectClientName().size());
}

TEST_F(ConnectServerTests, ConnectServer) {
    runTest(false);
}

#if defined(LWM2M_WITH_DTLS) && defined(LWM2M_SERVER_MODE)
TEST_F(ConnectServerTests, ConnectServerDtlsPSK) {
    runTest(true);
}
#endif
