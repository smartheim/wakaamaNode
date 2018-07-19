#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "uri.h"

/*
 * The lwm2m_data_t is used to store LWM2M resource values in a hierarchical way.
 * Depending on the type the value is different:
 * - LWM2M_TYPE_OBJECT, LWM2M_TYPE_OBJECT_INSTANCE, LWM2M_TYPE_MULTIPLE_RESOURCE: value.asChildren
 * - LWM2M_TYPE_STRING, LWM2M_TYPE_OPAQUE: value.asBuffer
 * - LWM2M_TYPE_INTEGER, LWM2M_TYPE_TIME: value.asInteger
 * - LWM2M_TYPE_FLOAT: value.asFloat
 * - LWM2M_TYPE_BOOLEAN: value.asBoolean
 *
 * LWM2M_TYPE_STRING is also used when the data is in text format.
 */

typedef enum
{
    LWM2M_TYPE_UNDEFINED = 0,
    LWM2M_TYPE_OBJECT,
    LWM2M_TYPE_OBJECT_INSTANCE,
    LWM2M_TYPE_MULTIPLE_RESOURCE,

    LWM2M_TYPE_STRING,
    LWM2M_TYPE_OPAQUE,
    LWM2M_TYPE_INTEGER,
    LWM2M_TYPE_FLOAT,
    LWM2M_TYPE_BOOLEAN,

    LWM2M_TYPE_OBJECT_LINK
} lwm2m_data_type_t;

typedef struct _lwm2m_data_t lwm2m_data_t;

struct _lwm2m_data_t
{
    lwm2m_data_type_t type;
    uint16_t    id;
    union
    {
        bool        asBoolean;
        int64_t     asInteger;
        double      asFloat;
        struct
        {
            size_t    length;
            uint8_t * buffer;
        } asBuffer;
        struct
        {
            size_t         count;
            lwm2m_data_t * array;
        } asChildren;
        struct
        {
            uint16_t objectId;
            uint16_t objectInstanceId;
        } asObjLink;
    } value;
};

typedef enum
{
    LWM2M_CONTENT_TEXT      = 0,        // Also used as undefined
    LWM2M_CONTENT_LINK      = 40,
    LWM2M_CONTENT_OPAQUE    = 42,
    LWM2M_CONTENT_TLV_OLD   = 1542,     // Keep old value for backward-compatibility
    LWM2M_CONTENT_TLV       = 11542,
    LWM2M_CONTENT_JSON_OLD  = 1543,     // Keep old value for backward-compatibility
    LWM2M_CONTENT_JSON      = 11543
} lwm2m_media_type_t;

lwm2m_data_t * lwm2m_data_new(int size);
int lwm2m_data_parse(lwm2m_uri_t * uriP, const uint8_t *buffer, size_t bufferLen, lwm2m_media_type_t format, lwm2m_data_t ** dataP);
int lwm2m_data_serialize(lwm2m_uri_t * uriP, int size, lwm2m_data_t * dataP, lwm2m_media_type_t * formatP, uint8_t ** bufferP);
void lwm2m_data_free(int size, lwm2m_data_t * dataP);

void lwm2m_data_encode_string(const char * string, lwm2m_data_t * dataP);
void lwm2m_data_encode_nstring(const char * string, size_t length, lwm2m_data_t * dataP);
void lwm2m_data_encode_opaque(const uint8_t *buffer, size_t length, lwm2m_data_t * dataP);
void lwm2m_data_encode_int(int64_t value, lwm2m_data_t * dataP);
int lwm2m_data_decode_int(const lwm2m_data_t * dataP, int64_t * valueP);
void lwm2m_data_encode_float(double value, lwm2m_data_t * dataP);
int lwm2m_data_decode_float(const lwm2m_data_t * dataP, double * valueP);
void lwm2m_data_encode_bool(bool value, lwm2m_data_t * dataP);
int lwm2m_data_decode_bool(const lwm2m_data_t * dataP, bool * valueP);
void lwm2m_data_encode_objlink(uint16_t objectId, uint16_t objectInstanceId, lwm2m_data_t * dataP);
void lwm2m_data_encode_instances(lwm2m_data_t * subDataP, size_t count, lwm2m_data_t * dataP);
void lwm2m_data_include(lwm2m_data_t * subDataP, size_t count, lwm2m_data_t * dataP);
