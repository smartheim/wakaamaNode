#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3376 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3376 - txPowerBackOffEvent
 *  TX Power backoff information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - TX Power Backoff
    int TxPowerBackoff;
    
};

enum class RESID {
    TxPowerBackoff = 0,
    
};

/* \brief Class for object 3376 - txPowerBackOffEvent
 *  TX Power backoff information
 */
class object : public Lwm2mObject<3376, object, instance> {
public:

    // 0 - TX Power Backoff
    Resource(0, &instance::TxPowerBackoff, O_RES_R) TxPowerBackoff;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3376::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3376::RESID c1) { return (uint16_t) c1 == c2; }
	