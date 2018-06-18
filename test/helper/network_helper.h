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

#include <stdint.h>
#include "../src/wakaama/liblwm2m.h"

#ifdef __cplusplus
extern "C" {
#endif

// Uses lwm2m_step() to figure out what needs to be send and
// receives from the network stack and input traffic into wakaama via lwm2m_handle_packet().
uint8_t network_step_blocking(lwm2m_context_t * lwm2mH, int bound_sockets);

// Return true for success or if already initialized and false on error
bool test_network_init(void);

// Frees all network ressources, that were acquired in network_init()
void test_network_close(void);

void* network_get_interface(int id);

#ifdef __cplusplus
}
#endif
