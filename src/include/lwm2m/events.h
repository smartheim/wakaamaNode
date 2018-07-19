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
#include "context.h"
#include <inttypes.h>
#include "../../inplace_function.h"

/**
 * Use the event dispatcher to register a function for particular events
 * instead of manually parsing and evaluating the process() return value and state.
 */
class EventDispatcher {
    void dispatch(int result, lwm2m_context_t* context);
public:
    // We need to compare to the last value
    uint8_t lastState = STATE_INITIAL;

    // Change from lwm2m->state (any) -> lwm2m->state (STATE_READY)
    stdext::inplace_function<void(), 20> connected;
    // Change from lwm2m->state (any) -> lwm2m->state (COAP_503_SERVICE_UNAVAILABLE)
    stdext::inplace_function<void(), 20> disconnected;
    // change from (any) -> COAP_506_DTLS_CONNECTION_DENIED
    stdext::inplace_function<void(), 20> dtls_handhshake_failed;
    // change from (any) -> COAP_505_NO_NETWORK_CONNECTION
    stdext::inplace_function<void(), 20> network_failed;
};
