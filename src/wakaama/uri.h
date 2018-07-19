#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "er-coap-13/er-coap-13.h"

/*
 * URI
 *
 * objectId is always set
 * instanceId or resourceId are set according to the flag bit-field
 *
 */

#define LWM2M_MAX_ID   ((uint16_t)0xFFFF)

#define LWM2M_URI_FLAG_OBJECT_ID    (uint8_t)0x04
#define LWM2M_URI_FLAG_INSTANCE_ID  (uint8_t)0x02
#define LWM2M_URI_FLAG_RESOURCE_ID  (uint8_t)0x01

#define LWM2M_URI_IS_SET_INSTANCE(uri) (((uri)->flag & LWM2M_URI_FLAG_INSTANCE_ID) != 0)
#define LWM2M_URI_IS_SET_RESOURCE(uri) (((uri)->flag & LWM2M_URI_FLAG_RESOURCE_ID) != 0)

typedef struct
{
    uint8_t     flag;           // indicates which segments are set
    uint16_t    objectId;
    uint16_t    instanceId;
    uint16_t    resourceId;
} lwm2m_uri_t;


#define LWM2M_STRING_ID_MAX_LEN 6

// Parse an URI in LWM2M format and fill the lwm2m_uri_t.
// Return the number of characters read from buffer or 0 in case of error.
// Valid URIs: /1, /1/, /1/2, /1/2/, /1/2/3
// Invalid URIs: /, //, //2, /1//, /1//3, /1/2/3/, /1/2/3/4
int lwm2m_stringToUri(const char * buffer, size_t buffer_len, lwm2m_uri_t * uriP);

typedef enum
{
    URI_DEPTH_OBJECT,
    URI_DEPTH_OBJECT_INSTANCE,
    URI_DEPTH_RESOURCE,
    URI_DEPTH_RESOURCE_INSTANCE
} uri_depth_t;

// defined in uri.c
lwm2m_uri_t * uri_decode(char * altPath, multi_option_t *uriPath);
int uri_getNumber(const uint8_t *uriString, size_t uriLength);
int uri_toString(lwm2m_uri_t * uriP, uint8_t * buffer, size_t bufferLen, uri_depth_t * depthP);
