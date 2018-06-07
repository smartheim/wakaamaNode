# Limitations

## Auto generated registry objects

Unfortunately the lwm2m description does not consistently contain information about the size of a string or an opaque block.
Currently strings and opaque resources are hardcoded to 30 bytes in size.

## Object link resources

The library does not support object links as resources if you use the C or C++ objects API.

## Resources: Multiple instances

The library does not support multiple instances of resources. Those are mostly used for object links anyway.

## Main loop timing

A connection to a lwM2M server may be interrupted if the the libraries main loop method is not called in time.
Do not `delay()` or ADC read for too long.
