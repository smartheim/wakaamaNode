# About OMA Lightweight M2M

Standards for constrained devices are rapidly consolidating and the availability of IP on constrained devices enabled these devices to easily connect to the Internet. The IETF has also created a set of specifications for such IP-enabled devices to work in a Web-like fashion. One such protocol is the [Constrained Application Protocol (CoAP)](https://tools.ietf.org/html/rfc7252) that provides request/response methods, ways to identify resources, discovery mechanisms, etc. similar to the [Hypertext Transfer Protocol](https://tools.ietf.org/html/rfc2616) but for use in constrained environments.

However, the use of standardized protocols does not ensure interoperability on the application layer. Therefore, there is a clear need for being able to communicate using structured data models on top of protocols like CoAP and HTTP.

OMA (Open Mobile Alliance) has defined a standard for IoT or M2M devices, building on CoAP (and DTLS). It defines bootstrap and device management, as well as a data model.

## Data model

Each LwM2M client presents a data model - standardized, symbolic representation of its configuration and state that is accessible for reading and modifying by LwM2M Servers. It can be thought of as a combination of a hierarchical configuration file, and a view on statistical information about the device and its environment.

The LwM2M data model is very strictly organized as a three-level tree. Entities on each of those levels are identified with numerical identifiers. Those three levels are:

<ul>
<li>
<b>Object</b> - each Object represent some different concept of data accessible via the LwM2M client. For example, separate Objects are defined for managing connections with LwM2M servers, for managing network connections, for accessing data from various types of sensors, etc.

Each Object is assigned a unique numerical identifier in the range 0-65535, inclusive. OMA manages a registry of known Object IDs. Each Object defines a set of Resources whose meanings are common for each Object Instance.
</li>

<li>
<b>Object Instance</b> - some Objects are described as “single-instance” - such Objects always have exactly one Instance with identifier 0. Examples of such Objects include the Device object which describes the device itself, and the Firmware Update object which is used to perform firmware upgrades.

Other Objects may have multiple Instances; sometimes the number of Instances may be variable and the Instances themselves may be creatable via LwM2M. Examples of such Objects include the Object that manages connections to LwM2M Servers, Object that represents optional software packages installed on the device, and Objects representing sensors (whose instances are, however, not creatable). Identifiers for each Instance of such Objects may be arbitrarily chosen in the range 0-65534, inclusive - note that 65535 is reserved and forbidden in this context.
</li>

<li>
<b>Resource</b> - each Object Instance of a given Object supports the same set of Resources, as defined by the Object definition. Within a given Object, each Resource ID (which may be in the range 0-65535, inclusive) has a well-defined meaning, and represent the same concept. However, some Resources may not be present in some Object Instances, and, obviously, their values and mapping onto real-world entities may be different.
</li>
</ul>

The numerical identifiers on each of these levels form a path, which is used as the path portion of CoAP URLs. For example, a path `/1/2/3` refers to Resource ID=3 in Object Instance ID=2 of Object ID=1. Whole Object Instances (/1/2) or event Objects (/1) may be referred to using this syntax as well.

Find an example for an object definition in LWM2M xml schema at [urn:oma:lwm2m:ext:3303](http://www.openmobilealliance.org/tech/profiles/lwm2m/3303.xml).

### Objects

Each Object definition, which may be found in the LwM2M specification, features the following information:

* **Name** - description of the object; it is not used in the actual on-wire protocol.
* **Object ID** - numerical identifier of the Object
* **Instances** - Single (always has one Instance with ID=0) or Multiple (may have arbitrary number of Instances depending on current configuration)
* **Mandatory** - Mandatory (must be supported by all LwM2M Client implementations) or Optional (may not be supported)
* **Object URN** -  For example *urn:oma:lwm2m:ext:3347*
* **Resource definitions**: A list of resource definitions. See section further down.

#### Implemented objects

The current set of mandatory and therefore implemented Objects consists of:

* **/0 - LwM2M Security** - contains confidential part of information about connections to the LwM2M Servers configured in the Client. From the on-wire protocol perspective, it is write-only and accessible only via the Bootstrap Interface.
* **/1 - LwM2M Server** - contains non-confidential part of information about connections to the LwM2M Servers configured in the Client.
* **/2 - Access Control** needs to be supported and present if the Client supports more than one LwM2M Server connection at once.
* **/3 - Device** - contains basic information about the device, such as e.g. serial number.
* **/5 - Firmware** - enables OTA/Over-the-Air update support

### Resources

Each of the Resource definitions, contained in each Object definition, features the following information:

* **ID** - numerical identifier of the Object.
* **Name** - short description of the resource; it is not used in the actual on-wire protocol.
* **Operations** - one of:
    - **R** - read-only Resource
    - **W** - write-only Resource
    - **RW** - writeable Resource
    - **E** - executable Resource
* **Instances** - Single or Multiple; “Multiple” allows to have more than one instance of an object
* **Mandatory** - Mandatory or Optional; Mandatory resources need to be present in all Instances on all devices. Optional resources may not be present in all Instances, and may even be not supported at all on some Clients.
* **Type** - data type of the Resource value (or its instances in case of Multiple Resources).
* **Range or Enumeration** - specification of valid values for the Resource, within the given data type.
* **Units** - units in which a numerical value is given.
* **Description** - detailed description of the resource.

## References to specifications and further sources
- "Anjay LwM2M library documentation" <https://avsystem.github.io/Anjay-doc>
- "IP for Smart Objects - IPSO Objects" <https://github.com/IPSO-Alliance/pub/edit/master/README.md>
- "The Constrained Application Protocol (CoAP)". April 2017. <https://tools.ietf.org/html/rfc7252>
- "Lightweight Machine to Machine Technical Specification, Approved Version 1.0". Feb 2017. [OMA-TS-LightweightM2M-V1_0-20170208-A.pdf](http://www.openmobilealliance.org/release/LightweightM2M/V1_0-20170208-A/OMA-TS-LightweightM2M-V1_0-20170208-A.pdf)
- "Observing Resources in the Constrained Application Protocol (CoAP)". April 2017. <https://tools.ietf.org/html/rfc7641>
- "Constrained RESTful Environments (CoRE) Link Format". April 2017. <https://tools.ietf.org/html/rfc6690>
