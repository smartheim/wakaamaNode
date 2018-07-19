# WakaamaNode [![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode) [![Stability: Active](https://masterminds.github.io/stability/active.svg)](https://masterminds.github.io/stability/active.html)

This is a Lightweight M2M library meant to be used for embedded/constrained devices with a convenient C++ API and bindings for C.
[Get Started](https://openhab-nodes.github.io/wakaamaNode/).

> Lightweight M2M is a protocol from the Open Mobile Alliance for M2M or IoT device management and communication.
It is a convention on top of CoAP/UDP which itself is a light and compact protocol with an efficient resource data model.
It follows a server/client architecture with Request/Response semantics (GET, POST, PUT, DELETE), as well as observable resources.
Optional DTLS (Datagram TLS) ensures secure communication between LwM2M Servers and LwM2M Clients.

The CoAP/lwM2M data model is explained in the [documentation](https://openhab-nodes.github.io/wakaamaNode/api/about/).

A lot of common and not so common object and resource identifiers are standardised via the [OMA Object & Resource Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html). For example object [3311](http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml) is for light controls, [3312](http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml) for power sources such as smart plugs.

## Features
* The well-tested [Eclipse Wakaama](https://github.com/eclipse/wakaama) provides the underlying lwM2M protocol.
* A powerful [Connections API](https://openhab-nodes.github.io/wakaamaNode/api/connection-api/) allows to configure lwM2M servers
* [lwM2M object definition API](https://openhab-nodes.github.io/wakaamaNode/api/objects-custom/) for C and C++
* All LwM2M Objects of the [OMA Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html) are predefined for the [C++ Objects API](https://openhab-nodes.github.io/wakaamaNode/api/objects-registry/).
* 3 Platform integrations (posix/win32, esp8266-sdk, freertos)
* 2 Network stack integrations (posix/win32, lwIP)
* 2 Firmware update integrations (posix/Win32, arduino OTA)
* Supports optional DTLS via mbedTLS
* All API functionality and library<-->wakaama server communication is covered by tests.

Have a look at the documentation: https://openhab-nodes.github.io/wakaamaNode/

## License

* This platform code and API wrappers are provided under the MIT License (MIT).
* Wakaama is provided under the Eclipse Public License - v2.0.
* TinyFSM is provided unter The MIT License (MIT), Copyright (c) 2012-2018 Axel Burri
* Optional-lite, Span-lite, String-View-Lite is provided under the Boost Software License 1.0, Copyright (c) Martin Moene
