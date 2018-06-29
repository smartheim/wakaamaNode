#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3356 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3356 - radioLinkFailureEvent
 *  Radio Link Failure Event
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Modem time when RLF is occurred
    int timeRLF;
    
    // 1 - Radio Link Failure cause        0 = configurationFailue        1 = handoverFailure        2 = rachFailure,        3 = maxRetransmission,        4 = ipCheckFailue        5 = sibReadingFailure        6 = mibChange        7 = other
    int rlfCause;
    
};

enum class RESID {
    timeRLF = 0,
    rlfCause = 1,
    
};

/* \brief Class for object 3356 - radioLinkFailureEvent
 *  Radio Link Failure Event
 */
class object : public Lwm2mObject<3356, object, instance> {
public:

    // 0 - Modem time when RLF is occurred
    Resource(0, &instance::timeRLF, O_RES_R) timeRLF;
    
    // 1 - Radio Link Failure cause        0 = configurationFailue        1 = handoverFailure        2 = rachFailure,        3 = maxRetransmission,        4 = ipCheckFailue        5 = sibReadingFailure        6 = mibChange        7 = other
    Resource(1, &instance::rlfCause, O_RES_R) rlfCause;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3356::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3356::RESID c1) { return (uint16_t) c1 == c2; }
	