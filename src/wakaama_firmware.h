#pragma once
#include "wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum lwm2m_update_features {
    UPDATE_FEATURE_WITH_DIRECT_RECEIVE = 1,
    UPDATE_FEATURE_WITH_URI_DOWNLOAD = 2
} lwm2m_update_state_t;

lwm2m_update_state_t lwm2m_udapte_features();

void lwm2m_update_download_from_uri(const char* uri, size_t uri_length);

void lwm2m_update_receive(unsigned total_bytes, unsigned offset, uint8_t* data, unsigned length);

void lwm2m_update_execute();

typedef enum lwm2m_update_state {
    UPDATE_STATE_DEFAULT,
    UPDATE_STATE_SUCCESS,
    UPDATE_STATE_NO_STORAGE,
    UPDATE_STATE_NO_MEM,
    UPDATE_STATE_CONNECTION_LOST,
    UPDATE_STATE_CRC_FAIL,
    UPDATE_STATE_UNSUPPORTED,
    UPDATE_STATE_INAVLID_URI
} lwm2m_update_state_t;

void lwm2m_update_set_state(lwm2m_update_state_t state);

#ifdef __cplusplus
}
#endif
