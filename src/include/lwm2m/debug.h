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
#pragma once
#include "../../wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LWM2M_WITH_LOGS
#define lwm2m_printf(...)
#endif

void print_state(lwm2m_context_t * lwm2mH);

#ifdef __cplusplus
}
#endif
