/*******************************************************************************
 *
 * Copyright (c) 2013, 2014 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    David Navarro, Intel Corporation - initial API and implementation
 *    Julien Vermillard, Sierra Wireless
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
 *    
 *******************************************************************************/

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
#include "wakaama_client_internal.h"
#include "wakaama_object_utils.h"

static lwm2m_object_with_meta_t server_object = {{0,0}};

static bool server_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

OBJECT_META(server_instance_t, server_object_meta, server_object_write_verify_cb,
        {0, O_RES_R|O_RES_UINT16                 ,  offsetof(server_instance_t,shortServerId)},
        {1, O_RES_R|O_RES_W|O_RES_UINT32,  offsetof(server_instance_t,lifetime)},
        {2, O_RES_R|O_RES_W|O_RES_UINT32,  offsetof(server_instance_t,defaultMinPeriod)},
        {3, O_RES_R|O_RES_W|O_RES_UINT32,  offsetof(server_instance_t,defaultMaxPeriod)},
        {4, O_RES_E                                     ,  0},
        {5, O_RES_R|O_RES_W|O_RES_UINT32,  offsetof(server_instance_t,disableTimeout)},
        {6, O_RES_R|O_RES_W|O_RES_BOOL  ,  offsetof(server_instance_t,storing)},
        {7, O_RES_R|O_RES_W|O_RES_STRING_PREALLOC,  offsetof(server_instance_t,binding)},
        {8, O_RES_E                                     ,  0}
)

static bool server_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    server_instance_t* i = (server_instance_t*)instance;

    if(changed_res_id==7) {
        int len = strlen(i->binding);
        if (!(len > 0 && len <= 3)
                && (strncmp(i->binding, "U",   len) == 0
                 || strncmp(i->binding, "UQ",  len) == 0
                 || strncmp(i->binding, "S",   len) == 0
                 || strncmp(i->binding, "SQ",  len) == 0
                 || strncmp(i->binding, "US",  len) == 0
                 || strncmp(i->binding, "UQS", len) == 0))
            return false;
    }
    return true;
}

lwm2m_object_t * init_server_object()
{
    lwm2m_object_create_preallocated(&server_object, 1, false, server_object_meta);
    return (lwm2m_object_t*)&server_object;
}
