/*******************************************************************************
 *
 * Copyright (c) 2015 Intel Corporation and others.
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
 *    David Graeff - Make this a test suite
 *    
 *******************************************************************************/

#include "liblwm2m.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>

#include <gtest/gtest.h>
#include "memory.h"

static const char * tests[]={"1", "-114" , "2", "0", "-2", "919293949596979899", "-98979969594939291", "999999999999999999999999999999", "1.2" , "0.134" , "432f.43" , "0.01", "1.00000000000002", NULL};
static int64_t tests_expected_int[]={1,-114,2,0,-2,919293949596979899,-98979969594939291,-1,-1,-1,-1,-1,-1};
static double tests_expected_float[]={1,-114,2,0,-2,9.1929394959698e+17,-9.897996959493928e+16,1e+30,1.2,0.134,-1,0.01,1.00000000000002};

static int64_t ints[]={12, -114 , 1 , 134 , 43243 , 0, -215025};
static const char* ints_expected[] = {"12","-114","1", "134", "43243","0","-215025"};
static double floats[]={12, -114 , -30 , 1.02 , 134.000235 , 0.43243 , 0, -21.5025, -0.0925, 0.98765};
static const char* floats_expected[] = {"12","-114","-30", "1.02", "134.000235","0.43243","0","-21.5025","-0.0925","0.98765"};

TEST(utils,textToInt)
{
    int i;

    for (i = 0 ; tests[i] != nullptr ; i++)
    {
        int64_t res;

        if (utils_textToInt((const unsigned char*)tests[i], strlen(tests[i]), &res) != 1)
            res = -1;

        ASSERT_EQ(res, tests_expected_int[i]);
        //printf ("%i \"%s\" -> fail (%li)\n", i , tests[i], res );
    }
}

TEST(utils,textToFloat)
{
    int i;

    for (i = 0 ; tests[i] != nullptr ; i++)
    {
        double res;

        if (utils_textToFloat((const unsigned char*)tests[i], strlen(tests[i]), &res) != 1)
            res = -1;

        ASSERT_NEAR(res, tests_expected_float[i], 0.0001);
        //printf ("%i \"%s\" -> fail (%f)\n", i , tests[i], res );
    }
}

TEST(utils,intToTex)
{
    unsigned int i;

    for (i = 0 ; i < sizeof(ints)/sizeof(int64_t); i++)
    {
        char res[16];
        size_t len;

        len = utils_intToText(ints[i], (uint8_t*)res, 16);
        res[len] = 0;

        ASSERT_TRUE(len);
        ASSERT_STREQ(res, ints_expected[i]);
        //printf ("%i \"%i\" -> fail (%s)\n", i , ints[i], res );
    }
}

TEST(utils,floatToText)
{
    unsigned int i;

    for (i = 0 ; i < sizeof(floats)/sizeof(floats[0]); i++)
    {
        char res[16];
        size_t len;

        len = utils_floatToText(floats[i], (uint8_t*)res, 16);
        res[len] = 0;

        ASSERT_TRUE(len);
        ASSERT_STREQ(res, floats_expected[i]);
        //printf ("%i \"%.16g\" -> fail (%s)\n", i , floats[i], res );
    }
}

