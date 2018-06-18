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

#include <stdint.h>

// Configures the lwm2m device object instance
#include "wakaama_config.h"
#include "lwm2m/objects.h"

#ifdef __cplusplus
extern "C" {
#endif

// Resource Id's:
#define RES_O_MANUFACTURER          0
#define RES_O_MODEL_NUMBER          1
#define RES_O_SERIAL_NUMBER         2
#define RES_O_FIRMWARE_VERSION      3
#define RES_M_REBOOT                4
#define RES_O_FACTORY_RESET         5
#define RES_O_AVL_POWER_SOURCES     6
#define RES_O_POWER_SOURCE_VOLTAGE  7
#define RES_O_POWER_SOURCE_CURRENT  8
#define RES_O_BATTERY_LEVEL         9
#define RES_O_MEMORY_FREE           10
#define RES_M_ERROR_CODE            11
#define RES_O_RESET_ERROR_CODE      12
#define RES_O_CURRENT_TIME          13
#define RES_O_UTC_OFFSET            14
#define RES_O_TIMEZONE              15
#define RES_M_BINDING_MODES         16
#define RES_O_DEVICE_TYPE           17
#define RES_O_HARDWARE_VERSION      18
#define RES_O_SOFTWARE_VERSION      19
#define RES_O_BATTERY_STATUS        20
#define RES_O_MEMORY_TOTAL          21

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
    OpaqueType(7) time_offset; // 14
    const char* timezone;      // 15
    #endif

    #ifdef LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
    const char* hardware_ver;  // 18
    const char* software_ver;  // 19
    #endif

    // Binding mode. Always "U".  16
    OpaqueType(2) binding;
} device_instance_t;


#ifdef LWM2M_DEVICE_WITH_REBOOT
extern void lwm2m_reboot(void);
#endif

#ifdef LWM2M_DEVICE_WITH_FACTORY_RESET
extern void lwm2m_factory_reset(void);
#endif

/**
 * @brief Return the device information object.
 * Change this object before you connect to a server.
 * @return
 */
device_instance_t * lwm2m_device_data_get(void);

/**
 * @brief Call this if you have changed a ressource in the device_instance_t object.
 * You only have to do this after you have connected to a lwm2m server.
 *
 * To change a device information (version number etc), do the following:
 * - device_instance_t* device = lwm2m_device_data_get();
 * - device->firmware_ver = "1.2";
 * - lwm2m_device_res_has_changed(RES_O_FIRMWARE_VERSION);
 *
 * Some device information are obtained by calling a function.
 * The battery level is an example.
 * Just call lwm2m_device_res_has_changed(RES_O_BATTERY_LEVEL) periodically or after
 * the battery level has changed for a reason and the runtime will retrieve the new data by
 * calling lwm2m_get_bat_level().
 *
 * @param res_id The ressource id of the value you have changed in device_instance_t.
 */
void lwm2m_device_res_has_changed(uint16_t res_id);


#ifdef __cplusplus
}
#endif
