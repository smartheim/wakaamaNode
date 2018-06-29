#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id17 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 17 - Communication Characteristics
 *  This object enables configuration of various generic communications parameters.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Maximum uplink packet size supported by the communications channel.In case of 3GPP NB-IoT this applies to the maximum uplink packet size supported via the Non Access Stratum (NAS). This information can be retrieved via the Protocol Configuration Options as defined in 3GPP TS 24.008. 
    int Maximumuplinkpacketsize;
    
    // Optional resource
    // 1 - Maximum downlink packet size supported by the communications channel, and supported by the device buffer.
    int Maximumdownlinkpacketsize;
    
    // Optional resource
    // 2 - See [RFC 7252 CoAP]
    int CoAPACKTIMEOUT;
    
    // Optional resource
    // 3 - See [RFC 7252 CoAP]
    int CoAPACKRANDOMFACTOR;
    
    // Optional resource
    // 4 - See [RFC 7252 CoAP]
    int CoAPMAXRETRANSMIT;
    
    // Optional resource
    // 5 - See [RFC 7252 CoAP]
    int CoAPNSTART;
    
    // Optional resource
    // 6 - See [RFC 7252 CoAP]
    int CoAPDEFAULTLEISURE;
    
    // Optional resource
    // 7 - See [RFC 7252 CoAP]
    int CoAPPROBINGRATE;
    
};

enum class RESID {
    Maximumuplinkpacketsize = 0,
    Maximumdownlinkpacketsize = 1,
    CoAPACKTIMEOUT = 2,
    CoAPACKRANDOMFACTOR = 3,
    CoAPMAXRETRANSMIT = 4,
    CoAPNSTART = 5,
    CoAPDEFAULTLEISURE = 6,
    CoAPPROBINGRATE = 7,
    
};

/* \brief Class for object 17 - Communication Characteristics
 *  This object enables configuration of various generic communications parameters.
 */
class object : public Lwm2mObject<17, object, instance> {
public:

    // Optional resource
    // 0 - Maximum uplink packet size supported by the communications channel.In case of 3GPP NB-IoT this applies to the maximum uplink packet size supported via the Non Access Stratum (NAS). This information can be retrieved via the Protocol Configuration Options as defined in 3GPP TS 24.008. 
    Resource(0, &instance::Maximumuplinkpacketsize, O_RES_R) Maximumuplinkpacketsize;
    
    // Optional resource
    // 1 - Maximum downlink packet size supported by the communications channel, and supported by the device buffer.
    Resource(1, &instance::Maximumdownlinkpacketsize, O_RES_R) Maximumdownlinkpacketsize;
    
    // Optional resource
    // 2 - See [RFC 7252 CoAP]
    Resource(2, &instance::CoAPACKTIMEOUT, O_RES_RW) CoAPACKTIMEOUT;
    
    // Optional resource
    // 3 - See [RFC 7252 CoAP]
    Resource(3, &instance::CoAPACKRANDOMFACTOR, O_RES_RW) CoAPACKRANDOMFACTOR;
    
    // Optional resource
    // 4 - See [RFC 7252 CoAP]
    Resource(4, &instance::CoAPMAXRETRANSMIT, O_RES_RW) CoAPMAXRETRANSMIT;
    
    // Optional resource
    // 5 - See [RFC 7252 CoAP]
    Resource(5, &instance::CoAPNSTART, O_RES_RW) CoAPNSTART;
    
    // Optional resource
    // 6 - See [RFC 7252 CoAP]
    Resource(6, &instance::CoAPDEFAULTLEISURE, O_RES_RW) CoAPDEFAULTLEISURE;
    
    // Optional resource
    // 7 - See [RFC 7252 CoAP]
    Resource(7, &instance::CoAPPROBINGRATE, O_RES_RW) CoAPPROBINGRATE;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id17::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id17::RESID c1) { return (uint16_t) c1 == c2; }
	