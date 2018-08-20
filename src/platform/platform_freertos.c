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
typedef int make_iso_compilers_happy; // if not FREERTOS

#ifdef FREERTOS
// Recommended heap schema: heap4. http://www.freertos.org/a00111.html

#include <string.h>
#include <time.h>

#include <freertos.h>

void * lwm2m_malloc(size_t s)
{
    return pvPortMalloc(s);
}

void lwm2m_free(void * p)
{
    return vPortFree(p);
}

char * lwm2m_strdup(const char * str)
{
    size_t len = strlen(str);
    if(!len)
	return 0;
    char *dupStr = (char*)pvPortMalloc(len + 1);
    strcpy(dupStr, str);
	return dupStr;
}

int lwm2m_strncmp(const char * s1,
                     const char * s2,
                     size_t n)
{
    return strncmp(s1, s2, n);
}

time_t lwm2m_gettime(void)
{
    return xTaskGetTickCount()/configTICK_RATE_HZ;
}

#ifdef LWM2M_WITH_LOGS
void __attribute__((weak)) lwm2m_printf(const char * format, ...)
{

}
#else
void __attribute__((weak)) lwm2m_printf(const char * format, ...) {}

#endif

#endif
