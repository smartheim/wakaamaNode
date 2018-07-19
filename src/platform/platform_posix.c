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
typedef int make_iso_compilers_happy; // if not POSIX

#if (defined(_WIN32) || defined(__unix__) || defined(POSIX))

#include "../wakaama/liblwm2m.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

#ifndef LWM2M_WITHOUT_ALLOC_FREE
void* __attribute__((weak)) lwm2m_malloc(size_t s)
{
    return malloc(s);
}

void __attribute__((weak)) lwm2m_free(void * p)
{
    free(p);
}

char* __attribute__((weak)) lwm2m_strdup(const char * str)
{
    return strdup(str);
}
#endif

int lwm2m_strncmp(const char * s1,
                     const char * s2,
                     size_t n)
{
    return strncmp(s1, s2, n);
}

time_t __attribute__((weak)) lwm2m_gettime(void)
{
    struct timespec tv;
    clock_gettime(CLOCK_MONOTONIC, &tv);
    return tv.tv_sec;
}

time_t __attribute__((weak)) lwm2m_get_local_time(void) {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec;
}

#ifdef LWM2M_WITH_LOGS
void __attribute__((weak)) lwm2m_printf(const char * format, ...)
{
    va_list ap;

    va_start(ap, format);

    vfprintf(stderr, format, ap);

    va_end(ap);
}
#else
void __attribute__((weak)) lwm2m_printf(const char * format, ...) {}
#endif

#endif
