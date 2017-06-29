#pragma once

#include <stdint.h>

// Configures the lwm2m device object instance
#include "wakaama_config.h"

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
    char time_offset[7];       // 14
    const char* timezone;      // 15
    #endif

    #ifdef LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS
    const char* hardware_ver;  // 18
    const char* software_ver;  // 19
    #endif

    // Binding mode. Always "U".  16
    char binding[2];
} device_instance_t;

#ifdef __cplusplus
}
#endif
