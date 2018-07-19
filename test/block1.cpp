/*******************************************************************************
 *
 * Copyright (c) 2015 Bosch Software Innovations GmbH, Germany.
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
 *   Julien Vermillard - Please refer to git log
 *
 *******************************************************************************/

#include "internals.h"
#include "liblwm2m.h"
#include <gtest/gtest.h>

static void handle_12345(lwm2m_block1_data_t ** blk1,
                                  uint16_t mid) {
    uint8_t buffer[] = "12345";
    size_t bsize;
    uint8_t *resultBuffer = nullptr;

    uint8_t st = coap_block1_handler(blk1, mid, buffer, 5, 5, 0, true, &resultBuffer, &bsize);
    ASSERT_EQ(st, COAP_231_CONTINUE);
    ASSERT_FALSE(resultBuffer);
}

static void handle_67(lwm2m_block1_data_t ** blk1,
                                  uint16_t mid) {
    uint8_t buffer[] = "67";
    size_t bsize;
    uint8_t *resultBuffer = nullptr;

    uint8_t st = coap_block1_handler(blk1, mid, buffer, 2, 5, 1, false, &resultBuffer, &bsize);
    ASSERT_EQ(st, NO_ERROR);
    ASSERT_TRUE(*resultBuffer);
    ASSERT_EQ(bsize, 7);
    ASSERT_STREQ ((const char*)resultBuffer, "1234567");
}


TEST(block1,nominal)
{
    lwm2m_block1_data_t * blk1 = nullptr;

    handle_12345(&blk1, 123);
    handle_67(&blk1, 346);

    free_block1_buffer(blk1);
}

TEST(block1,retransmit)
{
    lwm2m_block1_data_t * blk1 = nullptr;

    handle_12345(&blk1, 1);
    handle_12345(&blk1, 1);
    handle_67(&blk1, 3);
    handle_67(&blk1, 3);
    handle_67(&blk1, 3);

    free_block1_buffer(blk1);
}

