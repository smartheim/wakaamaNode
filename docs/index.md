<picture>
  <source srcset="assets/logo_s.webp" type="image/webp">
  <source srcset="assets/logo_s.png" type="image/png"> 
  <img src="assets/logo_s.png" alt="LwM2M logo">
</picture>
# WakaamaNode [![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode)

This is a Lightweight M2M library meant to be used for embedded/constrained devices with a convenient C and C++ API.

> Lightweight M2M is a protocol from the Open Mobile Alliance for M2M/IoT device management and communication.
It is a convention on top of CoAP/UDP, a light and compact protocol with an efficient resource data model.
It follows a server/client architecture with Request/Response semantics (GET, POST, PUT, DELETE), as well as observable resources.
Optional DTLS (Datagram TLS) ensures secure communication between LWM2M Servers and LWM2M Clients.

The CoAP/lwM2M data model is explained on the [Object API](https://openhab-nodes.github.io/wakaamaNode/api/about/) page.

A lot of common and not so common object and resource identifiers are standardised via the [OMA Object & Resource Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html). For example object [3311](http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml) is for light controls, [3312](http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml) for power sources such as smart plugs.


## Getting started

Head over to the [Get started](quickstart/getting-started.md) page to dive right into installing and including the library in your project.

## Features
* **A connection API** (that implements lwm2m objects security, server and device) makes it simple to connect to a lwM2M server.
* **LwM2M object definition API** for C and C++ and [ready-to-use c++ classes](api/objects-registry.md) for all objects of the OMA Object & Resource Registry.
* The well-tested [Eclipse Wakaama](https://github.com/eclipse/wakaama) provides the underlying lwM2M protocol implementation.
     * Always up-to-date/in-sync Wakaama code (using a Travis CI daily cron job).
* **Secure connections** via optional DTLS and the mbedTLS library
* **Test coverage** - All API functionallity and library<-->wakaama server communication is covered by tests.

Platform/network:

* 3 Platform integrations (posix/win32, esp8266-sdk, freertos)
* 2 Network stack integrations (posix/win32, lwIP)
* 2 Firmware update integrations (posix/Win32, arduino OTA)

Building:

* 2 build toolchains supported: platformio and cmake
* Connection API and object API compilable with a C-only compiler (OTA support requires a c++ compiler though)

## Target device requirements
A target device needs **5kb RAM** and **10kb ROM** for the library without DTLS and some user defined objects.

Most of the API can be used in a staticly allocated memory environment.
Wakaama on the other hand uses dynamic memory allocation for events like server
connections, message receiving, message resends. 

!!! info
    You may influence the memory layout by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup`` accordingly.

The DTLS implementation that is optionally included (mbedTLS) makes use of dynamic memory allocation.

!!! info
    You may influence the memory layout by implementing ``mbedtls_malloc`` and ``mbedtls_free`` accordingly.

## Periodic synchronisation to the latest Wakaama/mbedTLS sources
Travis CI runs every day by a travis cron job to synchronize sources listed below back into the library:

* the ``src/wakaama`` directory to the latest code found in the *core* directory of
https://github.com/eclipse/wakaama.git.
* the ``src/network/mbedtls`` directory to the latest code found in the *inc/mbedtls/* and *src/* directory of
https://github.com/ARMmbed/mbed-os/tree/master/features/mbedtls.

This may cause tests in the master branch to fail, please use a tagged release of the library in this case.
If the tests do not fail, it is safe to assume that the library works as expected. Current status:

[![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode)

## Automated tests

Travis CI is executed on every commit. The following functionality is tested:

* The Object API for C
  * Reading/Writing of c-strings and opaque memory
  * Reading/Writing of boolean, int, double.
  * Executing of function pointers.
  * WriteVerify method is called correctly
  * Object discovery works
* The Object API for C++
  * Reading/Writing of c-strings and opaque memory
  * Reading/Writing of boolean, int, double.
  * Reading/Writing of all types above via indirect reading from a function, writing to a function
  * WriteVerify method is called correctly
  * Executable resources: Execute a function pointer
  * Object discovery works
* The connect API on Posix
  * Add/Remove servers
  * Connect to a server and on the server side: Make sure client objects are discovered
  * Connect to a server via dtls and on the server side: Make sure client objects are discovered
* The connect API on LWIP
  * Building the implementation
  - **Not tested**: A running example with LWIP. tun/tap is required on travis for this to work.
* Examples
  * Build all examples
  - **Not tested**: If the linux example can connect to a public lwm2m server.

## License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v2.0.

