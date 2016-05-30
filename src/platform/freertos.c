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
    char *dupStr = (char*)pvPortMalloc(sizeof(str));
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
#endif

#endif
