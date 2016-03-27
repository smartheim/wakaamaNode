/*
 * This object is single instance only, and is mandatory to all LWM2M device as it describe the object such as its
 * manufacturer, model, etc...
 *
 * Here we implement only some of the optional resources.
 *
 */

#include "liblwm2m.h"
#include "wakaama_client_internal.h"
#include "wakaama_object_utils.h"
#include "wakaama_device_data.h"

#include <string.h>
#include <ctype.h>

#define PRV_MANUFACTURER      "Open Mobile Alliance"
#define PRV_MODEL_NUMBER      "Lightweight M2M Client"
#define PRV_BINDING_MODE      "U"



static lwm2m_object_with_meta_t device_object = {0};
static device_instance_t device_instance = {0};

OBJECT_META(device_instance_t, device_object_meta, NULL,
        {O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,manufacturer)},
            {O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,model_name)},
            {O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,serial_number)},
            {O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,firmware_ver)},
            {O_RES_E, 0}, // reboot 4
            {O_RES_E, 0}, // factory reset 5
            {0,0},{0,0},{0,0}, // power 6-8

            #ifdef LWM2M_DEVICE_INFO_WITH_BATTERY
                // uint8_t battery_level;  //  9
            // - uint8_t lwm2m_get_bat_level()
            {O_RES_RW|O_RES_FUNCTION|O_RES_UINT8,  0},
            #else
            {0,0},
            #endif

            #ifdef LWM2M_DEVICE_INFO_WITH_MEMINFO
            // int64_t free_memory;    // 10
            // - int64_t lwm2m_get_free_mem()
            {O_RES_RW|O_RES_FUNCTION|O_RES_INT64,  0},
            #else
            {0,0},
            #endif

            #ifdef LWM2M_DEVICE_INFO_WITH_ERRCODE
            // int64_t error;          // 11
            // RES_O_RESET_ERROR_CODE     12
            // Implement these functions:
            // - int64_t lwm2m_get_last_error()
            // - void lwm2m_reset_last_error()
            {O_RES_RW|O_RES_FUNCTION|O_RES_INT64,  0},
            {O_RES_E, 0}, // RES_O_RESET_ERROR_CODE
            #else
            {0,0},{0,0},
            #endif

            {O_RES_RW|O_RES_FUNCTION|O_RES_INT64,  0}, // Implement: lwm2m_gettime() 13

            #ifdef LWM2M_DEVICE_INFO_WITH_TIME
            // Maximal "+HH:MM\0"
            {O_RES_RW|O_RES_STRING_PREALLOC,  offsetof(device_instance_t,time_offset)}, // time_offset[7];       // 14
            {O_RES_RW|O_RES_STRING,  offsetof(device_instance_t,timezone)}, // char* timezone;      // 15
            #else
            {0,0},{0,0},
            #endif

            {O_RES_RW|O_RES_STRING_PREALLOC,  offsetof(device_instance_t,binding)}, // Binding mode. Always "U".  16
            {O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,device_type)} // 17

            #ifdef LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
            ,{O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,hardware_ver)} // 18
            ,{O_RES_R|O_RES_STRING_STATIC ,  offsetof(device_instance_t,software_ver)}  // 19
            #else
            ,{0,0},{0,0}
            #endif

            #ifdef LWM2M_DEVICE_INFO_WITH_BATTERY
                // uint8_t battery_status; // 20
            // - uint8_t lwm2m_get_bat_status()
            ,{O_RES_RW|O_RES_FUNCTION|O_RES_UINT8,  0}
            #else
            ,{0,0}
            #endif

            #ifdef LWM2M_DEVICE_INFO_WITH_MEMINFO
            // int64_t total_memory;   // 21
            // - int64_t lwm2m_get_total_mem()
            ,{O_RES_RW|O_RES_FUNCTION|O_RES_UINT8,  0}
            #else
            ,{0,0}
            #endif
);

static uint8_t object_execute_cb(uint16_t instanceId,
                        uint16_t resourceId,
                        uint8_t * buffer,
                        int length,
                        lwm2m_object_t * objectP)
{
    server_instance_t * targetP;

    targetP = (server_instance_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == targetP)
        return COAP_404_NOT_FOUND;

    switch (resourceId)
    {
    case LWM2M_SERVER_DISABLE_ID:
    case LWM2M_SERVER_UPDATE_ID:
        // executed in core, if COAP_204_CHANGED is returned
        return COAP_204_CHANGED;
    default:
        return COAP_405_METHOD_NOT_ALLOWED;
    }
}

device_instance_t * lwm2m_device_data_get() {
    return &device_instance;
}

lwm2m_object_t * init_device_object()
{
    lwm2m_object_create_preallocated(&device_object, 3, false, &device_object_meta);
    device_object.obj.instanceList = lwm2m_list_add(device_object.obj.instanceList, (lwm2m_list_t*)&device_instance);
    device_instance.binding[0] = 'U';
    return (lwm2m_object_t*)&device_object;
}
