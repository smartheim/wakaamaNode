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

#include <stdint.h>
#include <stdio.h>

#include <thread>
#include <memory>

extern "C" {
#include "internals.h"
}

#define LWM2M_SERVER_ADDR "coap://127.0.0.1"

static lwm2m_object_t * prv_findObject(lwm2m_context_t * contextP,
                                       uint16_t Id)
{
    int i;

    for (i = 0 ; i < contextP->numObject ; i++)
    {
        if (contextP->objectList[i]->objID == Id)
        {
            return contextP->objectList[i];
        }
    }

    return NULL;
}

class AddRemoveServerTests : public testing::Test {
public:
    lwm2m_context_t * client_context;
    lwm2m_object_t * securityObj;
    lwm2m_object_t * serverObj;
    lwm2m_context_t * server_context;
    int client_bound_sockets;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";
    int client_updated;

 protected:
    virtual void TearDown() {
        lwm2m_client_close();

        if (server_context)
        {
            lwm2m_close(server_context);
            server_context = nullptr;
        }

        lwm2m_network_close(client_context);
    }

    virtual void SetUp() {
        client_context = lwm2m_client_init(client_name);
        ASSERT_TRUE(client_context) << "Failed to initialize wakaama\r\n";

        securityObj = prv_findObject(client_context, 0);
        serverObj   = prv_findObject(client_context, 1);

        ASSERT_TRUE(securityObj);
        ASSERT_TRUE(serverObj);

        server_context = nullptr;

        lwm2m_network_init(client_context, "12345");
    }
};


TEST_F(AddRemoveServerTests, AddServer) {
    uint8_t s = lwm2m_add_server(123, LWM2M_SERVER_ADDR, 100, false, NULL, NULL, 0);
    ASSERT_EQ(s, COAP_205_CONTENT);

    ASSERT_EQ(client_context->state, STATE_INITIAL);

    security_instance_t* secInstance = (security_instance_t*)securityObj->instanceList;
    server_instance_t* serverInstance = (server_instance_t*)serverObj->instanceList;

    ASSERT_EQ(123, secInstance->shortID);
    ASSERT_EQ(123, serverInstance->shortServerId);

    char uriBuffer[100];
    ASSERT_TRUE(lwm2m_get_server_uri(secInstance->instanceId,uriBuffer, sizeof(uriBuffer)));
    ASSERT_STREQ(uriBuffer, LWM2M_SERVER_ADDR);

    time_t timeout;
    uint8_t result = lwm2m_step(client_context, &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_REGISTERING, client_context->state);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(client_context->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);
}

TEST_F(AddRemoveServerTests, RemoveServer) {
    uint8_t result;
    time_t timeout;

    uint8_t s = lwm2m_add_server(123, LWM2M_SERVER_ADDR, 100, false, NULL, NULL, 0);
    ASSERT_EQ(s, COAP_205_CONTENT);

    security_instance_t* secInstance = (security_instance_t*)securityObj->instanceList;

    // Add server to serverlist
    result = lwm2m_step(client_context, &timeout);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(client_context->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);

    // Now assume registering worked
    serverListEntry->status = STATE_REGISTERED;
    serverListEntry->location = (char*)lwm2m_malloc(1);

    // Unregister now
    lwm2m_unregister_server(secInstance->instanceId);
    ASSERT_EQ(serverListEntry->status, STATE_DEREG_PENDING);
    serverListEntry->status = STATE_DEREGISTERED;

    lwm2m_remove_unregistered_servers();

    ASSERT_FALSE(securityObj->instanceList);
    ASSERT_FALSE(serverObj->instanceList);
    ASSERT_TRUE(client_context->serverList);

    ASSERT_EQ(client_context->state, STATE_INITIAL);
    result = lwm2m_step(client_context, &timeout);

    ASSERT_EQ(client_context->state, STATE_BOOTSTRAP_REQUIRED);
    ASSERT_FALSE(client_context->serverList);
}
