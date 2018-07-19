/*******************************************************************************
 *
 * Copyright (c) 2015 Bosch Software Innovations GmbH, Germany.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Bosch Software Innovations GmbH - Please refer to git log
 *
 *******************************************************************************/

#include "internals.h"
#include "liblwm2m.h"
#include <gtest/gtest.h>
#include "memory.h"

TEST(tlv, decodeTL)
{
    memoryObserver.reset();
    uint8_t data1[] = {0xC3, 55, 1, 2, 3};
    uint8_t data2[] = {0x28, 2, 3, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    uint8_t data3[0x194] = {0x90, 33, 1, 0x90 };
    lwm2m_data_type_t type;
    uint16_t id = 0;
    size_t   index = 0;
    size_t   length = 0;
    int result;


    result = lwm2m_decode_TLV(data1, sizeof(data1) - 1, &type, &id, &index, &length);
    ASSERT_EQ(result, 0);

    result = lwm2m_decode_TLV(data1, sizeof(data1), &type, &id, &index, &length);
    ASSERT_EQ(result, 5);
    ASSERT_EQ(type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(id, 55);
    ASSERT_EQ(index, 2);
    ASSERT_EQ(length, 3);

    result = lwm2m_decode_TLV(data2, sizeof(data2) - 1, &type, &id, &index, &length);
    ASSERT_EQ(result, 0);

    result = lwm2m_decode_TLV(data2, sizeof(data2), &type, &id, &index, &length);
    ASSERT_EQ(result, 13);
    ASSERT_EQ(type, LWM2M_TYPE_OBJECT_INSTANCE);
    ASSERT_EQ(id, 0x0203);
    ASSERT_EQ(index, 4);
    ASSERT_EQ(length, 9);

    result = lwm2m_decode_TLV(data3, sizeof(data3) - 1, &type, &id, &index, &length);
    ASSERT_EQ(result, 0);

    result = lwm2m_decode_TLV(data3, sizeof(data3), &type, &id, &index, &length);
    ASSERT_EQ(result, 0x194);
    ASSERT_EQ(type, LWM2M_TYPE_MULTIPLE_RESOURCE);
    ASSERT_EQ(id, 33);
    ASSERT_EQ(index, 4);
    ASSERT_EQ(length, 0x190);

    MEMEVAL(FAIL());
}

TEST(tlv, tlv_parse)
{
    memoryObserver.reset();
    // Resource 55 {1, 2, 3}
    uint8_t data1[] = {0xC3, 55, 1, 2, 3};
    // Instance 0x203 {Resource 55 {1, 2, 3}, Resource 66 {4, 5, 6, 7, 8, 9, 10, 11, 12 } }
    uint8_t data2[] = {0x28, 2, 3, 17, 0xC3, 55, 1, 2, 3, 0xC8, 66, 9, 4, 5, 6, 7, 8, 9, 10, 11, 12, };
    // Instance 11 {MultiResource 11 {ResourceInstance 0 {1, 2, 3}, ResourceInstance 1 {4, 5, 6, 7, 8, 9, ... } }
    uint8_t data3[174] = {0x08, 11, 171, 0x88, 77, 168, 0x43, 0, 1, 2, 3, 0x48, 1, 160, 4, 5, 6, 7, 8, 9};
    int result;
    lwm2m_data_t *dataP;
    lwm2m_data_t *tlvSubP;

    result = lwm2m_data_parse(nullptr, data1, sizeof(data1), LWM2M_CONTENT_TLV, &dataP);
    ASSERT_EQ(result, 1);
    ASSERT_TRUE(dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(dataP->id, 55);
    ASSERT_EQ(dataP->value.asBuffer.length, 3);
    ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, &data1[2], 3));
    lwm2m_data_free(result, dataP);

    result = lwm2m_data_parse(nullptr, data2, sizeof(data2), LWM2M_CONTENT_TLV, &dataP);
    ASSERT_EQ(result, 1);
    ASSERT_TRUE(dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_OBJECT_INSTANCE);
    ASSERT_EQ(dataP->id, 0x203);
    ASSERT_EQ(dataP->value.asChildren.count, 2);
    ASSERT_TRUE(dataP->value.asChildren.array);
    tlvSubP = dataP->value.asChildren.array;

    ASSERT_EQ(tlvSubP[0].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvSubP[0].id, 55);
    ASSERT_EQ(tlvSubP[0].value.asBuffer.length, 3);
    ASSERT_TRUE(0 == memcmp(tlvSubP[0].value.asBuffer.buffer, &data2[6], 3));

    ASSERT_EQ(tlvSubP[1].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvSubP[1].id, 66);
    ASSERT_EQ(tlvSubP[1].value.asBuffer.length, 9);
    ASSERT_TRUE(0 == memcmp(tlvSubP[1].value.asBuffer.buffer, &data2[12], 9));
    lwm2m_data_free(result, dataP);

    result = lwm2m_data_parse(nullptr, data3, sizeof(data3), LWM2M_CONTENT_TLV, &dataP);
    ASSERT_EQ(result, 1);
    ASSERT_TRUE(dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_OBJECT_INSTANCE);
    ASSERT_EQ(dataP->id, 11);
    ASSERT_EQ(dataP->value.asChildren.count, 1);
    ASSERT_TRUE(dataP->value.asChildren.array);
    tlvSubP = dataP->value.asChildren.array;

    ASSERT_EQ(tlvSubP[0].type, LWM2M_TYPE_MULTIPLE_RESOURCE);
    ASSERT_EQ(tlvSubP[0].id, 77);
    ASSERT_EQ(tlvSubP[0].value.asChildren.count, 2);
    ASSERT_TRUE(tlvSubP[0].value.asChildren.array);
    tlvSubP = tlvSubP[0].value.asChildren.array;

    ASSERT_EQ(tlvSubP[0].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvSubP[0].id, 0);
    ASSERT_EQ(tlvSubP[0].value.asBuffer.length, 3);
    ASSERT_TRUE(0 == memcmp(tlvSubP[0].value.asBuffer.buffer, &data3[8], 3));

    ASSERT_EQ(tlvSubP[1].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvSubP[1].id, 1);
    ASSERT_EQ(tlvSubP[1].value.asBuffer.length, 160);
    ASSERT_TRUE(0 == memcmp(tlvSubP[1].value.asBuffer.buffer, &data3[14], 160));
    lwm2m_data_free(result, dataP);

    MEMEVAL(FAIL());
}

TEST(tlv, tlv_serialize)
{
    memoryObserver.reset();

    int result;
    lwm2m_data_t *dataP;
    lwm2m_data_t *tlvSubP;
    lwm2m_data_t *tlvRscInstP;
    uint8_t data1[] = {1, 2, 3, 4};
    uint8_t data2[170] = {5, 6, 7, 8};
    uint8_t* buffer;



    tlvSubP = lwm2m_data_new(2);
    ASSERT_TRUE(tlvSubP);

    tlvSubP[0].id = 66;
    lwm2m_data_encode_opaque(data1, sizeof(data1), tlvSubP);
    ASSERT_EQ(tlvSubP[0].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvSubP[0].value.asBuffer.length, sizeof(data1));
    ASSERT_TRUE(tlvSubP[0].value.asBuffer.buffer);

    tlvSubP[1].type = LWM2M_TYPE_MULTIPLE_RESOURCE;
    tlvSubP[1].id = 77;
    tlvSubP[1].value.asChildren.count = 1;
    tlvSubP[1].value.asChildren.array = lwm2m_data_new(1);
    ASSERT_TRUE(tlvSubP[1].value.asChildren.array);
    tlvRscInstP = tlvSubP[1].value.asChildren.array;

    tlvRscInstP[0].id = 0;
    lwm2m_data_encode_opaque(data2, sizeof(data2), tlvRscInstP);
    ASSERT_EQ(tlvRscInstP[0].type, LWM2M_TYPE_OPAQUE);
    ASSERT_EQ(tlvRscInstP[0].value.asBuffer.length, sizeof(data2));
    ASSERT_TRUE(tlvRscInstP[0].value.asBuffer.buffer);

    dataP = lwm2m_data_new(1);
    ASSERT_TRUE(dataP);
    dataP->id = 3;
    lwm2m_data_include(tlvSubP, 2, dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_OBJECT_INSTANCE);
    ASSERT_EQ(dataP->value.asChildren.count, 2);
    ASSERT_EQ(dataP->value.asChildren.array, tlvSubP);

    lwm2m_media_type_t media_type = LWM2M_CONTENT_TLV;
    result = lwm2m_data_serialize(nullptr, 1, dataP, &media_type, &buffer);
    ASSERT_EQ(result, sizeof(data2) + sizeof(data1) + 11);

    ASSERT_EQ(buffer[0], 0x08);
    ASSERT_EQ(buffer[1], 3);
    ASSERT_EQ(buffer[2], sizeof(data2) + sizeof(data1) + 8);

    ASSERT_EQ(buffer[3], 0xC0 + sizeof(data1));
    ASSERT_EQ(buffer[4], 66);
    ASSERT_TRUE(0 == memcmp(data1, &buffer[5], sizeof(data1)));

    ASSERT_EQ(buffer[5 + sizeof(data1)], 0x88);
    ASSERT_EQ(buffer[6 + sizeof(data1)], 77);
    ASSERT_EQ(buffer[7 + sizeof(data1)], sizeof(data2) + 3);

    ASSERT_EQ(buffer[8 + sizeof(data1)], 0x48);
    ASSERT_EQ(buffer[9 + sizeof(data1)], 0);
    ASSERT_EQ(buffer[10 + sizeof(data1)], sizeof(data2));
    ASSERT_TRUE(0 == memcmp(data2, &buffer[11 + sizeof(data1)], sizeof(data2)));

    lwm2m_data_free(1, dataP);
    lwm2m_free(buffer);

    MEMEVAL(FAIL());
}

TEST(tlv, tlv_int)
{
   memoryObserver.reset();
   int64_t value;
   int result;
   lwm2m_data_t *dataP =  lwm2m_data_new(1);
   ASSERT_TRUE(dataP);

   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 0);

   lwm2m_data_encode_int(0x12, dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_INTEGER);
   ASSERT_EQ(dataP->value.asInteger, 0x12);
   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, 0x12);

   lwm2m_data_encode_string("18", dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
   ASSERT_EQ(dataP->value.asBuffer.length, 2);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "18", 2));
   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, 18);
   lwm2m_free(dataP->value.asBuffer.buffer);

   lwm2m_data_encode_string("-14678", dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
   ASSERT_EQ(dataP->value.asBuffer.length, 6);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "-14678", 6));
   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, -14678);
   lwm2m_free(dataP->value.asBuffer.buffer);

   uint8_t data1[] = { 0xed, 0xcc };
   lwm2m_data_encode_opaque(data1, sizeof(data1), dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_OPAQUE);
   ASSERT_EQ(dataP->value.asBuffer.length, sizeof(data1));
   ASSERT_TRUE(dataP->value.asBuffer.buffer);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, data1, sizeof(data1)));
   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, -0x1234);
   lwm2m_free(dataP->value.asBuffer.buffer);

   uint8_t data2[] = { 0x7f, 0x34, 0x56, 0x78, 0x91, 0x22, 0x33, 0x44 };
   lwm2m_data_encode_opaque(data2, sizeof(data2), dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_OPAQUE);
   ASSERT_EQ(dataP->value.asBuffer.length, sizeof(data2));
   ASSERT_TRUE(dataP->value.asBuffer.buffer);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, data2, sizeof(data2)));
   result = lwm2m_data_decode_int(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, 0x7f34567891223344);
   lwm2m_free(dataP->value.asBuffer.buffer);

   dataP->value.asBuffer.buffer =nullptr;

   lwm2m_data_free(1, dataP);
   MEMEVAL(FAIL());
}

TEST(tlv, tlv_bool)
{
   memoryObserver.reset();
   bool value;
   int result;
   lwm2m_data_t *dataP =  lwm2m_data_new(1);
   ASSERT_TRUE(dataP);

   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 0);

   lwm2m_data_encode_bool(true, dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_BOOLEAN);
   ASSERT_EQ(dataP->value.asBoolean, true);
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, true);

   lwm2m_data_encode_bool(false, dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_BOOLEAN);
   ASSERT_EQ(dataP->value.asBoolean, false);
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, false);

   lwm2m_data_encode_string("1", dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
   ASSERT_EQ(dataP->value.asBuffer.length, 1);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "1", 1));
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, true);
   lwm2m_free(dataP->value.asBuffer.buffer);

   lwm2m_data_encode_string("0", dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
   ASSERT_EQ(dataP->value.asBuffer.length, 1);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "0", 1));
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, false);
   lwm2m_free(dataP->value.asBuffer.buffer);

   uint8_t data1[] = { 0x00 };
   lwm2m_data_encode_opaque(data1, sizeof(data1), dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_OPAQUE);
   ASSERT_EQ(dataP->value.asBuffer.length, sizeof(data1));
   ASSERT_TRUE(dataP->value.asBuffer.buffer);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, data1, sizeof(data1)));
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, false);
   lwm2m_free(dataP->value.asBuffer.buffer);

   uint8_t data2[] = { 0x01 };
   lwm2m_data_encode_opaque(data2, sizeof(data2), dataP);
   ASSERT_EQ(dataP->type, LWM2M_TYPE_OPAQUE);
   ASSERT_EQ(dataP->value.asBuffer.length, sizeof(data2));
   ASSERT_TRUE(dataP->value.asBuffer.buffer);
   ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, data2, sizeof(data2)));
   result = lwm2m_data_decode_bool(dataP, &value);
   ASSERT_EQ(result, 1);
   ASSERT_EQ(value, true);
   lwm2m_free(dataP->value.asBuffer.buffer);

   dataP->value.asBuffer.buffer= nullptr;

   lwm2m_data_free(1, dataP);
   MEMEVAL(FAIL());
}

TEST(tlv, tlv_float)
{
    memoryObserver.reset();
    double value;
    int result;
    lwm2m_data_t *dataP = lwm2m_data_new(1);
    ASSERT_TRUE(dataP);

    result = lwm2m_data_decode_float(dataP, &value);
    ASSERT_EQ(result, 0);

    lwm2m_data_encode_float(1234.56, dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_FLOAT);
    ASSERT_EQ(dataP->value.asFloat, 1234.56);
    result = lwm2m_data_decode_float(dataP, &value);
    ASSERT_EQ(result, 1);
    ASSERT_EQ(value, 1234.56);

    lwm2m_data_encode_string("1234.56", dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
    ASSERT_EQ(dataP->value.asBuffer.length, 7);
    ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "1234.56", 7));
    result = lwm2m_data_decode_float(dataP, &value);
    ASSERT_EQ(result, 1);
    ASSERT_EQ(value, 1234.56);
    lwm2m_free(dataP->value.asBuffer.buffer);

    lwm2m_data_encode_string("-123456789.987", dataP);
    ASSERT_EQ(dataP->type, LWM2M_TYPE_STRING);
    ASSERT_EQ(dataP->value.asBuffer.length, 14);
    ASSERT_TRUE(0 == memcmp(dataP->value.asBuffer.buffer, "-123456789.987", 14));
    result = lwm2m_data_decode_float(dataP, &value);
    ASSERT_EQ(result, 1);
    ASSERT_EQ(value, -123456789.987);
    lwm2m_free(dataP->value.asBuffer.buffer);

    dataP->value.asBuffer.buffer= nullptr;

    lwm2m_data_free(1, dataP);
    MEMEVAL(FAIL());
}

