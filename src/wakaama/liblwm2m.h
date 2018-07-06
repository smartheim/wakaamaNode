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
 *    Fabien Fleutot - Please refer to git log
 *    Simon Bernard - Please refer to git log
 *    Toby Jaffey - Please refer to git log
 *    Julien Vermillard - Please refer to git log
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
 *    Ville Skyttä - Please refer to git log
 *
 *******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

#include "config.h"
#include "platform.h"
#include "errorcodes.h"

#include "list.h"
#include "utils.h"
#include "uri.h"
#include "data.h"
#include "tlv.h"
#include "json.h"

#include "objects.h"
#include "block1.h"

#include "server_object.h"
#include "observe.h"

#include "transaction.h"
#include "registration.h"
#include "discover.h"

#include "server_clientlist.h"

#include "bootstrap.h"
#include "context.h"

#include "communication.h"

#include "lwm2m_client.h"
#include "lwm2m_server.h"

#ifdef __cplusplus
}
#endif
