#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3364 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3364 - emmFailureCauseEvent
 *  Triggered at EMM failure - failure cause is logged
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - EMM Failure Causes - 3GPP 24.301
    int EMMCause;
    
};

enum class RESID {
    EMMCause = 0,
    
};

/* \brief Class for object 3364 - emmFailureCauseEvent
 *  Triggered at EMM failure - failure cause is logged
 */
class object : public Lwm2mObject<3364, object, instance> {
public:

    // 0 - EMM Failure Causes - 3GPP 24.301
    Resource(0, &instance::EMMCause, O_RES_R) EMMCause;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3364::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3364::RESID c1) { return (uint16_t) c1 == c2; }
	