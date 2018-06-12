/*
 * This object is single instance only, and is mandatory to all LWM2M devices.
 * It describe the device such as its manufacturer, model, etc...
 *
 * Some of the optional resources are implemented here as well and can be configured
 * via a config_wakaama.h file.
 *
 */

#include "wakaama/liblwm2m.h"
#include "internal.h"
#include "lwm2m_objects.h"
#include "object_device.h"
#include "lwm2m_connect.h"

// Configures the lwm2m device object instance
#include "wakaama_config.h"

#include <string.h>
#include <ctype.h>

#ifdef LWM2M_DEVICE_INFO_WITH_BATTERY
    // uint8_t battery_level;  //  9
    // uint8_t battery_status; // 20
    uint8_t lwm2m_get_bat_level(void);
    uint8_t lwm2m_get_bat_status(void);

    #define DEVICE_INFO_WITH_BATTERY \
    ,{RES_O_BATTERY_LEVEL, O_RES_R | O_RES_E , O_RES_UINT8, 0} \
    ,{RES_O_BATTERY_STATUS, O_RES_R | O_RES_E , O_RES_UINT8, 0}
#else
    #define DEVICE_INFO_WITH_BATTERY
#endif

#ifdef LWM2M_DEVICE_INFO_WITH_MEMINFO
    // int64_t free_memory;    // 10
    // int64_t total_memory;   // 21
    int64_t lwm2m_get_free_mem(void);
    int64_t lwm2m_get_total_mem(void);

    #define DEVICE_INFO_WITH_MEMINFO \
    ,{RES_O_MEMORY_FREE,  O_RES_R | O_RES_E , O_RES_INT64, 0} \
    ,{RES_O_MEMORY_TOTAL, O_RES_R | O_RES_E , O_RES_INT64, 0}

#else
    #define DEVICE_INFO_WITH_MEMINFO
#endif

#ifdef LWM2M_DEVICE_INFO_WITH_ERRCODE
    // int64_t error;          // 11
    // RES_O_RESET_ERROR_CODE     12
    // RES_O_RESET_ERROR_CODE
    // Implement these functions:
    int64_t lwm2m_get_last_error(void);
    void lwm2m_reset_last_error(void);
    #define DEVICE_INFO_WITH_ERRCODE \
    ,{RES_M_ERROR_CODE, O_RES_R | O_RES_E , O_RES_INT64, 0} \
    ,{RES_O_RESET_ERROR_CODE, O_RES_E,0 , 0}
#else
    #define DEVICE_INFO_WITH_ERRCODE
#endif

#ifdef LWM2M_DEVICE_INFO_WITH_TIME
    // time_offset[7];       // 14
    // char* timezone;      // 15
    // Maximal "+HH:MM\0"
    #define DEVICE_INFO_WITH_TIME \
    ,{RES_O_UTC_OFFSET, O_RES_R , O_RES_STRING_PREALLOC, offsetof(device_instance_t, time_offset)} \
    ,{RES_O_TIMEZONE, O_RES_R , O_RES_STRING, offsetof(device_instance_t, timezone)}
#else
    #define DEVICE_INFO_WITH_TIME
#endif

#ifdef LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
     // 18 and 19
    #define DEVICE_INFO_WITH_ADDITIONAL_VERSIONS \
    ,{RES_O_HARDWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, hardware_ver)}, \
    { RES_O_SOFTWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, software_ver) }
#else
    #define DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
#endif

OBJECT_META(device_instance_t, device_object, 3, NULL,
    {RES_O_MANUFACTURER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, manufacturer)},
    {RES_O_MODEL_NUMBER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, model_name)},
    {RES_O_SERIAL_NUMBER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, serial_number)},
    {RES_O_FIRMWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, firmware_ver)},
    {RES_M_REBOOT, O_RES_E,0, 0},       // reboot 4
    {RES_O_FACTORY_RESET, O_RES_E,0, 0} // factory reset 5
    DEVICE_INFO_WITH_BATTERY
    DEVICE_INFO_WITH_ERRCODE
    ,{RES_O_CURRENT_TIME, O_RES_R , O_RES_INT64, 0} // Implement: lwm2m_gettime() 13
    ,{RES_M_BINDING_MODES, O_RES_RW , O_RES_STRING_PREALLOC, offsetof(device_instance_t, binding)}
    DEVICE_INFO_WITH_TIME
    //  Binding mode. Always "U".  16
    ,{ RES_O_DEVICE_TYPE, O_RES_R , O_RES_STRING, offsetof(device_instance_t, device_type) } // 17
    DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
    DEVICE_INFO_WITH_BATTERY
    DEVICE_INFO_WITH_MEMINFO
) // End OBJECT_META


static device_instance_t device_instance = {0};

inline static lwm2m_object_res_item_t* prv_find_ressource(lwm2m_object_meta_information_t* metaP, unsigned res_id)
{
    lwm2m_object_res_item_t* resP = 0;
    for (int j=0; j < metaP->ressources_len; ++j)
    {
        if (metaP->ressources[j].ressource_id == res_id) {
            resP = &(metaP->ressources[j]);
            break;
        }
    }
    return resP;
}

/**
 * Behaves similar to the generic prv_read() of wakaama_object_utils.h,
 * but intercepts the ressource ids, where we need to inquire a function
 * first to get the result value.
 */
static uint8_t prv_device_read(uint16_t instanceId,
                                 int * numDataP,
                                 lwm2m_data_t ** dataArrayP,
                                 lwm2m_object_t * objectP)
{
    lwm2m_list_t* instanceP = lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = (lwm2m_object_meta_information_t*)objectP;

    // is the server asking for the full instance ?
    if (*numDataP == 0)
    {
        *numDataP = lwm2m_object_prepare_full_response(dataArrayP, metaP);
    }


    for (int i = 0 ; i < *numDataP ; i++)
    {
        lwm2m_data_t* dataP = &(*dataArrayP)[i];
        const unsigned res_id = dataP->id;

        lwm2m_object_res_item_t* resP = prv_find_ressource(metaP, res_id);

        if (!resP)
            return COAP_404_NOT_FOUND;

        if (!(resP->access & O_RES_R))
            return COAP_405_METHOD_NOT_ALLOWED;

        uint8_t result;
        switch (res_id) {
            #ifdef LWM2M_DEVICE_INFO_WITH_BATTERY
            case RES_O_BATTERY_LEVEL:
                lwm2m_data_encode_int(lwm2m_get_bat_level(), dataP);
                break;
            case RES_O_BATTERY_STATUS:
                lwm2m_data_encode_int(lwm2m_get_bat_status(), dataP);
                break;
            #endif
            #ifdef LWM2M_DEVICE_INFO_WITH_MEMINFO
            case RES_O_MEMORY_FREE:
                lwm2m_data_encode_int(lwm2m_get_free_mem(), dataP);
                break;
            case RES_O_MEMORY_TOTAL:
                lwm2m_data_encode_int(lwm2m_get_total_mem(), dataP);
                break;
            #endif
            #ifdef LWM2M_DEVICE_INFO_WITH_ERRCODE
            case RES_M_ERROR_CODE:
                lwm2m_data_encode_int(lwm2m_get_last_error(), dataP);
                break;
            #endif
            case RES_O_CURRENT_TIME:
                lwm2m_data_encode_int((int64_t)lwm2m_gettime(), dataP);
                break;
            default:
                if (resP->struct_member_offset==0)
                    return COAP_405_METHOD_NOT_ALLOWED;
                result = lwm2m_object_assign_single_value(dataP, resP, instanceP);
                if (result != COAP_205_CONTENT)
                    return result;
        } // end switch
    } // end for
    return COAP_205_CONTENT;
}


uint8_t prv_device_execute(uint16_t instanceId,
                        uint16_t resourceId,
                        uint8_t * buffer,
                        int length,
                        lwm2m_object_t * objectP)
{
    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = (lwm2m_object_meta_information_t*)objectP;

    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    lwm2m_object_res_item_t* resP = prv_find_ressource(metaP, resourceId);
    if (!resP)
        return COAP_404_NOT_FOUND;

    if (!(resP->access & O_RES_E))
        return COAP_405_METHOD_NOT_ALLOWED;

    switch(resP->ressource_id)
    {
        #ifdef LWM2M_DEVICE_WITH_REBOOT
        case RES_M_REBOOT:
            lwm2m_reboot();
            return COAP_205_CONTENT;
        #endif
        #ifdef LWM2M_DEVICE_WITH_FACTORY_RESET
        case RES_O_FACTORY_RESET:
            lwm2m_factory_reset();
            return COAP_205_CONTENT;
        #endif
    }
    return COAP_405_METHOD_NOT_ALLOWED;
}


device_instance_t * lwm2m_device_data_get() {
    return &device_instance;
}

lwm2m_object_t *init_device_object() {
    device_object->instanceList = (lwm2m_list_t*)&device_instance;
    device_object->readFunc = prv_device_read;
    device_object->executeFunc = prv_device_execute;
    device_instance.binding.data[0] = 'U';
    device_instance.binding.reserved_len = 2;
    #ifdef LWM2M_DEVICE_INFO_WITH_TIME
    device_instance.time_offset.reserved_len = 7;
    #endif
    return device_object;
}

void lwm2m_device_res_has_changed(uint16_t res_id) {
    lwm2m_uri_t uri;
    uri.flag = 0;
    uri.objectId = 3; // device
    uri.instanceId = 0;
    uri.resourceId = res_id;
    lwm2m_resource_value_changed(lwm2m_client_get_context(), &uri);
}
