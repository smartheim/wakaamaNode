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
#include "lwm2m_connect.h"
#include "lwm2m_objects.h"
#include "client_debug.h"
#include "wakaama_server_debug.h"
#include "network.h"
#include "internal.h"
#include "network_helper.h"
#include "memory.h"

#include <stdint.h>
#include <stdio.h>

#include <thread>
#include <memory>

extern "C" {
#include "internals.h"
}

#define LWM2M_SERVER_ADDR "coap://127.0.0.1"

class AddRemoveServerTests : public testing::Test {
public:
    lwm2m_object_t * securityObj=nullptr;
    lwm2m_object_t * serverObj=nullptr;
    lwm2m_context_t * server_context=nullptr;
    int client_bound_sockets;
    int client_updated;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";

 protected:
    virtual void TearDown() {
        lwm2m_client_close();

        if (server_context)
        {
            lwm2m_close(server_context);
            server_context = nullptr;
        }


        network_close();

        ASSERT_STREQ("", memoryObserver.printIfNotEmpty().c_str());
    }

    virtual void SetUp() {
        memoryObserver.reset();
        // Necessary for lwip to initialize the memory module
        ASSERT_TRUE(network_init());

        ASSERT_TRUE(lwm2m_client_init(client_name)) << "Failed to initialize wakaama\r\n";

        securityObj = lwm2m_client_get_context()->objectList;
        ASSERT_EQ(securityObj->objID, 0);
        ASSERT_TRUE(securityObj);
        serverObj   = securityObj->next;
        ASSERT_TRUE(serverObj);
        ASSERT_EQ(serverObj->objID, 1);

        server_context = nullptr;

        ASSERT_GE(lwm2m_network_init(lwm2m_client_get_context(), "12345"), 1);
    }
};


TEST_F(AddRemoveServerTests, AddServer) {
    ASSERT_TRUE(lwm2m_add_server(123, LWM2M_SERVER_ADDR, 100, false));

    ASSERT_EQ(lwm2m_client_get_context()->state, STATE_INITIAL);

    security_instance_t* secInstance = (security_instance_t*)securityObj->instanceList;
    server_instance_t* serverInstance = (server_instance_t*)serverObj->instanceList;

    ASSERT_EQ(123, secInstance->shortID);
    ASSERT_EQ(123, serverInstance->shortServerId);

    char uriBuffer[100];
    ASSERT_TRUE(lwm2m_get_server_uri(secInstance->instanceId,uriBuffer, sizeof(uriBuffer)));
    ASSERT_STREQ(uriBuffer, LWM2M_SERVER_ADDR);

    time_t timeout;
    uint8_t result = lwm2m_step(lwm2m_client_get_context(), &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_REGISTERING, lwm2m_client_get_context()->state);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(lwm2m_client_get_context()->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);
}

TEST_F(AddRemoveServerTests, RemoveServer) {
    time_t timeout;

    ASSERT_TRUE(lwm2m_add_server(123, LWM2M_SERVER_ADDR, 100, false));

    security_instance_t* secInstance = (security_instance_t*)securityObj->instanceList;

    // Add server to serverlist
    uint8_t result = lwm2m_step(lwm2m_client_get_context(), &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(lwm2m_client_get_context()->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);

    // Now assume registering worked
    serverListEntry->status = STATE_REGISTERED;
    serverListEntry->location = (char*)lwm2m_malloc(1);

    // Unregister now
    ASSERT_TRUE(lwm2m_unregister_server(secInstance->instanceId));
    ASSERT_EQ(STATE_DEREG_PENDING, serverListEntry->status);
    serverListEntry->status = STATE_DEREGISTERED;

    lwm2m_remove_unregistered_servers();

    ASSERT_FALSE(securityObj->instanceList);
    ASSERT_FALSE(serverObj->instanceList);
    ASSERT_TRUE(lwm2m_client_get_context()->serverList);

    ASSERT_EQ(lwm2m_client_get_context()->state, STATE_INITIAL);
    result = lwm2m_step(lwm2m_client_get_context(), &timeout);
    ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);

    ASSERT_EQ(lwm2m_client_get_context()->state, STATE_BOOTSTRAP_REQUIRED);
    ASSERT_FALSE(lwm2m_client_get_context()->serverList);
}