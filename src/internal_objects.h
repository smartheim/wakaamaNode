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
#include "wakaama/liblwm2m.h"
#include "lwm2m/c_objects.h"
#include "lwm2m/object_device.h"
#include "wakaama_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>

#define LWM2M_SECURITY_URI_ID                 0
#define LWM2M_SECURITY_BOOTSTRAP_ID           1
#define LWM2M_SECURITY_MODE_ID            2
#define LWM2M_SECURITY_PUBLIC_KEY_ID          3
#define LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID   4
#define LWM2M_SECURITY_SECRET_KEY_ID          5
#define LWM2M_SECURITY_SMS_SECURITY_ID        6
#define LWM2M_SECURITY_SMS_KEY_PARAM_ID       7
#define LWM2M_SECURITY_SMS_SECRET_KEY_ID      8
#define LWM2M_SECURITY_SMS_SERVER_NUMBER_ID   9
#define LWM2M_SECURITY_SHORT_SERVER_ID        10
#define LWM2M_SECURITY_HOLD_OFF_ID            11

/*
 *  Resources:
 *
 *          Name            | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Server URI              |  0 |            |  Single   |    Yes    | String  |         |       |
 *  Bootstrap Server        |  1 |            |  Single   |    Yes    | Boolean |         |       |
 *  Security Mode           |  2 |            |  Single   |    Yes    | Integer |   0-3   |       |
 *  Public Key or ID        |  3 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Server Public Key or ID |  4 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Secret Key              |  5 |            |  Single   |    Yes    | Opaque  |         |       |
 *  SMS Security Mode       |  6 |            |  Single   |    Yes    | Integer |  0-255  |       |
 *  SMS Binding Key Param.  |  7 |            |  Single   |    Yes    | Opaque  |   6 B   |       |
 *  SMS Binding Secret Keys |  8 |            |  Single   |    Yes    | Opaque  | 32-48 B |       |
 *  Server SMS Number       |  9 |            |  Single   |    Yes    | Integer |         |       |
 *  Short Server ID         | 10 |            |  Single   |    No     | Integer | 1-65535 |       |
 *  Client Hold Off Time    | 11 |            |  Single   |    Yes    | Integer |         |   s   |
 *
 */

typedef struct _security_instance_
{
    struct _security_instance_ * next;        // matches lwm2m_list_t::next
    uint16_t                     instanceId;  // matches lwm2m_list_t::id
    char                         uri[60];
    bool                         isBootstrap;
    uint8_t                      securityMode;
    #ifdef LWM2M_WITH_DTLS
    char *                       publicIdentity;
    uint16_t                     publicIdLen;
    char *                       serverPublicKey;
    uint16_t                     serverPublicKeyLen;
    char *                       secretKey;
    uint16_t                     secretKeyLen;
    #endif
    uint16_t                     shortID;
    uint32_t                     clientHoldOffTime;
} security_instance_t;

/*
 *  Resources:
 *
 *          Name         | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Short ID             |  0 |     R      |  Single   |    Yes    | Integer | 1-65535 |       |
 *  Lifetime             |  1 |    R/W     |  Single   |    Yes    | Integer |         |   s   |
 *  Default Min Period   |  2 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Default Max Period   |  3 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Disable              |  4 |     E      |  Single   |    No     |         |         |       |
 *  Disable Timeout      |  5 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Notification Storing |  6 |    R/W     |  Single   |    Yes    | Boolean |         |       |
 *  Binding              |  7 |    R/W     |  Single   |    Yes    | String  |         |       |
 *  Registration Update  |  8 |     E      |  Single   |    Yes    |         |         |       |
 *
 */
typedef struct _server_instance_
{
    struct _server_instance_ * next;   // matches lwm2m_list_t::next
    uint16_t    instanceId;            // matches lwm2m_list_t::id
    uint16_t    shortServerId;
    uint32_t    lifetime;
    uint32_t    defaultMinPeriod;
    uint32_t    defaultMaxPeriod;
    bool        storing;
    OpaqueType(4) binding;
    execFunc regUpdate;
} server_instance_t;

bool server_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

#define SERVER_OBJECT_RES \
    {0, O_RES_R,O_RES_UINT16 ,  offsetof(server_instance_t,shortServerId)}, \
    {1, O_RES_RW,O_RES_UINT32,  offsetof(server_instance_t,lifetime)}, \
    {2, O_RES_RW,O_RES_UINT32,  offsetof(server_instance_t,defaultMinPeriod)}, \
    {3, O_RES_RW,O_RES_UINT32,  offsetof(server_instance_t,defaultMaxPeriod)}, \
    {6, O_RES_RW,O_RES_BOOL  ,  offsetof(server_instance_t,storing)}, \
    {7, O_RES_RW,O_RES_STRING_PREALLOC,  offsetof(server_instance_t,binding)}, \
    {8, O_RES_E,0                     ,  offsetof(server_instance_t,regUpdate)}

OBJECT_META_DEFINE(server_object_t, SERVER_OBJECT_RES)

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
    time_t lwm2m_get_local_time(void);
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
    ,{RES_O_HARDWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, hardware_ver)} \
    ,{RES_O_SOFTWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, software_ver)}
#else
    #define DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
#endif


typedef struct _device_data_
{
    struct _security_instance_ * next;        // matches lwm2m_list_t::next
    uint16_t                     instanceId;  // matches lwm2m_list_t::id

    // Always include device info
    const char* manufacturer;  //  0
    const char* model_name;    //  1
    const char* serial_number; //  2
    const char* firmware_ver;  //  3
    const char* device_type;   // 17

    #ifdef LWM2M_DEVICE_INFO_WITH_TIME
    // Maximal "+HH:MM\0"
    OpaqueType(8) time_offset; // 14
    const char* timezone;      // 15
    #endif

    #ifdef LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
    const char* hardware_ver;  // 18
    const char* software_ver;  // 19
    #endif

    // Binding mode. Always "U".  16
    OpaqueType(2) binding;
} device_instance_t;

#define DEVICE_RES \
    {RES_O_MANUFACTURER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, manufacturer)} \
    ,{RES_O_MODEL_NUMBER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, model_name)} \
    ,{RES_O_SERIAL_NUMBER, O_RES_R , O_RES_STRING, offsetof(device_instance_t, serial_number)} \
    ,{RES_O_FIRMWARE_VERSION, O_RES_R , O_RES_STRING, offsetof(device_instance_t, firmware_ver)} \
    ,{RES_M_REBOOT, O_RES_E,0, 0} \
    ,{RES_O_FACTORY_RESET, O_RES_E,0, 0} \
    DEVICE_INFO_WITH_BATTERY \
    DEVICE_INFO_WITH_ERRCODE \
    ,{RES_O_CURRENT_TIME, O_RES_R , O_RES_INT64, 0} \
    ,{RES_M_BINDING_MODES, O_RES_RW , O_RES_STRING_PREALLOC, offsetof(device_instance_t, binding)} \
    DEVICE_INFO_WITH_TIME \
    ,{ RES_O_DEVICE_TYPE, O_RES_R , O_RES_STRING, offsetof(device_instance_t, device_type) } \
    DEVICE_INFO_WITH_ADDITIONAL_VERSIONS \
    DEVICE_INFO_WITH_BATTERY \
    DEVICE_INFO_WITH_MEMINFO

OBJECT_META_DEFINE(device_object_t, DEVICE_RES)

// OBJECT_META(device_instance_t, device_object, 3, NULL,DEVICE_RES)

typedef struct _lwm2m_client_context_t_ lwm2m_client_context_t;

void init_security_object(lwm2m_client_context_t* ctx);
void init_server_object(lwm2m_client_context_t* ctx);
void init_device_object(lwm2m_client_context_t* ctx);

/**
 * If you plan to implement a read-callback method, you need to be prepared for the case where the
 * server asks for all object ressources. Use this method to allocate memory and assign ressource
 * IDs to the array lwm2m_data_t elements.
 *
 * @param dataArrayP This method will allocate memory that needs needs to be freed with lwm2m_free() again after use.
 * @param metaP The lwm2m object meta information.
 * @return Returns the count of ressources in metaP and therefore allocated lwm2m_data_t objects of dataArrayP or -1 if an error occured (no memory could be acquired). Can return 0 if there are no readable ressources in the object described by the meta object.
 */
int lwm2m_object_prepare_full_response(lwm2m_data_t** dataArrayP, lwm2m_object_meta_information_t* metaP);

/**
 * Assign/transform a lwm2m_object_res_item_t to a lwm2m_data_t structure.
 * Uses lwm2m_data_encode_* methods.
 *
 * @param destination The destination lwm2m_data_t
 * @param resP A meta ressource description (one of lwm2m_object_meta_information_t::ressources)
 * @param instanceP An lwm2m object instance
 */
uint8_t lwm2m_object_assign_single_value(lwm2m_data_t* destination, lwm2m_object_res_item_t* resP, void* instanceP);

/**
 * Looks up a specific security object instance.
 *
 * @param security_instance_id The security object instance id (same as server object instance id).
 * @return Returns a security object instance for the given instance ID or NULL.
 */
security_instance_t* lwm2m_get_security_object(lwm2m_context_t *contextP, uint16_t security_instance_id);

/**
 * Erases public/private keys, certificates etc from the given security instance
 *
 * @param securityInstance A security instance
 */
void internal_erase_security_params(security_instance_t * securityInstance);

#ifdef __cplusplus
}
#endif
