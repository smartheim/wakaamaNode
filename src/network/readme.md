# Network integration
This directory consists of files for different network stack integrations:

* The lwip stack, used on many embedded systems
* and a posix compatible stack with some conditional code to make it work with the windows network stack as well.

An implementation has to keep track of open udp connections, open up a connection, close a connection.

## DTLS

Integrating DTLS into the wakaamaNode communication happens almost entirely in this directory.
The better part of the implementation is shared between all network stack implementation in the file `network_dtls.c`.

## Windows network stack

The efficient epoll() system call is used on Linux, instead of the ancient select().
To be able to use the same code and efficiency on Windows,
the shim library wepoll (https://github.com/piscisaureus/wepoll/) is included and conditionally compiled.

