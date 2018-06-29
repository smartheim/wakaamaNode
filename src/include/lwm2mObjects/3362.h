#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3362 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3362 - nasEmmTimerExpiryEvent
 *  NAS EMM timer expiry information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 -    1 = t3410
    int NasEmmTimerExpiryEvent;
    
};

enum class RESID {
    NasEmmTimerExpiryEvent = 0,
    
};

/* \brief Class for object 3362 - nasEmmTimerExpiryEvent
 *  NAS EMM timer expiry information
 */
class object : public Lwm2mObject<3362, object, instance> {
public:

    // 0 -    1 = t3410
    Resource(0, &instance::NasEmmTimerExpiryEvent, O_RES_R) NasEmmTimerExpiryEvent;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3362::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3362::RESID c1) { return (uint16_t) c1 == c2; }
	