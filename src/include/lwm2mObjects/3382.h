#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3382 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3382 - SipRegistrationEvent
 *  SIP Registration status
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 = Normal2 = Emergency
    int registrationType;
    
    // 1 - 0 = Success (when 200 OK is received)1 = Failure (when any error other than 401 is received, else when 408 timeout occurs)
    int registrationResult;
    
};

enum class RESID {
    registrationType = 0,
    registrationResult = 1,
    
};

/* \brief Class for object 3382 - SipRegistrationEvent
 *  SIP Registration status
 */
class object : public Lwm2mObject<3382, object, instance> {
public:

    // 0 - 1 = Normal2 = Emergency
    Resource(0, &instance::registrationType, O_RES_R) registrationType;
    
    // 1 - 0 = Success (when 200 OK is received)1 = Failure (when any error other than 401 is received, else when 408 timeout occurs)
    Resource(1, &instance::registrationResult, O_RES_R) registrationResult;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3382::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3382::RESID c1) { return (uint16_t) c1 == c2; }
	