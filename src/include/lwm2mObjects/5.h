#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id5 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Package5
    class PackageType : public Opaque<30> {};
    #endif
    
    #ifndef PackageURI5
    class PackageURIType : public PreallocString<30> {};
    #endif
    
    #ifndef PkgName5
    class PkgNameType : public PreallocString<30> {};
    #endif
    
    #ifndef PkgVersion5
    class PkgVersionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 5 - Firmware Update
 *  This LwM2M Object enables management of firmware which is to be updated. This Object
 *  includes installing firmware package, updating firmware, and performing actions
 *  after updating firmware. The firmware update MAY require to reboot the device; it will
 *  depend on a number of factors, such as the operating system architecture and the extent
 *  of the updated software.The envisioned functionality with LwM2M version 1.0 is to
 *  allow a LwM2M Client to connect to any LwM2M version 1.0 compliant Server to obtain a
 *  firmware imagine using the object and resource structure defined in this section experiencing
 *  communication security protection using DTLS. There are, however, other design decisions
 *  that need to be taken into account to allow a manufacturer of a device to securely install
 *  firmware on a device. Examples for such design decisions are how to manage the firmware
 *  update repository at the server side (which may include user interface considerations),
 *  the techniques to provide additional application layer security protection of the
 *  firmware image, how many versions of firmware imagines to store on the device, and how
 *  to execute the firmware update process considering the hardware specific details
 *  of a given IoT hardware product. These aspects are considered to be outside the scope
 *  of the LwM2M version 1.0 specification.A LwM2M Server may also instruct a LwM2M Client
 *  to fetch a firmware image from a dedicated server (instead of pushing firmware imagines
 *  to the LwM2M Client). The Package URI resource is contained in the Firmware object and
 *  can be used for this purpose.A LwM2M Client MUST support block-wise transfer [CoAP_Blockwise]
 *  if it implements the Firmware Update object.A LwM2M Server MUST support block-wise
 *  transfer. Other protocols, such as HTTP/HTTPs, MAY also be used for downloading firmware
 *  updates (via the Package URI resource). For constrained devices it is, however, RECOMMENDED
 *  to use CoAP for firmware downloads to avoid the need for additional protocol implementations.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Firmware package
    PackageType Package;
    
    // 1 - URI from where the device can download the firmware package by an alternative mechanism. As soon the device has received the Package URI it performs the download at the next practical opportunity. The URI format is defined in RFC 3986. For example, coaps://example.org/firmware is a syntactically valid URI. The URI scheme determines the protocol to be used. For CoAP this endpoint MAY be a LwM2M Server but does not necessarily need to be. A CoAP server implementing block-wise transfer is sufficient as a server hosting a firmware repository and the expectation is that this server merely serves as a separate file server making firmware images available to LwM2M Clients.
    PackageURIType PackageURI;
    
    // 2 - Updates firmware by using the firmware package stored in Package, or, by using the firmware downloaded from the Package URI.This Resource is only executable when the value of the State Resource is Downloaded.
    Executable Update;

    // 3 - Indicates current state with respect to this firmware update. This value is set by the LwM2M Client.0: Idle (before downloading or after successful updating)1: Downloading (The data sequence is on the way)2: Downloaded3: UpdatingIf writing the firmware package to Package Resource is done, or, if the device has downloaded the firmware package from the Package URI the state changes to Downloaded.Writing an empty string to Package URI Resource or setting the Package Resource to NULL (‘\0’), resets the Firmware Update State Machine: the State Resource value is set to Idle and the Update Result Resource value is set to 0.When in Downloaded state, and the executable Resource Update is triggered, the state changes to Updating.If the Update Resource failed, the state returns at Downloaded.If performing the Update Resource was successful, the state changes from Updating to Idle. Firmware Update mechanisms are illustrated below in Figure 29 of the LwM2M version 1.0 specification.
    int State;
    
    // 5 - Contains the result of downloading or updating the firmware0: Initial value. Once the updating process is initiated (Download /Update), this Resource MUST be reset to Initial value.1: Firmware updated successfully,2: Not enough flash memory for the new firmware package.3. Out of RAM during downloading process.4: Connection lost during downloading process.5: Integrity check failure for new downloaded package.6: Unsupported package type.7: Invalid URI8: Firmware update failed9: Unsupported protocol. A LwM2M client indicates the failure to retrieve the firmware image using the URI provided in the Package URI resource by writing the value 9 to the /5/0/5 (Update Result resource) when the URI contained a URI scheme unsupported by the client. Consequently, the LwM2M Client is unable to retrieve the firmware image using the URI provided by the LwM2M Server in the Package URI when it refers to an unsupported protocol.
    int UpdateResult;
    
    // Optional resource
    // 6 - Name of the Firmware Package
    PkgNameType PkgName;
    
    // Optional resource
    // 7 - Version of the Firmware package
    PkgVersionType PkgVersion;
    
    // Optional resource
    // 8 - This resource indicates what protocols the LwM2M Client implements to retrieve firmware images. The LwM2M server uses this information to decide what URI to include in the Package URI. A LwM2M Server MUST NOT include a URI in the Package URI object that uses a protocol that is unsupported by the LwM2M client.For example, if a LwM2M client indicates that it supports CoAP and CoAPS then a LwM2M Server must not provide an HTTP URI in the Packet URI.The following values are defined by this version of the specification:0 – CoAP (as defined in RFC 7252) with the additional support for block-wise transfer. CoAP is the default setting.1 – CoAPS (as defined in RFC 7252) with the additional support for block-wise transfer2 – HTTP 1.1 (as defined in RFC 7230)3 – HTTPS 1.1 (as defined in RFC 7230)Additional values MAY be defined in the future. Any value not understood by the LwM2M Server MUST be ignored.
    int FirmwareUpdateProtocolSupport;
    
    // 9 - The LwM2M Client uses this resource to indicate its support for transferring firmware images to the client either via the Package Resource (=push) or via the Package URI Resource (=pull) mechanism.0 – Pull only1 – Push only2 – Both. In this case the LwM2M Server MAY choose the preferred mechanism for conveying the firmware image to the LwM2M Client.
    int FirmwareUpdateDeliveryMethod;
    
};

enum class RESID {
    Package = 0,
    PackageURI = 1,
    Update = 2,
    State = 3,
    UpdateResult = 5,
    PkgName = 6,
    PkgVersion = 7,
    FirmwareUpdateProtocolSupport = 8,
    FirmwareUpdateDeliveryMethod = 9,
    
};

/* \brief Class for object 5 - Firmware Update
 *  This LwM2M Object enables management of firmware which is to be updated. This Object
 *  includes installing firmware package, updating firmware, and performing actions
 *  after updating firmware. The firmware update MAY require to reboot the device; it will
 *  depend on a number of factors, such as the operating system architecture and the extent
 *  of the updated software.The envisioned functionality with LwM2M version 1.0 is to
 *  allow a LwM2M Client to connect to any LwM2M version 1.0 compliant Server to obtain a
 *  firmware imagine using the object and resource structure defined in this section experiencing
 *  communication security protection using DTLS. There are, however, other design decisions
 *  that need to be taken into account to allow a manufacturer of a device to securely install
 *  firmware on a device. Examples for such design decisions are how to manage the firmware
 *  update repository at the server side (which may include user interface considerations),
 *  the techniques to provide additional application layer security protection of the
 *  firmware image, how many versions of firmware imagines to store on the device, and how
 *  to execute the firmware update process considering the hardware specific details
 *  of a given IoT hardware product. These aspects are considered to be outside the scope
 *  of the LwM2M version 1.0 specification.A LwM2M Server may also instruct a LwM2M Client
 *  to fetch a firmware image from a dedicated server (instead of pushing firmware imagines
 *  to the LwM2M Client). The Package URI resource is contained in the Firmware object and
 *  can be used for this purpose.A LwM2M Client MUST support block-wise transfer [CoAP_Blockwise]
 *  if it implements the Firmware Update object.A LwM2M Server MUST support block-wise
 *  transfer. Other protocols, such as HTTP/HTTPs, MAY also be used for downloading firmware
 *  updates (via the Package URI resource). For constrained devices it is, however, RECOMMENDED
 *  to use CoAP for firmware downloads to avoid the need for additional protocol implementations.
 */
class object : public Lwm2mObject<5, object, instance> {
public:

    // 0 - Firmware package
    Resource(0, &instance::Package, O_RES_W) Package;
    
    // 1 - URI from where the device can download the firmware package by an alternative mechanism. As soon the device has received the Package URI it performs the download at the next practical opportunity. The URI format is defined in RFC 3986. For example, coaps://example.org/firmware is a syntactically valid URI. The URI scheme determines the protocol to be used. For CoAP this endpoint MAY be a LwM2M Server but does not necessarily need to be. A CoAP server implementing block-wise transfer is sufficient as a server hosting a firmware repository and the expectation is that this server merely serves as a separate file server making firmware images available to LwM2M Clients.
    Resource(1, &instance::PackageURI, O_RES_RW) PackageURI;
    
    // 2 - Updates firmware by using the firmware package stored in Package, or, by using the firmware downloaded from the Package URI.This Resource is only executable when the value of the State Resource is Downloaded.
    Resource(2, &instance::Update) Update;
    
    // 3 - Indicates current state with respect to this firmware update. This value is set by the LwM2M Client.0: Idle (before downloading or after successful updating)1: Downloading (The data sequence is on the way)2: Downloaded3: UpdatingIf writing the firmware package to Package Resource is done, or, if the device has downloaded the firmware package from the Package URI the state changes to Downloaded.Writing an empty string to Package URI Resource or setting the Package Resource to NULL (‘\0’), resets the Firmware Update State Machine: the State Resource value is set to Idle and the Update Result Resource value is set to 0.When in Downloaded state, and the executable Resource Update is triggered, the state changes to Updating.If the Update Resource failed, the state returns at Downloaded.If performing the Update Resource was successful, the state changes from Updating to Idle. Firmware Update mechanisms are illustrated below in Figure 29 of the LwM2M version 1.0 specification.
    Resource(3, &instance::State, O_RES_R) State;
    
    // 5 - Contains the result of downloading or updating the firmware0: Initial value. Once the updating process is initiated (Download /Update), this Resource MUST be reset to Initial value.1: Firmware updated successfully,2: Not enough flash memory for the new firmware package.3. Out of RAM during downloading process.4: Connection lost during downloading process.5: Integrity check failure for new downloaded package.6: Unsupported package type.7: Invalid URI8: Firmware update failed9: Unsupported protocol. A LwM2M client indicates the failure to retrieve the firmware image using the URI provided in the Package URI resource by writing the value 9 to the /5/0/5 (Update Result resource) when the URI contained a URI scheme unsupported by the client. Consequently, the LwM2M Client is unable to retrieve the firmware image using the URI provided by the LwM2M Server in the Package URI when it refers to an unsupported protocol.
    Resource(5, &instance::UpdateResult, O_RES_R) UpdateResult;
    
    // Optional resource
    // 6 - Name of the Firmware Package
    Resource(6, &instance::PkgName, O_RES_R) PkgName;
    
    // Optional resource
    // 7 - Version of the Firmware package
    Resource(7, &instance::PkgVersion, O_RES_R) PkgVersion;
    
    // Optional resource
    // 8 - This resource indicates what protocols the LwM2M Client implements to retrieve firmware images. The LwM2M server uses this information to decide what URI to include in the Package URI. A LwM2M Server MUST NOT include a URI in the Package URI object that uses a protocol that is unsupported by the LwM2M client.For example, if a LwM2M client indicates that it supports CoAP and CoAPS then a LwM2M Server must not provide an HTTP URI in the Packet URI.The following values are defined by this version of the specification:0 – CoAP (as defined in RFC 7252) with the additional support for block-wise transfer. CoAP is the default setting.1 – CoAPS (as defined in RFC 7252) with the additional support for block-wise transfer2 – HTTP 1.1 (as defined in RFC 7230)3 – HTTPS 1.1 (as defined in RFC 7230)Additional values MAY be defined in the future. Any value not understood by the LwM2M Server MUST be ignored.
    Resource(8, &instance::FirmwareUpdateProtocolSupport, O_RES_R) FirmwareUpdateProtocolSupport;
    
    // 9 - The LwM2M Client uses this resource to indicate its support for transferring firmware images to the client either via the Package Resource (=push) or via the Package URI Resource (=pull) mechanism.0 – Pull only1 – Push only2 – Both. In this case the LwM2M Server MAY choose the preferred mechanism for conveying the firmware image to the LwM2M Client.
    Resource(9, &instance::FirmwareUpdateDeliveryMethod, O_RES_R) FirmwareUpdateDeliveryMethod;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id5::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id5::RESID c1) { return (uint16_t) c1 == c2; }
	
