/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */

/*
 *  Resources:
 *
 *          Name         | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Short ID             |  0 |     R      |  Single   |    Yes    | Integer | 1-65535 |       |
 *  Lifetime             |  1 |    R/W     |  Single   |    Yes    | Integer |         |   s   |
 *  Default Min Period   |  2 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Default Max Period   |  3 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Disable              |  4 |     E      |  Single   |    No     |         |         |       |
 *  Disable Timeout      |  5 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Notification Storing |  6 |    R/W     |  Single   |    Yes    | Boolean |         |       |
 *  Binding              |  7 |    R/W     |  Single   |    Yes    | String  |         |       |
 *  Registration Update  |  8 |     E      |  Single   |    Yes    |         |         |       |
 *
 */

#include "wakaama/liblwm2m.h"
#include "internal_objects.h"
#include "lwm2m/context.h"

bool server_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    server_instance_t* i = (server_instance_t*)instance;

    if(changed_res_id==7) {
        size_t len = strlen((char*)i->binding.data);
        if (!(len > 0 && len <= 3)
                && (strncmp((char*)i->binding.data, "U",   len) == 0
                 || strncmp((char*)i->binding.data, "UQ",  len) == 0
                 || strncmp((char*)i->binding.data, "S",   len) == 0
                 || strncmp((char*)i->binding.data, "SQ",  len) == 0
                 || strncmp((char*)i->binding.data, "US",  len) == 0
                 || strncmp((char*)i->binding.data, "UQS", len) == 0))
            return false;
    }
    return true;
}

void init_server_object(lwm2m_client_context_t *ctx) {
    OBJECT_META (server_instance_t,server_object,1,server_object_write_verify_cb,SERVER_OBJECT_RES);
    memcpy(&ctx->serverObject, server_objectP,sizeof(ctx->serverObject));
    lwm2m_add_initialize_object(&ctx->context, (lwm2m_object_t*)&ctx->serverObject, false);
}
