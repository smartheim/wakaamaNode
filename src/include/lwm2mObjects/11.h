#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id11 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Profilename11
    class ProfilenameType : public PreallocString<30> {};
    #endif
    
    #ifndef APN11
    class APNType : public PreallocString<30> {};
    #endif
    
    #ifndef UserName11
    class UserNameType : public PreallocString<30> {};
    #endif
    
    #ifndef Secret11
    class SecretType : public PreallocString<30> {};
    #endif
    
    #ifndef ReconnectSchedule11
    class ReconnectScheduleType : public PreallocString<30> {};
    #endif
    
    #ifndef ValidityMCCMNC11
    class ValidityMCCMNCType : public PreallocString<30> {};
    #endif
    
    #ifndef Connectionestablishmenttime111
    class Connectionestablishmenttime1Type : public PreallocString<30> {};
    #endif
    
    #ifndef Connectionendtime111
    class Connectionendtime1Type : public PreallocString<30> {};
    #endif
    
    #ifndef IPaddress211
    class IPaddress2Type : public PreallocString<30> {};
    #endif
    
    #ifndef Prefixlength211
    class Prefixlength2Type : public PreallocString<30> {};
    #endif
    
    #ifndef Subnetmask211
    class Subnetmask2Type : public PreallocString<30> {};
    #endif
    
    #ifndef Gateway211
    class Gateway2Type : public PreallocString<30> {};
    #endif
    
    #ifndef PrimaryDNSaddress211
    class PrimaryDNSaddress2Type : public PreallocString<30> {};
    #endif
    
    #ifndef SecondaryDNSaddress211
    class SecondaryDNSaddress2Type : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 11 - APN connection profile
 *  This object specifies resources to enable a device to connect to an APN.Notes:(1) For
 *  each activated PDP context request, the device may store at least one value of ‘Connection
 *  establishment time’, ‘connection establishment result’, ‘Connection end time’
 *  and if activation is unsuccessful then a ‘connection establishment reject cause’.
 *  It is a device decision how many instances to keep.(2) These resources are used in case
 *  IP related parameters are defined statically, and are also set with the IP related parameters
 *  in case of dynamic IP address assignment. The normal use case would be to have one IPv4
 *  and one IPv6 address which have each associated a prefix length (IPv6 only), a subnet
 *  mask, a gateway, and a primary and secondary DNS address.(3) For LTE a higher QoS may
 *  be established by setting up an additional bearer (“dedicated bearer”) in addition
 *  to the default bearer which is established to the default APN. A dedicated bearer which
 *  is set up by the network on request by the device containing a requested QCI value can
 *  either be established to the same APN as the default bearer or to another APN. The QoS
 *  of a dedicated bearer may be modified on request by the device. The association of QoS
 *  values and APNs for a subscriber is stored in the network and checked during the establishment
 *  of a bearer.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Human-readable identifier. Multiple connection profiles can share the same APN value but e.g. have different credentials.
    ProfilenameType Profilename;
    
    // Optional resource
    // 1 - Presented to network during connection to PDN e.g. ‘internet.15.234’.This resource is not included in case ‘Auto select APN by device’ resource has the value TRUE.If the APN resource is present but contains an empty string, then the device shall not provide an APN in the connection request (invoking default APN procedures in the network).
    APNType APN;
    
    // Optional resource
    // 2 - If this resource is present for a connection profile, it enables the device to choose an APN according to a device specific algorithm. It provides a fall-back mechanism e.g. for some MVNO SIMs the configured APN may not work.  Resource not included in case the ‘APN’ resource is specified.
    bool AutoselectAPNbydevice;
    
    // Optional resource
    // 3 - True: connection is activatedFalse: connection is de-activated.Allows the profile to be remotely activated or deactivated.
    bool Enablestatus;
    
    // 4 - Enumerated type:0: PAP1: CHAP2: PAP or CHAP3: None
    int AuthenticationType;
    
    // Optional resource
    // 5 - Used with e.g. PAP.
    UserNameType UserName;
    
    // Optional resource
    // 6 - Used with e.g. PAP.
    SecretType Secret;
    
    // Optional resource
    // 7 - Comma separated list of retry delay values in seconds to be used in case of unsuccessful connection establishment attempts. e.g. “10,60,600,3600,86400”
    ReconnectScheduleType ReconnectSchedule;
    
    // Optional resource
    // 8 - Coma separated mobile country code, then mobile network code – for which this APN is valid.
    ValidityMCCMNCType ValidityMCCMNC;
    
    // Optional resource
    // 9 - UTC time of connection request. See note (1)
    Connectionestablishmenttime1Type Connectionestablishmenttime1; // Time
    
    // Optional resource
    // 10 - 0 = accepted1 = rejected
    int Connectionestablishmentresult1;
    
    // Optional resource
    // 11 - Reject cause, see [3GPP-TS_24.008, 3GPP-TS_24.301]
    int Connectionestablishmentrejectcause1;
    
    // Optional resource
    // 12 - UTC time of connection end.
    Connectionendtime1Type Connectionendtime1; // Time
    
    // Optional resource
    // 13 - Rolling counter for total number of bytes sent via this interface since last device reset.
    int TotalBytesSent;
    
    // Optional resource
    // 14 - Rolling counter for total number of bytes received via this interface since last device reset.
    int TotalBytesReceived;
    
    // Optional resource
    // 15 - May be IPv4 or IPv6 address.
    IPaddress2Type IPaddress2;
    
    // Optional resource
    // 16 - Associated with IPv6 address.
    Prefixlength2Type Prefixlength2;
    
    // Optional resource
    // 17 - Subnet mask.
    Subnetmask2Type Subnetmask2;
    
    // Optional resource
    // 18 - Gateway.
    Gateway2Type Gateway2;
    
    // Optional resource
    // 19 - Primary DNS address.
    PrimaryDNSaddress2Type PrimaryDNSaddress2;
    
    // Optional resource
    // 20 - Secondary DNS address.
    SecondaryDNSaddress2Type SecondaryDNSaddress2;
    
    // Optional resource
    // 21 - For LTE and NB-IoT onlyQCI=Quality of service Class IdentifierThis resource enables the LWM2M server to signal the LWM2M client which QCI it shall request from the network.See [3GPP-TS_23.203, and 3GPP-TS_24.301] for a description of QCI values. See note (3).
    int QCI3;
    
    // Optional resource
    // 22 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 23 - Rolling counter for total number of packets sent via this interface since last device reset.
    int TotalPacketsSent;
    
    // Optional resource
    // 24 - 0=Non-IP1=IPv42=IPv63=IPv4v6
    int PDNType;
    
    // Optional resource
    // 25 - Determines the number of allowed uplink PDU transmissions per time interval per APN.Rate Control information is part of the Protocol Configuration Options (PCO) according to [3GPP-TS_24.008 and 3GPP-TS_27.060]
    int APNRateControl;
    
};

enum class RESID {
    Profilename = 0,
    APN = 1,
    AutoselectAPNbydevice = 2,
    Enablestatus = 3,
    AuthenticationType = 4,
    UserName = 5,
    Secret = 6,
    ReconnectSchedule = 7,
    ValidityMCCMNC = 8,
    Connectionestablishmenttime1 = 9,
    Connectionestablishmentresult1 = 10,
    Connectionestablishmentrejectcause1 = 11,
    Connectionendtime1 = 12,
    TotalBytesSent = 13,
    TotalBytesReceived = 14,
    IPaddress2 = 15,
    Prefixlength2 = 16,
    Subnetmask2 = 17,
    Gateway2 = 18,
    PrimaryDNSaddress2 = 19,
    SecondaryDNSaddress2 = 20,
    QCI3 = 21,
    Vendorspecificextensions = 22,
    TotalPacketsSent = 23,
    PDNType = 24,
    APNRateControl = 25,
    
};

/* \brief Class for object 11 - APN connection profile
 *  This object specifies resources to enable a device to connect to an APN.Notes:(1) For
 *  each activated PDP context request, the device may store at least one value of ‘Connection
 *  establishment time’, ‘connection establishment result’, ‘Connection end time’
 *  and if activation is unsuccessful then a ‘connection establishment reject cause’.
 *  It is a device decision how many instances to keep.(2) These resources are used in case
 *  IP related parameters are defined statically, and are also set with the IP related parameters
 *  in case of dynamic IP address assignment. The normal use case would be to have one IPv4
 *  and one IPv6 address which have each associated a prefix length (IPv6 only), a subnet
 *  mask, a gateway, and a primary and secondary DNS address.(3) For LTE a higher QoS may
 *  be established by setting up an additional bearer (“dedicated bearer”) in addition
 *  to the default bearer which is established to the default APN. A dedicated bearer which
 *  is set up by the network on request by the device containing a requested QCI value can
 *  either be established to the same APN as the default bearer or to another APN. The QoS
 *  of a dedicated bearer may be modified on request by the device. The association of QoS
 *  values and APNs for a subscriber is stored in the network and checked during the establishment
 *  of a bearer.
 */
class object : public Lwm2mObject<11, object, instance> {
public:

    // 0 - Human-readable identifier. Multiple connection profiles can share the same APN value but e.g. have different credentials.
    Resource(0, &instance::Profilename, O_RES_RW) Profilename;
    
    // Optional resource
    // 1 - Presented to network during connection to PDN e.g. ‘internet.15.234’.This resource is not included in case ‘Auto select APN by device’ resource has the value TRUE.If the APN resource is present but contains an empty string, then the device shall not provide an APN in the connection request (invoking default APN procedures in the network).
    Resource(1, &instance::APN, O_RES_RW) APN;
    
    // Optional resource
    // 2 - If this resource is present for a connection profile, it enables the device to choose an APN according to a device specific algorithm. It provides a fall-back mechanism e.g. for some MVNO SIMs the configured APN may not work.  Resource not included in case the ‘APN’ resource is specified.
    Resource(2, &instance::AutoselectAPNbydevice, O_RES_RW) AutoselectAPNbydevice;
    
    // Optional resource
    // 3 - True: connection is activatedFalse: connection is de-activated.Allows the profile to be remotely activated or deactivated.
    Resource(3, &instance::Enablestatus, O_RES_RW) Enablestatus;
    
    // 4 - Enumerated type:0: PAP1: CHAP2: PAP or CHAP3: None
    Resource(4, &instance::AuthenticationType, O_RES_RW) AuthenticationType;
    
    // Optional resource
    // 5 - Used with e.g. PAP.
    Resource(5, &instance::UserName, O_RES_RW) UserName;
    
    // Optional resource
    // 6 - Used with e.g. PAP.
    Resource(6, &instance::Secret, O_RES_RW) Secret;
    
    // Optional resource
    // 7 - Comma separated list of retry delay values in seconds to be used in case of unsuccessful connection establishment attempts. e.g. “10,60,600,3600,86400”
    Resource(7, &instance::ReconnectSchedule, O_RES_RW) ReconnectSchedule;
    
    // Optional resource
    // 8 - Coma separated mobile country code, then mobile network code – for which this APN is valid.
    Resource(8, &instance::ValidityMCCMNC, O_RES_RW) ValidityMCCMNC;
    
    // Optional resource
    // 9 - UTC time of connection request. See note (1)
    Resource(9, &instance::Connectionestablishmenttime1, O_RES_R) Connectionestablishmenttime1;
    
    // Optional resource
    // 10 - 0 = accepted1 = rejected
    Resource(10, &instance::Connectionestablishmentresult1, O_RES_R) Connectionestablishmentresult1;
    
    // Optional resource
    // 11 - Reject cause, see [3GPP-TS_24.008, 3GPP-TS_24.301]
    Resource(11, &instance::Connectionestablishmentrejectcause1, O_RES_R) Connectionestablishmentrejectcause1;
    
    // Optional resource
    // 12 - UTC time of connection end.
    Resource(12, &instance::Connectionendtime1, O_RES_R) Connectionendtime1;
    
    // Optional resource
    // 13 - Rolling counter for total number of bytes sent via this interface since last device reset.
    Resource(13, &instance::TotalBytesSent, O_RES_R) TotalBytesSent;
    
    // Optional resource
    // 14 - Rolling counter for total number of bytes received via this interface since last device reset.
    Resource(14, &instance::TotalBytesReceived, O_RES_R) TotalBytesReceived;
    
    // Optional resource
    // 15 - May be IPv4 or IPv6 address.
    Resource(15, &instance::IPaddress2, O_RES_RW) IPaddress2;
    
    // Optional resource
    // 16 - Associated with IPv6 address.
    Resource(16, &instance::Prefixlength2, O_RES_RW) Prefixlength2;
    
    // Optional resource
    // 17 - Subnet mask.
    Resource(17, &instance::Subnetmask2, O_RES_RW) Subnetmask2;
    
    // Optional resource
    // 18 - Gateway.
    Resource(18, &instance::Gateway2, O_RES_RW) Gateway2;
    
    // Optional resource
    // 19 - Primary DNS address.
    Resource(19, &instance::PrimaryDNSaddress2, O_RES_RW) PrimaryDNSaddress2;
    
    // Optional resource
    // 20 - Secondary DNS address.
    Resource(20, &instance::SecondaryDNSaddress2, O_RES_RW) SecondaryDNSaddress2;
    
    // Optional resource
    // 21 - For LTE and NB-IoT onlyQCI=Quality of service Class IdentifierThis resource enables the LWM2M server to signal the LWM2M client which QCI it shall request from the network.See [3GPP-TS_23.203, and 3GPP-TS_24.301] for a description of QCI values. See note (3).
    Resource(21, &instance::QCI3, O_RES_R) QCI3;
    
    // Optional resource
    // 22 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 23 - Rolling counter for total number of packets sent via this interface since last device reset.
    Resource(23, &instance::TotalPacketsSent, O_RES_R) TotalPacketsSent;
    
    // Optional resource
    // 24 - 0=Non-IP1=IPv42=IPv63=IPv4v6
    Resource(24, &instance::PDNType, O_RES_RW) PDNType;
    
    // Optional resource
    // 25 - Determines the number of allowed uplink PDU transmissions per time interval per APN.Rate Control information is part of the Protocol Configuration Options (PCO) according to [3GPP-TS_24.008 and 3GPP-TS_27.060]
    Resource(25, &instance::APNRateControl, O_RES_R) APNRateControl;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id11::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id11::RESID c1) { return (uint16_t) c1 == c2; }
	