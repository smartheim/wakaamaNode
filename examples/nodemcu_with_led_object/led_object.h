#pragma once

#include "wakaama_object_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

lwm2m_object_meta_information_t* led_object_get_meta();
lwm2m_list_t* led_object_create_instances();

#ifdef __cplusplus
}
#endif