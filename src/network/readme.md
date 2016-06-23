# Network integration
This directory consists of files for different network stack integrations. Currently
the lwip stack and a posix compatible stack as well as the windows network stack is supported.

Basically the work an implementation has to do is to keep track of open connections,
open up a connection, close a connection. A connection is a udp socket in this case.
