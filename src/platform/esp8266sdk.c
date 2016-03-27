#ifdef ESP8266

#include <string.h>
#include <stdarg.h>

#include <esp_common.h>

void * lwm2m_malloc(size_t s)
{
    return os_malloc(s);
}

void lwm2m_free(void * p)
{
    return os_free(p);
}

char * lwm2m_strdup(const char * str)
{
    return strdup(str);
}

int lwm2m_strncmp(const char * s1,
                     const char * s2,
                     size_t n)
{
    return strncmp(s1, s2, n);
}

time_t lwm2m_gettime(void)
{
    // Convert system time in us to s.
    return system_get_time()/1000/1000;
}

#ifdef LWM2M_WITH_LOGS
void __attribute__((weak))  lwm2m_printf(const char * format, ...)
{
    va_list ap;

    va_start(ap, format);

    os_printf(format, ap);

    va_end(ap);
}
#endif

#endif
