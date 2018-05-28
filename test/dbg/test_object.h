#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "wakaama_object_utils.h"

lwm2m_object_meta_information_t* test_object_get_meta(void);
lwm2m_list_t* test_object_create_instance(uint16_t instance_id, void *readFun8, void *readFun32, void *readFunStr, void *execFun);

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

    char* test_str;

    char test_str_prealloc[20];

    uint8_t* test_opaque;
    size_t test_opaque_len;

    void* test_execute_fun;
    void* test_read_fun_int8;
    void* test_read_fun_uint32;
    void* test_read_fun_string;

} test_object_instance_t;

#ifdef __cplusplus
}
#endif
