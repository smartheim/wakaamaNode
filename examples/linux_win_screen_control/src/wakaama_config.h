#ifndef LWM2M_LITTLE_ENDIAN
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define LWM2M_LITTLE_ENDIAN
    #endif
#endif
// Client mode, posix, with json and dtls
#define LWM2M_CLIENT_MODE 1
#define POSIX 1
#define LWM2M_SUPPORT_JSON 1
#define LWM2M_WITH_DTLS 1
// Enable logs
#define LWM2M_WITH_LOGS 1
// Enable additional features
#define LWM2M_FIRMWARE_UPGRADES 1
#define LWM2M_DEVICE_INFO_WITH_TIME 1
