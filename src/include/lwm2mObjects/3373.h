#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3373 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3373 - txPowerHeadroomEvent
 *  TX power headroom information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    int subFrameNumber;
    
    // 2 - headroom value in dB (-23..40)
    int headroomvalue;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    headroomvalue = 2,
    
};

/* \brief Class for object 3373 - txPowerHeadroomEvent
 *  TX power headroom information
 */
class object : public Lwm2mObject<3373, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - headroom value in dB (-23..40)
    Resource(2, &instance::headroomvalue, O_RES_R) headroomvalue;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3373::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3373::RESID c1) { return (uint16_t) c1 == c2; }
	