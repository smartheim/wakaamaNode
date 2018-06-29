#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3381 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3381 - VolteCallEvent
 *  VoLTE call status
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 0 = Inactive call1 = Active call2 = Attempting3 = Hold
    int callStatus;
    
    // 1 - 0 = Emergency1 = Voice call
    int callType;
    
};

enum class RESID {
    callStatus = 0,
    callType = 1,
    
};

/* \brief Class for object 3381 - VolteCallEvent
 *  VoLTE call status
 */
class object : public Lwm2mObject<3381, object, instance> {
public:

    // 0 - 0 = Inactive call1 = Active call2 = Attempting3 = Hold
    Resource(0, &instance::callStatus, O_RES_R) callStatus;
    
    // 1 - 0 = Emergency1 = Voice call
    Resource(1, &instance::callType, O_RES_R) callType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3381::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3381::RESID c1) { return (uint16_t) c1 == c2; }
	