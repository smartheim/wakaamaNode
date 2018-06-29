#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3383 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3383 - sipPublishEvent
 *  SIP Publish status
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - -1 = Publish message not available0 = Success (when 200 OK is received)1 = Failure (when any error other than 401 is received; else when 408 timeout occurs)
    int publishResult;
    
};

enum class RESID {
    publishResult = 0,
    
};

/* \brief Class for object 3383 - sipPublishEvent
 *  SIP Publish status
 */
class object : public Lwm2mObject<3383, object, instance> {
public:

    // 0 - -1 = Publish message not available0 = Success (when 200 OK is received)1 = Failure (when any error other than 401 is received; else when 408 timeout occurs)
    Resource(0, &instance::publishResult, O_RES_R) publishResult;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3383::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3383::RESID c1) { return (uint16_t) c1 == c2; }
	