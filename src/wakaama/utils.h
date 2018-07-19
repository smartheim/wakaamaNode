#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"
#include "uri.h"
#include "data.h"
#include "server_object.h"

// defined in utils.c
lwm2m_data_type_t utils_depthToDatatype(uri_depth_t depth);
lwm2m_binding_t utils_stringToBinding(const uint8_t *buffer, size_t length);
lwm2m_media_type_t utils_convertMediaType(coap_content_type_t type);
int utils_isAltPathValid(const char * altPath);
int utils_stringCopy(char * buffer, size_t length, const char * str);
size_t utils_intToText(int64_t data, uint8_t * string, size_t length);
size_t utils_floatToText(double data, uint8_t * string, size_t length);
int utils_textToInt(const uint8_t * buffer, size_t length, int64_t * dataP);
int utils_textToFloat(const uint8_t * buffer, size_t length, double * dataP);

size_t utils_base64GetSize(size_t dataLen);
size_t utils_base64Encode(const uint8_t * dataP, size_t dataLen, uint8_t * bufferP, size_t bufferLen);


// Most compilers will optimize the following branched function
//#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})
//#define IS_BIG_ENDIAN (!(union { uint16_t u16; unsigned char c; }){ .u16 = 1 }.c)
#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

// Consider the byte order while copying
static inline void utils_int16Copy(void * dst,
                     const void * src)
{
    const bool is_big_endian = IS_BIG_ENDIAN;
    if (is_big_endian)
        memcpy(dst, src, 2);
    else {
        const uint16_t* orig = (const uint16_t*)src;
        *((uint16_t *)dst) =  (uint16_t)(*orig << 8) | (uint16_t)(*orig >> 8 );
    }
}

// Consider the byte order while copying
static inline void utils_int32Copy(void * dst,
                     const void * src)
{
    const bool is_big_endian = IS_BIG_ENDIAN;
    if (is_big_endian)
        memcpy(dst, src, 4);
    else {
        ((uint8_t *)dst)[0] = ((const uint8_t *)src)[3];
        ((uint8_t *)dst)[1] = ((const uint8_t *)src)[2];
        ((uint8_t *)dst)[2] = ((const uint8_t *)src)[1];
        ((uint8_t *)dst)[3] = ((const uint8_t *)src)[0];
    }
}

// Consider the byte order while copying
static inline void utils_doubleCopy(void * dst,
                     const void * src)
{
    const bool is_big_endian = IS_BIG_ENDIAN;
    if (is_big_endian)
        memcpy(dst, src, 8);
    else {
        ((uint8_t *)dst)[0] = ((const uint8_t *)src)[7];
        ((uint8_t *)dst)[1] = ((const uint8_t *)src)[6];
        ((uint8_t *)dst)[2] = ((const uint8_t *)src)[5];
        ((uint8_t *)dst)[3] = ((const uint8_t *)src)[4];
        ((uint8_t *)dst)[4] = ((const uint8_t *)src)[3];
        ((uint8_t *)dst)[5] = ((const uint8_t *)src)[2];
        ((uint8_t *)dst)[6] = ((const uint8_t *)src)[1];
        ((uint8_t *)dst)[7] = ((const uint8_t *)src)[0];
    }
}

#ifdef LWM2M_CLIENT_MODE
typedef struct _lwm2m_context_t lwm2m_context_t;

lwm2m_server_t * utils_findServer(lwm2m_context_t * contextP, void * fromSessionH);
lwm2m_server_t * utils_findBootstrapServer(lwm2m_context_t * contextP, void * fromSessionH);
#endif
