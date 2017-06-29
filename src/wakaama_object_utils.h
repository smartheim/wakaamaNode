#pragma once
#include "wakaama/liblwm2m.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef char* (*readFunc) (void);
typedef void  (*execFunc) (uint8_t * buffer, int length);

typedef enum _lwm2m_object_util_type_ {
    O_RES_BOOL   = 1, ///< A boolean value
    O_RES_DOUBLE = 2, ///< A floating point decimal value
    O_RES_INT8   = 3, ///< Int with range [-128,127]
    O_RES_UINT8  = 4, ///< Int with range [0,255]
    O_RES_INT16  = 5, ///< Int with range [-32000,32000]
    O_RES_UINT16 = 6, ///< Int with range [0,65500]
    O_RES_INT32  = 7, ///< Int with range [-2^31,2^31-1]
    O_RES_UINT32 = 8, ///< Int with range [0, 2^32-1]
    O_RES_INT64  = 9, ///< Int with range [-2^63, 2^63-1]
    O_RES_STRING          = 10, ///< free + strdub for an entry
    O_RES_STRING_STATIC   = 11, ///< assign pointer, no free
    O_RES_STRING_PREALLOC = 12, ///< preallocated space. In the write verify cb make sure the incoming string fits into the allocated space.
    O_RES_OPAQUE          = 13, ///< free + memcpy with length for an antry
    O_RES_OPAQUE_STATIC   = 14 ///< assign pointer and length, no free
} lwm2m_object_util_type_t;

typedef enum _lwm2m_object_util_access_ {
    O_RES_R  = (1 << 4), ///< Read only access
    O_RES_W  = (1 << 5), ///< Write only access
    O_RES_RW = (1 << 4)|(1 << 5), ///< Read/Write only access
    O_RES_E  = (1 << 6), ///< Execute only
    O_RES_RWE = (1 << 4)|(1 << 5)|(1 << 6), ///< Read/Write and executable ressource
    O_RES_FUNCTION = (1 << 7) ///< Executable and a function is provided
} lwm2m_object_util_access_t;

typedef struct _lwm2m_object_res_item_t_ {
    uint16_t ressource_id;
    uint8_t type_and_access;
    uint8_t struct_member_offset;
} lwm2m_object_res_item_t;


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
    uint16_t instance_object_size;            ///< sizeof(instance_t) otherwise.
    object_write_verify_cb_t write_verify_cb; ///< Verify or react to write in this callback. Optional.
    uint8_t ressources_len;                   ///< Of how many ressources does your ressource instances consists of.
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
  * See documentation of lwm2m_object_create.
  */
#define OBJECT_META(object_instance_t, variable_name, write_cb, ...) \
    typedef struct            \
    {                                                                \
        uint16_t instance_object_size;                               \
        object_write_verify_cb_t write_verify_cb;                    \
        uint8_t ressources_len;                                      \
        lwm2m_object_res_item_t ressources[sizeof((lwm2m_object_res_item_t[]){__VA_ARGS__}) / sizeof (lwm2m_object_res_item_t)];                        \
    } lwm2m_object_meta_information_custom_t;                        \
    static lwm2m_object_meta_information_custom_t meta_object =    \
    {sizeof(object_instance_t), write_cb, sizeof((lwm2m_object_res_item_t[]){__VA_ARGS__}) / sizeof (lwm2m_object_res_item_t), {__VA_ARGS__}}; \
    STATIC_ASSERT(sizeof(object_instance_t) > sizeof(uint8_t), "Object utils can only be used for object structs smaller than 256 bytes!"); \
    lwm2m_object_meta_information_t* variable_name = (lwm2m_object_meta_information_t*)&meta_object;

/**
  * Usually you define and only work with an lwm2m_object_t object.
  * If you use these lwm2m object helper methods, additionally
  * to lwm2m_object_t there is also meta data required.
  */
typedef struct __attribute__((__packed__))
{
    lwm2m_object_t obj;
    lwm2m_object_meta_information_t *meta;
} lwm2m_object_with_meta_t;

STATIC_ASSERT(sizeof(lwm2m_object_with_meta_t)==sizeof(lwm2m_object_t)+sizeof(lwm2m_object_meta_information_t*),
              "lwm2m_object_with_meta_t packing failed. The object meta data pointer have to follow the object data immediatelly");

/**
 * @brief Free an lwm2m object, you have created with {@see lwm2m_object_create}.
 * The instances which are connected to this object are not freed!
 * @param objectP The object. May not be NULL.
 */
void lwm2m_object_free(lwm2m_object_t * objectP);

/**
 * @brief Helps you with creating a new lwm2m object.
 *
 * You may create a custom object or any predefined objects, except
 * server and client management objects with id <=7.
 * An lwm2m object consists of an object id and none, one or more object instances. Wakaama
 * allows you to add user data to an object by using the object->userdata member.
 *
 * A lwm2m object instance consists of one ore more ressources identified by their ressource ids.
 * A ressource may be an uint8, int8, uint16, int16, uint32, int32, uint64, int64, double, c-string.
 * If you implement any object with an id registered at
 * http://technical.openmobilealliance.org/Technical/technical-information/omna/lightweight-m2m-lwm2m-object-registry,
 * your object instances have to provide all of the defined ressources.
 *
 * Usually you create a struct that consists of all needed ressources, representing an instance.
 * Please be aware that your object instance
 * have to "inherit" lwm2m_list_t::next and lwm2m_list_t::id like in the following example:
 *
 * typedef struct {
 *    struct _prv_instance_ * next; // matches lwm2m_list_t::next
 *    uint16_t shortID;             // matches lwm2m_list_t::id
 *    ... Your members are defined here...
 * } your_object_instance_t;
 *
 * To allow wakaama to
 * - query from your object instances,
 * - write to it and
 * - execute on it
 * you have to provide a machine readable description. You do this by definining a
 * lwm2m_object_meta_information_t. Hereby an example for the following object definition is given:
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
 * Use OBJECT_META() and create a corresponding meta object like this:
 *
 * OBJECT_META(your_object_instance_t, test_object_meta, test_object_write_verify_cb,
 *     {0, O_RES_RW|O_RES_UINT8 , offsetof(your_object_instance_t,test)},
 *     {1, O_RES_E                   , 0},
 *     {2, O_RES_RW|O_RES_DOUBLE, offsetof(your_object_instance_t,dec)}
 * );
 *
 * You provide the object instance structure and the variable name for the meta object via
 * the first and second argument.
 *
 * The third argument may be set to NULL. Otherwise set it to a callback method which is called on
 * a write to your object instance. You may react on a write in this method and you may deny the write if the new value
 * is not in range of your allowed values. See object_write_verify_cb_t for more information.
 *
 * The following arguments describe the ressources of your object instances. Each entry consists of three values:
 * 1) The id of the ressource
 * 2) Describes the access (O_RES_RW for read/write etc) and the type (O_RES_UINT8 for uint8 etc).
 * Additionally to the type the O_RES_FUNCTION flag can be set for read only ressource items. The value will not be read
 * from the struct but a function call result is used instead.
 * 3) Points to the position of the related member in the struct or 0 for execute-only ressources.
 *
 * If you have an OPAQUE field in your struct you have to define it as a pointer, directly followed by a size_t struct member,
 * where the length information is stored. An example:
 *
 * typedef struct {
 *    struct _prv_instance_ * next; // matches lwm2m_list_t::next
 *    uint16_t shortID;             // matches lwm2m_list_t::id
 *    uint8_t*  opaque_field;
 *    size_t    opaque_field_length;  // The length of the opaque_field buffer.
 * } your_object_instance_t;
 *
 * For OPAQUE fields and STRING fields exists normal, _STATIC and for strings additionaly _PREALLOC variants.
 * On each assignment to the normal variant, a series of free(), malloc() and strcpy() will be executed.
 * For the _STATIC variant the incoming data pointer will be assigned to the member variable directly and you have to
 * take care, that the assigned data is valid as long as that object instance is alive.
 * The _PREALLOC variant
 *
 * To add an instance use something like:
 * object->obj.instanceList = lwm2m_list_add(object->obj.instanceList, instanceP);
 *
 * @param context   The wakaama context.
 * @param object_id The object id. Ids below 7 are forbidden. Ids >=10241 are for custom objects.
 *                  Look at http://technical.openmobilealliance.org/Technical/technical-information/omna/lightweight-m2m-lwm2m-object-registry
 *                  for predefined object definitions for ids 8-2047.
 * @param allow_dynamic_instance_creation if you want a lwm2m server to be able to create new instances of your object.
 * @param meta_information
 * @return
 */
extern lwm2m_object_t* lwm2m_object_create(
                                    uint16_t object_id,
                                    bool allow_dynamic_instance_creation,
                                    lwm2m_object_meta_information_t* meta_information);

/**
 * @brief Similar to lwm2m_object_create
 * Instead of allocating an object on the heap for you like in lwm2m_object_create, with this method
 * you have to provide a pointer to the memory where the object data should be stored.
 * @param object The object memory, doesn't need to be initialized.
 * @param object_id The object ID (coap ressource id)
 * @param allow_dynamic_instance_creation Allows or disallows the use of lwm2m_object_instances_add(). Heap memory will be used.
 * @param meta_information The objects meta data.
 */
void lwm2m_object_create_preallocated(lwm2m_object_with_meta_t* object,
                                      uint16_t object_id,
                                      bool allow_dynamic_instance_creation,
                                      lwm2m_object_meta_information_t* meta_information);

/**
 * @brief Add an instance to an object.
 * Ideally you do this before you have connected to a server. Otherwise you
 * have to notify the server with lwm2m_update_registration(..., true) about the changed object.
 * @param object The lwm2m_object.
 * @param instance One or more linked instances.
 */
void lwm2m_object_instances_add(lwm2m_object_t* object, lwm2m_list_t* instance);

#ifdef __cplusplus
}
#endif
