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

/*
 * This object is single instance only, and is mandatory to all LWM2M devices.
 * It describe the device such as its manufacturer, model, etc...
 *
 * Some of the optional resources are implemented here as well and can be configured
 * via a wakaama_config.h file.
 */

#include "wakaama/liblwm2m.h"
#include "lwm2m/c_objects.h"
#include "lwm2m/c_connect.h"
#include "lwm2m/object_device.h"
#include "internal_objects.h"

// Configures the lwm2m device object instance
#include "wakaama_config.h"

#include <string.h>
#include <ctype.h>

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
                                 lwm2m_object_t * objectP,
                               lwm2m_context_t * contextP)
{
    (void)contextP;
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
            #ifdef LWM2M_DEVICE_INFO_WITH_TIME
            case RES_O_CURRENT_TIME:
                lwm2m_data_encode_int((int64_t)lwm2m_get_local_time(), dataP);
                break;
            #endif
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
                        lwm2m_context_t * contextP,
                        lwm2m_object_t * objectP)
{
    (void)contextP;
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

void init_device_object(lwm2m_client_context_t* ctx) {
    OBJECT_META (device_instance_t,device_object,3,NULL,DEVICE_RES);
    memcpy(&ctx->deviceObject, device_objectP,sizeof(ctx->deviceObject));
     ctx->deviceObject.obj.objID = 3;
    ctx->deviceObject.obj.instanceList = (lwm2m_list_t*)&ctx->deviceInstance;
    ctx->deviceObject.obj.readFunc = prv_device_read;
    ctx->deviceObject.obj.executeFunc = prv_device_execute;
    ctx->deviceInstance.binding.data[0] = 'U';
    ctx->deviceInstance.binding.reserved_len = 2;
    #ifdef LWM2M_DEVICE_INFO_WITH_TIME
    ctx->deviceInstance.time_offset.reserved_len = 7;
    #endif
}

inline void lwm2m_device_res_has_changed(lwm2m_context_t * contextP, uint16_t res_id) {
    lwm2m_uri_t uri = {9,3,0,res_id};
    lwm2m_resource_value_changed(contextP, &uri);
}
