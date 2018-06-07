# WakaamaNode [![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode)

This is a Lightweight M2M library meant to be used for embedded/constrained devices with a convenient C and C++ API.

> Lightweight M2M is a protocol from the Open Mobile Alliance for M2M or IoT device management and communication.
It is a convention on top of CoAP/UDP, a light and compact protocol with an efficient resource data model.
It follows a server/client architecture with Request/Response semantics (GET, POST, PUT, DELETE), as well as observable resources.
Optional DTLS (Datagram TLS) ensures secure communication between LWM2M Servers and LWM2M Clients.

Each service on a constrained device/sensor/actor is modeled as an lwM2M object instance with a set of so called resources,
accessible via a unique CoAP URI.
lwM2M URIs have a clear hierarchy of *objectID*/*objectInstanceID*/*resourceID*.
A lot of common and not so common object and resource identifiers are standardised via the [OMA Object & Resource Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html).

For example object [3311](http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml) is for light controls, [3312](http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml) for power sources such as smart plugs.

## Features
* The well-tested [Eclipse Wakaama](https://github.com/eclipse/wakaama) provides the underlying lwM2M protocol.
* Always up-to-date/in-sync Wakaama code (using a Travis CI daily cron job).
* All necessary lwm2m objects (security, server, device) for connecting to a lwM2M server are provided.
* 3 Platform integrations (posix/win32, esp8266-sdk, freertos)
* 2 Network stack integrations (posix/win32, lwIP)
* 2 Firmware update integrations (posix/Win32, arduino OTA)
* Easy lwm2m object definition API for C and C++
* Supports optional DTLS via mbedTLS
* All API functionallity and library<-->wakaama server communication is covered by tests.

Have a look at the documentation: https://openhab-nodes.github.com/wakaamaNode

## License
This platform code and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v2.0.

