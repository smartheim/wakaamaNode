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

#include "test_object_c.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

OBJECT_META(test_object_instance_t, test_object_meta, 1024, test_object_write_verify_cb,
    { 0, O_RES_RW,O_RES_UINT8,   offsetof(test_object_instance_t,test_u8)},
    { 1, O_RES_RW,O_RES_INT8,    offsetof(test_object_instance_t,test_i8)},
    { 2, O_RES_RW,O_RES_UINT16,  offsetof(test_object_instance_t,test_u16)},
    { 3, O_RES_RW,O_RES_INT16,   offsetof(test_object_instance_t,test_i16)},
    { 4, O_RES_RW,O_RES_UINT32,  offsetof(test_object_instance_t,test_u32)},
    { 5, O_RES_RW,O_RES_INT32,   offsetof(test_object_instance_t,test_i32)},
    { 6, O_RES_RW,O_RES_INT64,   offsetof(test_object_instance_t,test_i64)},

    { 7, O_RES_RW,O_RES_DOUBLE,  offsetof(test_object_instance_t,test_double)},

    { 8, O_RES_RW,O_RES_BOOL,    offsetof(test_object_instance_t,test_bool)},

    { 9, O_RES_R, O_RES_STRING,  offsetof(test_object_instance_t,test_str)},
    {10, O_RES_RW,O_RES_STRING_PREALLOC, offsetof(test_object_instance_t,test_str_prealloc)},

    {11, O_RES_RW,O_RES_OPAQUE_INDIRECT, offsetof(test_object_instance_t,test_opaque)},
    {12, O_RES_RW,O_RES_OPAQUE_PREALLOC, offsetof(test_object_instance_t,test_opaque_prealloc)},

    {13, O_RES_E, 0,                     offsetof(test_object_instance_t,test_execute_fun)},

    {14, O_RES_R|O_RES_E,O_RES_INT8,     offsetof(test_object_instance_t,test_read_fun_int8)},
    {15, O_RES_R|O_RES_E,O_RES_UINT32,   offsetof(test_object_instance_t,test_read_fun_uint32)},
    {16, O_RES_R|O_RES_E,O_RES_STRING,   offsetof(test_object_instance_t,test_read_fun_string)},
    {17, O_RES_W|O_RES_E,O_RES_STRING,   offsetof(test_object_instance_t,test_write_fun_string)},
    {18, O_RES_RW|O_RES_E,O_RES_STRING,  offsetof(test_object_instance_t,test_readWrite_fun_string)},
    {19, O_RES_RW,O_RES_OPAQUE_PREALLOC, offsetof(test_object_instance_t,test_oaque_empty)},
)

lwm2m_object_t *get_test_object() {
    return test_object_metaP;
}

lwm2m_list_t* test_object_create_instance(uint16_t instance_id,
                                          IndirectReadType(int8_t,readFun8),
                                          IndirectReadType(uint32_t,readFun32),
                                          IndirectReadType(const char*,readFunStr),
                                          IndirectWriteType(const char*,writeFunStr),
                                          ExecutableType execFun) {
    test_object_instance_t * targetP = (test_object_instance_t *)malloc(sizeof(test_object_instance_t));
    if (NULL == targetP) return NULL;
    memset(targetP, 0, sizeof(test_object_instance_t));
    targetP->shortID = instance_id;

    targetP->test_i8 =  -0x0F;
    targetP->test_i16 = -0x0FFF;
    targetP->test_i32 = -0x0FFFFFFF;
    targetP->test_i64 = -0x0FFFFFFFFFFFF;

    targetP->test_u8 =  0x0F;
    targetP->test_u16 = 0x0FFF;
    targetP->test_u32 = 0x0FFFFFFF;

    targetP->test_bool = true;

    targetP->test_double = 0.12;

    targetP->test_str = "test";

    targetP->test_str_prealloc.reserved_len = 20;
    strncpy((char*)targetP->test_str_prealloc.data, "test", targetP->test_str_prealloc.reserved_len);
    targetP->test_str_prealloc.used_len = 4;

    targetP->test_opaque.data = (uint8_t*)"test";
    targetP->test_opaque.reserved_len = 0;
    targetP->test_opaque.used_len = 4;

    memcpy(targetP->test_opaque_prealloc.data, "ab\0\nab", 6);
    targetP->test_opaque_prealloc.reserved_len = 20;
    targetP->test_opaque_prealloc.used_len = 6;

    targetP->test_oaque_empty.reserved_len = 20;
    targetP->test_oaque_empty.used_len = 0;

    targetP->test_read_fun_int8 = readFun8;
    targetP->test_read_fun_uint32 = readFun32;
    targetP->test_read_fun_string = readFunStr;
    targetP->test_write_fun_string = writeFunStr;
    targetP->test_readWrite_fun_string.read = readFunStr;
    targetP->test_readWrite_fun_string.write = writeFunStr;
    targetP->test_execute_fun = execFun;

    return (lwm2m_list_t*)targetP;
}

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==7 && (i->test_double > 1.0 || i->test_double < 0.0)) return false;

    return true;
}
