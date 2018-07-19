## Automated tests

Travis CI is executed on every commit. The following functionality is tested:

* [x] The Object API for C
    - [x] Reading/Writing of c-strings and opaque memory
    - [x] Reading/Writing of boolean, int, double.
    - [x] Executing of function pointers.
    - [x] WriteVerify method is called correctly
    - [x] Object discovery works
* [x] The Object API for C++
    - [x] Reading/Writing of c-strings and opaque memory
    - [x] Reading/Writing of boolean, int, double.
    - [x] Reading/Writing of all types above via indirect reading from a function, writing to a function
    - [x] WriteVerify method is called correctly
    - [x] Executable resources: Execute a function pointer
    - [x] Object discovery works
* [x] The connect API in C/C++ on Posix
     * [x] Add/Remove servers
     * [x] Connect to a (wakaama lwm2m) server. On the server side: Make sure client objects are discovered
     * [x] Connect to a (wakaama lwm2m) server via dtls. On the server side: Make sure client objects are discovered
     * [x] Memory allocations match deallocations
* [ ] The connect API on LWIP
     * [x] Building the implementation
     - [ ] A running example with LWIP. **Not continously tested on travis: tun/tap would be required**.
* [x] Event dispatcher (C++)
     * [x] Dispatching events once
     * [x] Connected, Disconnected, DTLS_failed event delivered
* [x] LwM2M Data types
     * [x] TLV
     * [x] JSON
     * [x] Convert numbers
* [x] LwM2M URI handling
* [x] CoAP/LwM2M Block1
* [ ] Firmware updates
     * [ ] On linux
     * [ ] On windows
     * [ ] On esp8266
     * [ ] With http PULL
     * [ ] With coap PUSH
* Examples
     * [x] Build all examples
     - [x] C++ example: Connext to the public leshan lwm2m server with DTSL
     - [x] C example: Connect to the public leshan lwm2m server
