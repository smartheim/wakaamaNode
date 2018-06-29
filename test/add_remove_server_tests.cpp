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
#include "lwm2m/objects.h"
#include "lwm2m/debug.h"
#include "wakaama_server_debug.h"
#include "lwm2m/network.h"
#include "../src/internal.h"
#include "with_lwip/lwip_tap_helper.h"
#include "memory.h"

#include <stdint.h>
#include <stdio.h>

#include <thread>
#include <memory>
#include <algorithm>

extern "C" {
#include "internals.h"
}

#define LWM2M_SERVER_ADDR "coap://127.0.0.1:12345"

class AddRemoveServerTests : public testing::Test {
public:
    lwm2m_context_t * server_context=nullptr;
    lwm2m_client_context_t client_context{};
    int client_bound_sockets;
    int client_updated;

    // Client name and connected client name
    char* connected_client_name = nullptr;
    const char* client_name = "testClient";

 protected:
    virtual void TearDown() {
        lwm2m_client_close(&client_context);

        if (server_context)
        {
            lwm2m_close(server_context);
            server_context = nullptr;
        }

        lwip_network_close();

        std::for_each(memoryObserver.memAreas.begin (),memoryObserver.memAreas.end(),
                      [](MemoryObserver::MemAreas::value_type it){
            FAIL() << "Entry @ " +std::to_string(it.first) + "\n" + it.second;
        });
    }

    virtual void SetUp() {
        memoryObserver.reset();
        // Necessary for lwip to initialize the memory module
        ASSERT_TRUE(lwip_network_init());

        ASSERT_GE(lwm2m_client_init(&client_context,client_name), 1);

        ASSERT_EQ(client_context.securityObject.objID, 0);
        ASSERT_EQ(client_context.serverObject.obj.objID, 1);
        ASSERT_EQ(client_context.deviceObject.obj.objID, 3);

        server_context = nullptr;
    }
};


TEST_F(AddRemoveServerTests, AddServer) {
    ASSERT_TRUE(lwm2m_add_server(CTX(client_context), 123, LWM2M_SERVER_ADDR, 100, false));

    ASSERT_EQ(CTX(client_context)->state, STATE_INITIAL);

    security_instance_t* secInstance = (security_instance_t*)client_context.securityObject.instanceList;
    server_instance_t* serverInstance = (server_instance_t*)client_context.serverObject.obj.instanceList;

    ASSERT_EQ(123, secInstance->shortID);
    ASSERT_EQ(123, serverInstance->shortServerId);

    ASSERT_STREQ(lwm2m_get_server_uri(CTX(client_context), 123), LWM2M_SERVER_ADDR);

    time_t timeout;
    int result = lwm2m_step(CTX(client_context), &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);
    ASSERT_EQ(STATE_REGISTER_REQUIRED2, CTX(client_context)->state);

    result = lwm2m_step(CTX(client_context), &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);

    ASSERT_EQ(STATE_REGISTERING, CTX(client_context)->state);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(CTX(client_context)->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);
}

TEST_F(AddRemoveServerTests, RemoveServer) {
    time_t timeout;

    ASSERT_TRUE(lwm2m_add_server(CTX(client_context), 123, LWM2M_SERVER_ADDR, 100, false));

    security_instance_t* secInstance = (security_instance_t*)client_context.securityObject.instanceList;

    // Add server to serverlist
    int result = lwm2m_step(CTX(client_context), &timeout);
    ASSERT_EQ(COAP_NO_ERROR, result);

    lwm2m_server_t * serverListEntry;
    serverListEntry = (lwm2m_server_t *)LWM2M_LIST_FIND(CTX(client_context)->serverList, secInstance->instanceId);
    ASSERT_TRUE(serverListEntry);

    // Now assume registering worked
    serverListEntry->status = STATE_REGISTERED;
    serverListEntry->location = (char*)lwm2m_malloc(1);

    // Unregister now
    ASSERT_TRUE(lwm2m_unregister_server(CTX(client_context), secInstance->instanceId));
    ASSERT_EQ(STATE_DEREG_PENDING, serverListEntry->status);
    serverListEntry->status = STATE_DEREGISTERED;

    lwm2m_remove_unregistered_servers(CTX(client_context));

    ASSERT_FALSE(client_context.securityObject.instanceList);
    ASSERT_FALSE(client_context.serverObject.obj.instanceList);
    ASSERT_TRUE(CTX(client_context)->serverList);

    ASSERT_EQ(CTX(client_context)->state, STATE_INITIAL);
    result = lwm2m_step(CTX(client_context), &timeout);
    ASSERT_EQ(COAP_503_SERVICE_UNAVAILABLE, result);

    ASSERT_EQ(CTX(client_context)->state, STATE_BOOTSTRAP_REQUIRED);
    ASSERT_FALSE(CTX(client_context)->serverList);
}
