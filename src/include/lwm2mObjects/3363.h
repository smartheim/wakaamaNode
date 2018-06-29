#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3363 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3363 - nasEsmExpiryEvent
 *  NAS ESM timer expiry information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 = t34802 = t34823 = t34814 = t3492
    int NasEsmExpiryEvent;
    
};

enum class RESID {
    NasEsmExpiryEvent = 0,
    
};

/* \brief Class for object 3363 - nasEsmExpiryEvent
 *  NAS ESM timer expiry information
 */
class object : public Lwm2mObject<3363, object, instance> {
public:

    // 0 - 1 = t34802 = t34823 = t34814 = t3492
    Resource(0, &instance::NasEsmExpiryEvent, O_RES_R) NasEsmExpiryEvent;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3363::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3363::RESID c1) { return (uint16_t) c1 == c2; }
	