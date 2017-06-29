#ifndef LWM2M_CLIENT_MODE
    #define LWM2M_CLIENT_MODE
#endif
#ifndef LWM2M_LITTLE_ENDIAN
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define LWM2M_LITTLE_ENDIAN
    #endif
#endif