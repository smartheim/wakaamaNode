#pragma once

#include "wakaama_object_utils.h"

lwm2m_object_meta_information_t* test_object_get_meta();
lwm2m_list_t* test_object_create_instance(uint16_t instance_id);

uint8_t test_object_execute_cb(uint16_t instanceId, uint16_t resourceId, uint8_t * buffer, int length, lwm2m_object_t * objectP);
