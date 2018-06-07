# Custom platform

Platform code need to implement the following methods:

```cpp
void* lwm2m_malloc(size_t s);

void lwm2m_free(void * p);

char* lwm2m_strdup(const char * str);

int lwm2m_strncmp(const char * s1,
                     const char * s2,
                     size_t n);

time_t __attribute__((weak)) lwm2m_gettime(void);

#ifdef LWM2M_WITH_LOGS
void __attribute__((weak)) lwm2m_printf(const char * format, ...);
#endif
```

`lwm2m_printf` is implemented with a weak linkage, so that the application is
able to override the log destination.

The implementation is expected to reside in the
[<img src="../../assets/github.png" style="width:20px"> src/platform](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/platform)
directory.
