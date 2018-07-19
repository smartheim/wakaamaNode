#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "config.h"
#include "data.h"

/*
 * Utility function to parse TLV buffers directly
 *
 * Returned value: number of bytes parsed
 * buffer: buffer to parse
 * buffer_len: length in bytes of buffer
 * oType: (OUT) type of the parsed TLV record. can be:
 *          - LWM2M_TYPE_OBJECT
 *          - LWM2M_TYPE_OBJECT_INSTANCE
 *          - LWM2M_TYPE_MULTIPLE_RESOURCE
 *          - LWM2M_TYPE_OPAQUE
 * oID: (OUT) ID of the parsed TLV record
 * oDataIndex: (OUT) index of the data of the parsed TLV record in the buffer
 * oDataLen: (OUT) length of the data of the parsed TLV record
 */

#define LWM2M_TLV_HEADER_MAX_LENGTH 6

int lwm2m_decode_TLV(const uint8_t * buffer, size_t buffer_len, lwm2m_data_type_t * oType, uint16_t * oID, size_t * oDataIndex, size_t * oDataLen);

// defined in tlv.c
int tlv_parse(const uint8_t *buffer, size_t bufferLen, lwm2m_data_t ** dataP);
int tlv_serialize(bool isResourceInstance, int size, lwm2m_data_t * dataP, uint8_t ** bufferP);
