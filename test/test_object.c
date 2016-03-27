/*
 Released to the public domain.

 David Graeff <david.graeff@web.de>
*/

/*
 * Implements an object for testing purpose
 *
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  test |  0 |    R/W     |    No     |    Yes    | Integer | 0-128 |       |                       |
 *  exec |  1 |     E      |    No     |    Yes    |         |       |       |                       |
 *  dec  |  2 |    R/W     |    No     |    Yes    |  Float  |       |       |                       |
 *  sig  |  3 |    R/W     |    No     |    Yes    | Integer |       |       | 16-bit signed integer |
 *
 */

#include "test_object.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {O_RES_RW|O_RES_UINT8,  offsetof(test_object_instance_t,test_u8)},
    {O_RES_RW|O_RES_INT8,   offsetof(test_object_instance_t,test_i8)},
    {O_RES_RW|O_RES_UINT16,  offsetof(test_object_instance_t,test_u16)},
    {O_RES_RW|O_RES_INT16,   offsetof(test_object_instance_t,test_i16)},
    {O_RES_RW|O_RES_UINT32,  offsetof(test_object_instance_t,test_u32)},
    {O_RES_RW|O_RES_INT32,   offsetof(test_object_instance_t,test_i32)},
    {O_RES_RW|O_RES_INT64,   offsetof(test_object_instance_t,test_i64)},

    {O_RES_RW|O_RES_DOUBLE, offsetof(test_object_instance_t,test_double)},

    {O_RES_RW|O_RES_BOOL, offsetof(test_object_instance_t,test_bool)},

    {O_RES_RW|O_RES_STRING_STATIC,  offsetof(test_object_instance_t,test_str)},
    {O_RES_RW|O_RES_STRING_PREALLOC,  offsetof(test_object_instance_t,test_str_prealloc)},
    {O_RES_RW|O_RES_OPAQUE_STATIC,  offsetof(test_object_instance_t,test_opaque)},

    {O_RES_E                       ,  0},

    {O_RES_E|O_RES_FUNCTION        ,  offsetof(test_object_instance_t,test_execute_fun)},

    {O_RES_R|O_RES_INT8|O_RES_FUNCTION,  offsetof(test_object_instance_t,test_read_fun_int8)},
    {O_RES_R|O_RES_UINT32|O_RES_FUNCTION,  offsetof(test_object_instance_t,test_read_fun_uint32)},
    {O_RES_R|O_RES_STRING|O_RES_FUNCTION,  offsetof(test_object_instance_t,test_read_fun_string)}
);

lwm2m_object_meta_information_t *test_object_get_meta() {
    return &test_object_meta;
}

lwm2m_list_t* test_object_create_instance(uint16_t instance_id, void* readFun8, void* readFun32, void* readFunStr, void* execFun) {
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
    strncpy(targetP->test_str_prealloc, "test", 5);

    targetP->test_opaque = "test";
    targetP->test_opaque_len = 4;

    targetP->test_read_fun_int8 = readFun8;
    targetP->test_read_fun_uint32 = readFun32;
    targetP->test_read_fun_string = readFunStr;
    targetP->test_execute_fun = execFun;

    return (lwm2m_list_t*)targetP;
}

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==7 && (i->test_double > 1.0 || i->test_double < 0.0)) return false;

    return true;
}
