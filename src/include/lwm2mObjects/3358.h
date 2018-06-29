#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3358 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3358 - rrcTimerExpiryEvent
 *  RRC timer expiry event information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 = t3002 = t3013 = t3024 = t3035 = t3046 = t3057 = t3118 = t3209 = t32110 = other
    int RrcTimerExpiryEvent;
    
};

enum class RESID {
    RrcTimerExpiryEvent = 0,
    
};

/* \brief Class for object 3358 - rrcTimerExpiryEvent
 *  RRC timer expiry event information
 */
class object : public Lwm2mObject<3358, object, instance> {
public:

    // 0 - 1 = t3002 = t3013 = t3024 = t3035 = t3046 = t3057 = t3118 = t3209 = t32110 = other
    Resource(0, &instance::RrcTimerExpiryEvent, O_RES_R) RrcTimerExpiryEvent;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3358::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3358::RESID c1) { return (uint16_t) c1 == c2; }
	