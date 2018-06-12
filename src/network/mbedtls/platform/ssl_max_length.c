 #if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#ifdef ESP8266
unsigned int max_content_len=512;
#else
unsigned int max_content_len=4048;
#endif
