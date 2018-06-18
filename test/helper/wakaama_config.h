// Enables the wifi object where you may provide information about the wifi strength, connected ssid etc.
#define LWM2M_DEV_INFO_WIFI_METRICS

// Allows to perform a reboot of the device. Implement lwm2m_reboot() for this to work.
#define LWM2M_DEVICE_WITH_REBOOT

// Allows to perform a factory reset. Implement lwm2m_factory_reset() for this to work.
// In this method you should erase all user memory, connection setups and so on.
#define LWM2M_DEVICE_WITH_FACTORY_RESET

// Implement lwm2m_get_bat_level() and lwm2m_get_bat_status().
#define LWM2M_DEVICE_INFO_WITH_BATTERY

// Implement lwm2m_get_free_mem() and lwm2m_get_total_mem().
#define LWM2M_DEVICE_INFO_WITH_MEMINFO

// Implement lwm2m_get_last_error() and lwm2m_reset_last_error().
#define LWM2M_DEVICE_INFO_WITH_ERRCODE

// Implement lwm2m_gettime() and update the fields  **timezone** and **time_offset**
// of the device information object.
#define LWM2M_DEVICE_INFO_WITH_TIME

// Adds a **hardware_ver** and a **software_ver** c-string field.
#define LWM2M_DEVICE_INFO_WITH_ADDITIONAL_VERSIONS

// Enables the firmware update mechanism.
#define LWM2M_FIRMWARE_UPGRADES

// Enable DTLS support
#define LWM2M_WITH_DTLS
