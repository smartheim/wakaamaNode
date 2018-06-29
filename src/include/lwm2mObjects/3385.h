#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3385 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3385 - volteCallStateChangeEvent
 *  VoLTE call status change
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 0 = Inactive call1 = Active call2 = Attempting3 = Hold
    int callStatus;
    
    // 1 - 0 = Not available1 = Normal Call Clearing2 = Call Drop
    int VolteCallStateChangeCause;
    
};

enum class RESID {
    callStatus = 0,
    VolteCallStateChangeCause = 1,
    
};

/* \brief Class for object 3385 - volteCallStateChangeEvent
 *  VoLTE call status change
 */
class object : public Lwm2mObject<3385, object, instance> {
public:

    // 0 - 0 = Inactive call1 = Active call2 = Attempting3 = Hold
    Resource(0, &instance::callStatus, O_RES_R) callStatus;
    
    // 1 - 0 = Not available1 = Normal Call Clearing2 = Call Drop
    Resource(1, &instance::VolteCallStateChangeCause, O_RES_R) VolteCallStateChangeCause;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3385::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3385::RESID c1) { return (uint16_t) c1 == c2; }
	