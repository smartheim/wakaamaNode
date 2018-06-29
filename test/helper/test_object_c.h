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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "lwm2m/c_objects.h"

lwm2m_object_t *get_test_object(void);
lwm2m_list_t* test_object_create_instance(uint16_t instance_id,
                                          IndirectReadType(int8_t,readFun8),
                                          IndirectReadType(uint32_t,readFun32),
                                          IndirectReadType(const char*,readFunStr),
                                          IndirectWriteType(const char*,writeFunStr),
                                          ExecutableType execFun);

typedef struct _test_object_instance_
{
    /*
     * The first two are mandatories and represent the pointer to the next instance and the ID of this one. The rest
     * is the instance scope user data (uint8_t test in this case)
     */
    struct _test_object_instance_ * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id

    uint8_t test_u8;
    int8_t  test_i8;
    uint16_t test_u16;
    int16_t  test_i16;
    uint32_t test_u32;
    int32_t  test_i32;
    int64_t  test_i64;

    double   test_double;

    bool test_bool;

    // Read only c-string O_RES_STRING
    char* test_str;

    OpaqueType(20) test_oaque_empty;
    OpaqueType(20) test_str_prealloc;
    OpaqueIndirect test_opaque;
    OpaqueType(20) test_opaque_prealloc;

    ExecutableType test_execute_fun;
    IndirectReadType(int8_t,test_read_fun_int8);
    IndirectReadType(uint32_t,test_read_fun_uint32);
    IndirectReadType(const char*,test_read_fun_string);
    IndirectWriteType(const char*,test_write_fun_string);
    IndirectReadWriteType(const char*) test_readWrite_fun_string;

} test_object_instance_t;

#ifdef __cplusplus
}
#endif
