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
#include "../../wakaama/liblwm2m.h"
#include <assert.h>

/*
 * Methods and Enums defined in this file are for easily creating a new lwM2M object definition
 * and object instances. This is for the C-API.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Implement this method to get notified of altered lwM2M resources.
 *
 * This method is only called if all verifications and validations succeeded and the
 * resource value has actually been written.
 */
void lwm2m_resource_changed_event(uint16_t object_id, uint16_t object_instance_id, uint16_t resource_id);

typedef char* (*readFunc) (lwm2m_context_t *contextP,lwm2m_list_t* instance);
typedef void  (*execFunc) (lwm2m_context_t *contextP,lwm2m_list_t* instance);

typedef enum _lwm2m_object_util_type_ {
    O_RES_EXEC   = 0, ///< Executable resource == no type
    O_RES_BOOL   = 1, ///< A boolean value
    O_RES_DOUBLE = 2, ///< A floating point decimal value
    O_RES_INT8   = 3, ///< Int with range [-128,127]
    O_RES_UINT8  = 4, ///< Int with range [0,255]
    O_RES_INT16  = 5, ///< Int with range [-32000,32000]
    O_RES_UINT16 = 6, ///< Int with range [0,65500]
    O_RES_INT32  = 7, ///< Int with range [-2^31,2^31-1]
    O_RES_UINT32 = 8, ///< Int with range [0, 2^32-1]
    O_RES_INT64  = 9, ///< Int with range [-2^63, 2^63-1]
    O_RES_STRING          = 10, ///< Readonly c-string
    O_RES_STRING_PREALLOC = 11, ///< preallocated space. To be used with OpaqueType(N) in C or Opaque<N> in C++.
    O_RES_OPAQUE_INDIRECT = 12, ///< To be used with type OpaqueIndirect
    O_RES_OPAQUE_PREALLOC = 13  ///< preallocated space. To be used with OpaqueType(N) in C or Opaque<N> in C++.
} lwm2m_object_util_type_t;

typedef enum _lwm2m_object_util_access_ {
    O_RES_R  = 1, ///< Read only access
    O_RES_W  = 2, ///< Write only access
    O_RES_RW = O_RES_R|O_RES_W, ///< Read/Write access
    O_RES_E  = 4, ///< Standalone: Makes this resource executable. Combinded with O_RES_R: Reads the resource value from the function.
    O_RES_M  = 8  ///< Indicator for a resource modification. After a write this flag will be erased.
} lwm2m_object_util_access_t;

#pragma GCC diagnostic push
#ifdef __clang__
#pragma clang diagnostic ignored "-Wpedantic"
#endif
#pragma GCC diagnostic ignored "-Wpedantic"
typedef struct _lwm2m_object_res_item_t_ {
    uint16_t ressource_id;
    uint8_t access:4;
    uint8_t type:4;
    uint8_t struct_member_offset;
} lwm2m_object_res_item_t;
#pragma GCC diagnostic pop

/**
 * Use this type for an opaque memory, referened indirectly through a pointer
 */
typedef struct _lwm2m_object_res_opaque_t_ {
    uint16_t reserved_len;
    uint16_t used_len;
    uint8_t* data;
} OpaqueIndirect;

/**
 * Use this type for an opaque in-place memory
 */
#define OpaqueType(N) struct { \
    uint16_t reserved_len; \
    uint16_t used_len; \
    uint8_t data[N]; \
}

typedef void(*ExecutableType)(uint8_t * buffer,
                              int length);
#define IndirectReadType(TYPE,NAME) TYPE(*NAME)(void)
#define IndirectWriteType(TYPE,NAME) void(*NAME)(TYPE,int)

#define IndirectReadWriteType(TYPE) struct { \
    TYPE(*read)(void); \
    void(*write)(TYPE,int); \
}

/**
 * Internal structure. Use "OpaqueType(2) var_name;" instead.
 */
typedef struct _lwm2m_object_res_opaque_mem_t_ {
    uint16_t reserved_len;
    uint16_t used_len;
    uint8_t data[1];
} OpaqueType_t;


/**
 * @brief A callback that if provided will verify a write to an object ressource.
 * An example implementation:
 *
 * bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
 *     // First cast to the right instance struct.
 *     test_object_instance_t* i = (test_object_instance_t*)instance;
 *
 *     // if ressource 1 has a range from 0-128 return false if range is violated.
 *     if(changed_res_id==1 && i->test > 128) return false;
 *
 *     // You may react to a write here now. Like setting a GPIO or anything.
 *
 *     return true; // Usually accepts a write to an object
 * }
 *
 * @param instance       The object instance where the write takes place.
 * @param changed_res_id The id of the ressource that has changed.
 * @return Return false if the set value is not in range or is in any other means not
 *         not allowed on this object instance.
 */
typedef bool (*object_write_verify_cb_t)(lwm2m_list_t* instance, uint16_t changed_res_id);

/**
  * See documentation of lwm2m_object_create.
  */
typedef struct _lwm2m_object_meta_information_ {
    lwm2m_object_t obj;
    uint16_t instance_object_size;            ///< sizeof(instance_t)
    object_write_verify_cb_t write_verify_cb; ///< Verify or react to write in this callback. Optional.
    uint8_t ressources_len;                   ///< Of how many ressources does your object instance consists of.
    lwm2m_object_res_item_t ressources[1];     ///< Describe your instance_t / your ressources.
} lwm2m_object_meta_information_t;

#ifdef __cplusplus
#define STATIC_ASSERT static_assert
#elif __STDC_VERSION__ >= 201112L
#define STATIC_ASSERT _Static_assert
#else // For C89, C99
#define STATIC_ASSERT(a, b)
#endif

/**
 * Usually you define and only work with an lwm2m_object_t object.
 * If you use WakaamaNode object helper methods, additionally
 * to lwm2m_object_t there is also meta data required.
 *
 * Hereby an example for the following object definition is given:
 *
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  test |  1 |    R/W     |    No     |    Yes    | Integer | 0-128 |       |                       |
 *  exec |  2 |     E      |    No     |    Yes    |         |       |       |                       |
 *  dec  |  3 |    R/W     |    No     |    Yes    |  Float  |       |       |                       |
 *
 * You need a struct that may look like this:
 *
 * typedef struct {
 *    struct _prv_instance_ * next; // matches lwm2m_list_t::next
 *    uint16_t shortID;             // matches lwm2m_list_t::id
 *    uint8_t  test;   // For Res id 1
 *    double   dec;    // For Res id 3
 * } your_object_instance_t;
 *
 * Use OBJECT_META() and create a corresponding lwm2m object with an attached meta object like this:
 *
 * OBJECT_META(your_object_instance_t, test_object, test_object_write_verify_cb,
 *     {0, O_RES_RW,O_RES_UINT8 , offsetof(your_object_instance_t,test)},
 *     {1, O_RES_E ,0,          , 0},
 *     {2, O_RES_RW,O_RES_DOUBLE, offsetof(your_object_instance_t,dec)}
 * );
 *
 * You provide the object instance ("your_object_instance_t") and the variable name ("test_object")
 * for the object via the first and second argument.
 *
 * The third argument may be set to NULL. Otherwise set it to a callback method which is called on
 * a write to your object instance. You may react on a write in this method and you may deny the write if the new value
 * is not in range of your allowed values. See object_write_verify_cb_t for more information.
 *
 * The succeeding arguments describe the ressources of your object instances.
 *
 */
#define OBJECT_META_DEFINE(TYPENAME, ...) \
    typedef struct           \
    {                                                                \
        lwm2m_object_t obj;                                          \
        uint16_t instance_object_size;                               \
        object_write_verify_cb_t write_verify_cb;                    \
        uint8_t ressources_len;                                      \
        lwm2m_object_res_item_t ressources[(sizeof((lwm2m_object_res_item_t[]){__VA_ARGS__}) / sizeof (lwm2m_object_res_item_t))]; \
    } TYPENAME;

#define OBJECT_META_DECL(TYPENAME, variable_name) \
    TYPENAME variable_name;

#define OBJECT_META_INIT(object_instance_t, object_id, write_cb, RES) \
    {{NULL, object_id,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}, \
        sizeof(object_instance_t), write_cb, \
        sizeof((lwm2m_object_res_item_t[]){RES}) / sizeof (lwm2m_object_res_item_t), RES}

#define OBJECT_META_DECL_INIT(TYPENAME, variable_name, object_instance_t, object_id, write_cb, ...) \
    TYPENAME variable_name = OBJECT_META_INIT(object_instance_t, object_id, write_cb, __VA_ARGS__)

#define OBJECT_META(object_instance_t, variable_name, object_id, write_cb, ...) \
    typedef struct            \
    {                                                                \
        lwm2m_object_t obj;                                          \
        uint16_t instance_object_size;                               \
        object_write_verify_cb_t write_verify_cb;                    \
        uint8_t ressources_len;                                      \
        lwm2m_object_res_item_t ressources[sizeof((lwm2m_object_res_item_t[]){__VA_ARGS__}) / sizeof (lwm2m_object_res_item_t)];                        \
    } variable_name##_t;                        \
    static variable_name##_t variable_name =    \
    {{NULL, object_id,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}, sizeof(object_instance_t), write_cb, sizeof((lwm2m_object_res_item_t[]){__VA_ARGS__}) / sizeof (lwm2m_object_res_item_t), {__VA_ARGS__}}; \
    STATIC_ASSERT(sizeof(object_instance_t) > sizeof(uint8_t), "Object utils can only be used for object structs smaller than 256 bytes!"); \
    lwm2m_object_t* variable_name##P = (lwm2m_object_t*)&variable_name;

/**
 * @brief Initializes an lwm2m object, created with OBJECT_META().
 *
 * This will also add the object to the wakaama object registry. If the client
 * is already connected to a server, the server will be notified.
 *
 * Remove an object with lwm2m_remove_object(context, object_id) again.
 *
 * @param contextP   The wakaama context.
 * @param object   The wakaama lwm2m object with meta information attached.
 * @param allow_dynamic_instance_creation if you want a lwm2m server to be able to create new instances of your object.
 * @return The error code or COAP_NO_ERROR if no error.
 */
extern int lwm2m_add_initialize_object(lwm2m_context_t * contextP,
                                        lwm2m_object_t* object,
                                        bool allow_dynamic_instance_creation);

/**
 * @brief Add an instance to an object.
 * Ideally you do this before you connect to a server and before you call `lwm2m_add_initialize_object`.
 *
 * @param contextP   The wakaama context.
 * @param object The lwm2m_object.
 * @param instance An object instance. Only adds the instance if there is none with the same instance id.
 * @return The error code or COAP_NO_ERROR if no error.
 *      Returns COAP_IGNORE if instance with same id is already existing.
 */
int lwm2m_object_instance_add(lwm2m_context_t * contextP, lwm2m_object_t* object, lwm2m_list_t* instance);

/**
 * @brief Removes an instance from an object.
 *
 * Will inform a connected server of the updated object.
 *
 * @param contextP   The wakaama context.
 * @param object The lwm2m_object.
 * @param instance_id The instance id
 * @return The error code or COAP_NO_ERROR if no error.
 */
lwm2m_list_t* lwm2m_object_instance_remove(lwm2m_context_t * contextP, lwm2m_object_t* object, uint16_t instance_id);

#ifdef __cplusplus
}
#endif
