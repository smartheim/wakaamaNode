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

#include "lwm2m/objects.h"

/*
 * Implements an object for testing purpose
 *
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name        | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  test_u8     |  0 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_i8     |  1 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_u16    |  2 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_i16    |  3 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_u32    |  4 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_i32    |  5 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_i64    |  6 |    R/W     |    No     |    Yes    | Integer |       |       |                       |
 *  test_double |  7 |    R/W     |    No     |    Yes    | Float   |       |       |                       |
 *  test_bool   |  8 |    R/W     |    No     |    Yes    | Bool    |       |       |                       |
 *  test_str    |  9 |     R      |    No     |    Yes    | String  |       |       | read only string      |
 *  test_str_pre| 10 |    R/W     |    No     |    Yes    | String  |       |       | prealloc string       |
 *  test_opaque | 11 |    R/W     |    No     |    Yes    | String  |       |       | Opaque string         |
 *  test_opaq_pr| 12 |    R/W     |    No     |    Yes    | String  |       |       | Opaque string         |
 *  exec        | 13 |     E      |    No     |    Yes    |         |       |       |                       |
 *  exec_callbac| 14 |     E      |    No     |    Yes    |         |       |       | Callback execute      |
 *  test_i8_fun | 15 |     R      |    No     |    Yes    | Integer |       |       | int8 from function    |
 *  test_u32_fun| 16 |     R      |    No     |    Yes    | Integer |       |       | int32 from function   |
 *  test_str_fun| 17 |     R      |    No     |    Yes    | String  |       |       | string from function  |
 *  test_rw_fun | 18 |     RW     |    No     |    Yes    | String  |       |       | R/W from/to function  |
 *
 */

struct TestInheritance : public Opaque<20>{  };

struct MyTestObjectInstance : public Lwm2mObjectInstance {
    uint8_t test_u8=  0x0F;
    int8_t  test_i8=  -0x0F;
    uint16_t test_u16 = 0x0FFF;
    int16_t  test_i16 = -0x0FFF;
    uint32_t test_u32 = 0x0FFFFFFF;
    int32_t  test_i32 = -0x0FFFFFFF;
    int64_t  test_i64 = -0x0FFFFFFFFFFFF;

    double   test_double = 0.12;
    bool test_bool = true;
    const char* test_str = "test";

    PreallocString<20> test_str_prealloc;
    OpaqueIndirect test_opaque{0,4,(uint8_t*)"test"};
    Opaque<20> test_opaque_prealloc;
    TestInheritance test_inheritance;

    Executable test_execute_fun;
    IndirectRead<int8_t> test_read_fun_int8;
    IndirectRead<uint32_t> test_read_fun_uint32;
    IndirectRead<const char*> test_read_fun_string;

    IndirectWrite<const char*> test_write_fun_string;
    IndirectReadWrite<const char*> test_readWrite_fun_string;

    MyTestObjectInstance() = default;
    MyTestObjectInstance(Executable test_execute_fun,
                         IndirectRead<int8_t> test_read_fun_int8,
                         IndirectRead<uint32_t> test_read_fun_uint32,
                         IndirectRead<const char*> test_read_fun_string,
                         IndirectWrite<const char*> test_write_fun_string,
                         IndirectReadWrite<const char*> test_readWrite_fun_string)
        : test_execute_fun(test_execute_fun), test_read_fun_int8(test_read_fun_int8),
        test_read_fun_uint32(test_read_fun_uint32),test_read_fun_string(test_read_fun_string),
        test_write_fun_string(test_write_fun_string),test_readWrite_fun_string(test_readWrite_fun_string) {
        test_str_prealloc.copy("test");
        test_opaque_prealloc.copy("ab\0\nab",6);
    }
};

#pragma pack(push,1)
struct MyTestObjectSecond: public Lwm2mObject<1024, MyTestObjectSecond, MyTestObjectInstance> {
    Resource(0, &MyTestObjectInstance::test_u8, O_RES_RW) test_u8;
    Resource(1, &MyTestObjectInstance::test_i8, O_RES_RW) test_i8;
    Resource(2, &MyTestObjectInstance::test_u16, O_RES_RW) test_u16;
    Resource(3, &MyTestObjectInstance::test_i16, O_RES_RW) test_i16;
    Resource(4, &MyTestObjectInstance::test_u32, O_RES_RW) test_u32;
    Resource(5, &MyTestObjectInstance::test_i32, O_RES_RW) test_i32;
    Resource(6, &MyTestObjectInstance::test_i64, O_RES_RW) test_i64;
};
#pragma pack(pop)

#pragma pack(push,1)
struct MyTestObject: public Lwm2mObject<1024, MyTestObject, MyTestObjectInstance> {
    Resource(0, &MyTestObjectInstance::test_u8, O_RES_RW) test_u8;
    Resource(1, &MyTestObjectInstance::test_i8, O_RES_RW) test_i8;
    Resource(2, &MyTestObjectInstance::test_u16, O_RES_RW) test_u16;
    Resource(3, &MyTestObjectInstance::test_i16, O_RES_RW) test_i16;
    Resource(4, &MyTestObjectInstance::test_u32, O_RES_RW) test_u32;
    Resource(5, &MyTestObjectInstance::test_i32, O_RES_RW) test_i32;
    Resource(6, &MyTestObjectInstance::test_i64, O_RES_RW) test_i64;

    Resource(7, &MyTestObjectInstance::test_double, O_RES_RW) test_double;

    Resource(8, &MyTestObjectInstance::test_bool, O_RES_RW) test_bool;

    Resource(9, &MyTestObjectInstance::test_str, O_RES_R) test_str;

    Resource(10, &MyTestObjectInstance::test_str_prealloc, O_RES_RW) test_str_prealloc;

    Resource(11, &MyTestObjectInstance::test_opaque, O_RES_RW) test_opaque;
    Resource(12, &MyTestObjectInstance::test_opaque_prealloc, O_RES_RW) test_opaque_prealloc;

    Resource(13, &MyTestObjectInstance::test_execute_fun) test_execute_fun;
    Resource(14, &MyTestObjectInstance::test_read_fun_int8) test_read_fun_int8;
    Resource(15, &MyTestObjectInstance::test_read_fun_uint32) test_read_fun_uint32;
    Resource(16, &MyTestObjectInstance::test_read_fun_string) test_read_fun_string;

    Resource(17, &MyTestObjectInstance::test_write_fun_string) test_write_fun_string;
    Resource(18, &MyTestObjectInstance::test_readWrite_fun_string) test_readWrite_fun_string;

    Resource(19, &MyTestObjectInstance::test_inheritance, O_RES_RW) test_inheritance;

    MyTestObject() {
        verifyWrite = ([](MyTestObjectInstance* i, uint16_t res_id) {
            if(res_id==7 && (i->test_double > 1.0 || i->test_double < 0.0)) return false;
            return true;
        });
    }
};
#pragma pack(pop)
