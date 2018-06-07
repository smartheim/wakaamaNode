#pragma once
#include "wakaama/liblwm2m.h"

/**
 * The firmware update / OTA support is only available for a C++ project.
 */

enum lwm2m_update_features {
    UPDATE_FEATURE_WITH_DIRECT_RECEIVE = 1,
    UPDATE_FEATURE_WITH_URI_DOWNLOAD = 2
} lwm2m_update_state;

enum lwm2m_update_state {
    UPDATE_STATE_DEFAULT,
    UPDATE_STATE_SUCCESS,
    UPDATE_STATE_NO_STORAGE,
    UPDATE_STATE_NO_MEM,
    UPDATE_STATE_CONNECTION_LOST,
    UPDATE_STATE_CRC_FAIL,
    UPDATE_STATE_UNSUPPORTED,
    UPDATE_STATE_INAVLID_URI
} lwm2m_update_state;
