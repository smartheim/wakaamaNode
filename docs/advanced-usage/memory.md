A target device needs **5kb RAM** and **10kb ROM** for the library without DTLS and some user defined objects.

Most of the API can be used in a staticly allocated memory environment.
Wakaama on the other hand uses dynamic memory allocation for events like server
connections, message receiving, message resends. 

!!! info
    You may influence the memory layout by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup`` accordingly.

The DTLS implementation that is optionally included (mbedTLS) makes use of dynamic memory allocation.

!!! info
    You may influence the memory layout by implementing ``mbedtls_malloc`` and ``mbedtls_free`` accordingly.
 
