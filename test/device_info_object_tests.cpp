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
#include "lwm2m/network.h"
#include <stdint.h>
#include "memory.h"
#include <algorithm>

extern "C" {
    #include "internals.h"
    #include "../src/internal_objects.h"

    uint8_t lwm2m_get_bat_level() {
        return 12;
    }

    uint8_t lwm2m_get_bat_status() {
        return 12;
    }

    int64_t lwm2m_get_free_mem() {
        return 12;
    }

    int64_t lwm2m_get_total_mem() {
        return 12;
    }

    int64_t lwm2m_get_last_error() {
        return -12;
    }

    bool reboot_executed = false;
    void lwm2m_reboot() {
        reboot_executed = true;
    }

    bool factory_reset = false;
    void lwm2m_factory_reset() {
        factory_reset = true;
    }

    // Return dummy time and overwrite platform implementation (which is declared with __attribute__((weak)))
    int64_t lwm2m_gettime() {
        return 1498765432;
    }
}

/**
 * Tests the device information object with all optional fields enabled
 */
class DeviceInfoObjectTests : public testing::Test {
public:
    lwm2m_client_context_t client_context;
    device_instance_t * deviceInstance;
    lwm2m_object_t* deviceObject;
 protected:
    virtual void TearDown() {
        lwm2m_client_close(&client_context);
        std::for_each(memoryObserver.memAreas.begin (),memoryObserver.memAreas.end(),
                      [](MemoryObserver::MemAreas::value_type it){
            FAIL() << "Entry @ " +std::to_string(it.first) + "\n" + it.second;
        });
    }

    virtual void SetUp() {
        memoryObserver.reset();

        lwm2m_client_init(&client_context, "testClient");

        deviceInstance = &client_context.deviceInstance;

        deviceObject = (lwm2m_object_t*)lwm2m_list_find((lwm2m_list_t *)CTX(client_context)->objectList, 3);
        ASSERT_TRUE(deviceObject);
        ASSERT_EQ(deviceObject->instanceList, (lwm2m_list_t*)deviceInstance);

        deviceInstance->manufacturer = "manufacturer";
        deviceInstance->model_name = "model_name";
        deviceInstance->serial_number = "serial_number";
        deviceInstance->firmware_ver = "firmware_ver";
        deviceInstance->device_type = "device_type";
        deviceInstance->hardware_ver = "hardware1.0";
        deviceInstance->software_ver = "software1.0";
        memcpy(deviceInstance->time_offset.data, "+11:12", sizeof("+11:12"));
        deviceInstance->timezone = "Europe/+2";
    }
};

// Perform a read all test
TEST_F(DeviceInfoObjectTests, ReadAll) {
    lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID, 3, 0, 0};
    lwm2m_media_type_t format = LWM2M_CONTENT_JSON;

    std::string fullRead;
    {
        size_t buffer_len=0;
        char* buffer;
        uint8_t s = object_read(CTX(client_context),&uri,&format,(uint8_t**)&buffer,&buffer_len);
        ASSERT_EQ(s, CONTENT_2_05);
        fullRead.assign(buffer,buffer_len);
        lwm2m_free(buffer);
    }

    const char expect[] = "{\"bn\":\"/3/0/\",\"e\":[{\"n\":\"0\",\"sv\":\"manufacturer\"},{\"n\":\"1\",\"sv\":\"model_name\"},{\"n\":\"2\",\"sv\":\"serial_number\"},{\"n\":\"3\",\"sv\":\"firmware_ver\"},{\"n\":\"9\",\"v\":12},{\"n\":\"20\",\"v\":12},{\"n\":\"11\",\"v\":-12},{\"n\":\"13\",\"v\":1498765432},{\"n\":\"16\",\"sv\":\"U\"},{\"n\":\"14\",\"sv\":\"+11:12\"},{\"n\":\"15\",\"sv\":\"Europe/+2\"},{\"n\":\"17\",\"sv\":\"device_type\"},{\"n\":\"18\",\"sv\":\"hardware1.0\"},{\"n\":\"19\",\"sv\":\"software1.0\"},{\"n\":\"9\",\"v\":12},{\"n\":\"20\",\"v\":12},{\"n\":\"10\",\"v\":12},{\"n\":\"21\",\"v\":12}]}";

    ASSERT_STREQ(expect, fullRead.c_str());
    ASSERT_EQ(sizeof(expect), fullRead.size()+1);
}

TEST_F(DeviceInfoObjectTests, ExecuteReboot) {
    lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID, 3, 0, RES_M_REBOOT};
    uint8_t* buffer=0;
    size_t buffer_len=0;
    ASSERT_FALSE(reboot_executed);
    uint8_t s =  object_execute(CTX(client_context),&uri,buffer,buffer_len);
    ASSERT_EQ(COAP_205_CONTENT, s);
    ASSERT_TRUE(reboot_executed);
}

TEST_F(DeviceInfoObjectTests, ExecuteFactoryReset) {
    lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID, 3, 0, RES_O_FACTORY_RESET};
    uint8_t* buffer=0;
    size_t buffer_len=0;
    ASSERT_FALSE(factory_reset);
    uint8_t s =  object_execute(CTX(client_context),&uri,buffer,buffer_len);
    ASSERT_EQ(COAP_205_CONTENT, s);
    ASSERT_TRUE(factory_reset);
}
