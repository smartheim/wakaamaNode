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
#include <stdint.h>
#include "test_object.h"
#include "wakaama_client_debug.h"
#include "wakaama_network.h"
#include "wakaama_object_utils.h"
#include "wakaama_simple_client.h"

extern "C" {
#include "internals.h"
}

bool executed = false;

void executeFun(uint8_t* buffer, int length) {
  executed = true;
}

int8_t readFun8() {
  return -12;
}

uint32_t readFun32() {
  return 0xFFFF;
}

const char* readFunStr() {
  return "testFunction";
}

class ObjectUtilsTests : public testing::Test {
 public:
  lwm2m_context_t* lwm2mH;
  lwm2m_object_t* test_object;

 protected:
  virtual void TearDown() {
    lwm2m_client_close();
    executed = false;
  }

  virtual void SetUp() {
    test_object = lwm2m_object_create(1024, true, test_object_get_meta());
    lwm2m_object_instances_add(
        test_object,
        test_object_create_instance(10, (void*)readFun8, (void*)readFun32,
                                    (void*)readFunStr, (void*)executeFun));

    lwm2mH = lwm2m_client_init("testClient");
    ASSERT_TRUE(lwm2mH) << "Failed to initialize wakaama\r\n";

    lwm2m_add_object(lwm2mH, test_object);

    lwm2m_object_t* o = (lwm2m_object_t*)lwm2m_list_find(
        (lwm2m_list_t*)lwm2mH->objectList, 1024);
    ASSERT_EQ(o, test_object);

    ASSERT_TRUE(object_isInstanceNew(lwm2mH, 1024, 0));
    ASSERT_FALSE(object_isInstanceNew(lwm2mH, 1024, 10));
  }
};

TEST_F(ObjectUtilsTests, Reading) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID,
                     1024, 10, 0};
  lwm2m_media_type_t format = LWM2M_CONTENT_JSON;
  char* buffer;
  size_t buffer_len;
  uint8_t s =
      object_read(lwm2mH, &uri, &format, (uint8_t**)&buffer, &buffer_len);

  const char* expect =
      "{\"bn\":\"/1024/10/"
      "\",\"e\":[{\"n\":\"0\",\"v\":15},{\"n\":\"1\",\"v\":-15},{\"n\":\"2\","
      "\"v\":4095},{\"n\":\"3\",\"v\":-4095},{\"n\":\"4\",\"v\":268435455},{"
      "\"n\":\"5\",\"v\":-268435455},{\"n\":\"6\",\"v\":-281474976710655},{"
      "\"n\":\"7\",\"v\":0.12},{\"n\":\"8\",\"bv\":true},{\"n\":\"9\",\"sv\":"
      "\"test\"},{\"n\":\"10\",\"sv\":\"test\"},{\"n\":\"11\",\"sv\":\"dGVzdA=="
      "\"},{\"n\":\"14\",\"v\":-12},{\"n\":\"15\",\"v\":65535},{\"n\":\"16\","
      "\"sv\":\"testFunction\"}]}";
  int i = strlen(expect);

  ASSERT_EQ(s, CONTENT_2_05);
  ASSERT_EQ(buffer_len, i);
  ASSERT_TRUE(memcmp(expect, buffer, buffer_len) == 0);

  lwm2m_free(buffer);
}

TEST_F(ObjectUtilsTests, ExecutingNonExecutable) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID,
                     1024, 10, 0};
  uint8_t s = object_execute(lwm2mH, &uri, nullptr, 0);
  ASSERT_EQ(s, METHOD_NOT_ALLOWED_4_05);
}

TEST_F(ObjectUtilsTests, ExecutingFunction) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID |
                         LWM2M_URI_FLAG_RESOURCE_ID,
                     1024, 10, 13};
  executed = false;
  uint8_t s = object_execute(lwm2mH, &uri, nullptr, 0);
  ASSERT_EQ(s, CHANGED_2_04);
  ASSERT_TRUE(executed);
}

TEST_F(ObjectUtilsTests, Discover) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID,
                     1024, 10, 0};
  char* buffer;
  size_t buffer_len;
  uint8_t s =
      object_discover(lwm2mH, &uri, nullptr, (uint8_t**)&buffer, &buffer_len);
  ASSERT_EQ(s, CONTENT_2_05);

  const char* expect =
      "</1024/10>,</1024/10/0>,</1024/10/1>,</1024/10/2>,</1024/10/3>,</1024/10/4>,</1024/"
      "10/5>,</1024/10/6>,</1024/10/7>,</1024/10/8>,</1024/10/9>,</1024/10/"
      "10>,</1024/10/11>,</1024/10/12>,</1024/10/13>,</1024/10/14>,</1024/10/"
      "15>,</1024/10/16>";

  ASSERT_EQ(strlen(expect), buffer_len);
  buffer = (char*)realloc(buffer, buffer_len + 1);
  buffer[buffer_len] = 0;
  ASSERT_STREQ(expect, buffer);

  lwm2m_free(buffer);
}

TEST_F(ObjectUtilsTests, WriteIntBoolDouble) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID |
                         LWM2M_URI_FLAG_RESOURCE_ID,
                     1024, 10, 0};
  const char* valueInt = "10";
  size_t len = strlen(valueInt);
  test_object_instance_t* targetP =
      (test_object_instance_t*)test_object->instanceList;
  uint8_t s;

  // Check number writing

  lwm2m_attributes_t attrib;
  attrib.toSet = ATTR_FLAG_NUMERIC;
  for (int i = 0; i < 7; ++i) {
    uri.resourceId = i;
    ASSERT_EQ(COAP_205_CONTENT, object_checkReadable(lwm2mH, &uri, &attrib));
    s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)valueInt, len);
    ASSERT_EQ(s, CHANGED_2_04);
  }

  ASSERT_EQ(targetP->test_i8, 10);
  ASSERT_EQ(targetP->test_u8, 10);
  ASSERT_EQ(targetP->test_i16, 10);
  ASSERT_EQ(targetP->test_u16, 10);
  ASSERT_EQ(targetP->test_i32, 10);
  ASSERT_EQ(targetP->test_u32, 10);
  ASSERT_EQ(targetP->test_i64, 10);

  // check double writing

  uri.resourceId = 7;
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)valueInt, len);
  ASSERT_EQ(s, COAP_400_BAD_REQUEST) << "Verify method does not work";

  const char* doubleValue = "0.8";
  len = strlen(doubleValue);
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)doubleValue,
                   len);
  ASSERT_EQ(s, CHANGED_2_04) << "Verify method does not work";
  ASSERT_EQ(targetP->test_double, 0.8);

  // check boolean writing

  targetP->test_bool = false;
  const char* boolValue = "1";
  len = strlen(boolValue);
  uri.resourceId = 8;
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)boolValue, len);
  ASSERT_EQ(s, CHANGED_2_04);
  ASSERT_EQ(targetP->test_bool, true);
}

TEST_F(ObjectUtilsTests, WriteString) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID |
                         LWM2M_URI_FLAG_RESOURCE_ID,
                     1024, 10, 0};
  const char* value = "newcontent";
  size_t len = strlen(value);
  test_object_instance_t* targetP =
      (test_object_instance_t*)test_object->instanceList;
  lwm2m_object_meta_information_t* metaP =
      ((lwm2m_object_with_meta_t*)test_object)->meta;
  uint8_t s;

  uri.resourceId = 9;
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)value, len);
  ASSERT_EQ(s, CHANGED_2_04);
  ASSERT_STREQ(value, targetP->test_str);

  // Ressource 9 is a static string. after writing it should be a normal string
  ASSERT_TRUE((metaP->ressources[9].type_and_access & 0x0f) & O_RES_STRING);

  // Check prealloc string
  uri.resourceId = 10;
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)value, len);
  ASSERT_EQ(s, CHANGED_2_04);
  ASSERT_STREQ(value, targetP->test_str_prealloc);
}

TEST_F(ObjectUtilsTests, WriteOpaque) {
  lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID |
                         LWM2M_URI_FLAG_RESOURCE_ID,
                     1024, 10, 0};
  const char* value = "newcontent";
  size_t len = strlen(value);
  test_object_instance_t* targetP =
      (test_object_instance_t*)test_object->instanceList;
  lwm2m_object_meta_information_t* metaP =
      ((lwm2m_object_with_meta_t*)test_object)->meta;
  uint8_t s;

  uri.resourceId = 11;
  ASSERT_TRUE((metaP->ressources[uri.resourceId].type_and_access & 0x0f) &
              O_RES_OPAQUE_STATIC);
  s = object_write(lwm2mH, &uri, LWM2M_CONTENT_TEXT, (uint8_t*)value, len);
  ASSERT_EQ(s, CHANGED_2_04);
  ASSERT_EQ(len, targetP->test_opaque_len);
  ASSERT_TRUE(memcmp(value, targetP->test_opaque, len) == 0);

  // Ressource 11 is a static opaque. after writing it should be a normal opaque
  // value.
  ASSERT_TRUE((metaP->ressources[uri.resourceId].type_and_access & 0x0f) &
              O_RES_OPAQUE);
}
