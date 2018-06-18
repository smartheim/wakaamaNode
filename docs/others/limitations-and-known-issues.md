# Limitations

## Auto generated registry objects

Unfortunately the lwm2m description does not consistently contain information about the maximum size of a string or an opaque block.
Currently strings and opaque resources are hardcoded to 30 bytes in size. Each string and opaque resource is defined as Macro
and can be overridden before including the respective header file.

## Resources: Object links

The library does not support object links as resources if you use the C or C++ objects API.

## Resources: Multiple instances

The library does not support multiple instances of resources. Those are mostly used for object links though.

## DTLS: Certificate based encryption suits

The library only supports to configure the embedded mbedtls to use preshared (PSK) ciphers suits.

## Main loop timing

A connection to a lwM2M server may be interrupted if the libraries main loop method is not called in time.
Do not `delay()` or ADC read for too long. The `lwm2m_client_process` method will return a `time_t` value
in seconds to let you know when the next call is due.
