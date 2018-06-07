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

Each service on a constrained device/sensor/actor is modeled as an lwM2M object instance with a set of so called resources,
accessible via a unique CoAP URI.
lwM2M URIs have a clear hierarchy of *objectID*/*objectInstanceID*/*resourceID*.
A lot of common and not so common object and resource identifiers are standardised via the [OMA Object & Resource Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html).

For example object [3311](http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml) is for light controls, [3312](http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml) for power sources such as smart plugs.

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
A target device needs **5kb RAM** and **10kb ROM** for the library and some user defined  objects.

Most of the API can be used in a staticly allocated memory environment.
Wakaama on the other hand uses dynamic memory allocation for events like server
connections, message receiving, message resends. 
The DTLS implementation that is included (mbedTLS) makes use of dynamic memory allocation.

!!! info
    You may influence the memory layout by implementing ``lwm2m_malloc``, ``lwm2m_free`` and ``lwm2m_strdup`` accordingly.

## Automatic synchronisation to the latest Wakaama/mbed TLS sources
Travis CI is executed on every commit and additionally every day by a travis cron job.
The CI script syncronizes:

* the ``src/wakaama`` directory to the latest code found in the core directory of
https://github.com/eclipse/wakaama.git.
* the ``src/network/mbedtls`` directory to the latest code found in the inc/mbedtls/ and src/ directory of
https://github.com/ARMmbed/mbed-os/tree/master/features/mbedtls.

This may cause tests in the master branch to fail, please use a tagged release of the library in this case.

## License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v2.0.

