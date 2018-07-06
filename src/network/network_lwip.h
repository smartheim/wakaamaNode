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

#include <lwip/ip.h>
#include <lwip/udp.h>
typedef struct udp_pcb udp_pcb_t;

#include <stdint.h>
#include <stdbool.h>

typedef struct _addr_t_ {
    ip_addr_t     addr;
    uint16_t      port;
} addr_t;

typedef struct _sock_t_ {
    udp_pcb_t * udp;
    void* net_if_out;
} sock_t;
