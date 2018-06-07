# OTA updates

lwM2M defines a firmware upgrade object. The wakaamaNode library provides two
reference implementations: For the Arduino OTA model and for Posix/Windows binaries.

Find the implementations in the
[<img src="../../assets/github.png" style="width:20px"> src/firmware](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/src/firmware)
directory.


Updating or even checking the version is a server initatiated operation, wakaamaNode
will not perform any checks on its own.

## OTA security

You should only accept an OTA request, if you are connected to a DTLS secured connection
with an authentificated server.
