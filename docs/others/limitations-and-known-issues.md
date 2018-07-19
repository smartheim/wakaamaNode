# Limitations

## Auto generated registry objects

Unfortunately the lwm2m description does not consistently contain information about the maximum size of a string or an opaque block.
Currently strings and opaque resources are hardcoded to 30 bytes in size. Each string and opaque resource is defined as Macro
and can be overridden before including the respective header file.

## Resources: Object links

The library does not support object links as resources if you use the C or C++ objects API.

## Resources: Multiple instances

The library does not support multiple instances of resources. Those are mostly used for object links though.

## DTLS: Certificate based encryption + public raw key

The library only supports to configure the embedded mbedtls to use preshared (PSK) ciphers suits. Public raw keys are not yet fully supported by mbedtls
and certificate based encryption needs further configuration tuning of mbedtls.

## DTLS: Handshake

The lwm2m state machine will freeze as soon as a dtls handshake takes place.
This avoids the state machine to issue new packets or setup timers, while the actuall
connection have not been established yet.
If multiple servers are configured, all dtls handshakes take place in parallel.

But only if all have finished (successfully or timed out), the lwm2m state machine and lwm2m handshake will be processed.

## Main loop timing

A connection to a lwM2M server or a dtls session may get expired if the libraries main loop method is not called in time.
Do not `delay()`/`sleep()` or call blocking functions for too long. The `lwm2m_due_time` function returns a value
in seconds to let you know when the next call is due.
