#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3372 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3372 - TimingAdvance
 *  Timing Advance Information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    int subFrameNumber;
    
    // 2 - in TA units microseconds
    int timingAdvance;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    timingAdvance = 2,
    
};

/* \brief Class for object 3372 - TimingAdvance
 *  Timing Advance Information
 */
class object : public Lwm2mObject<3372, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - in TA units microseconds
    Resource(2, &instance::timingAdvance, O_RES_R) timingAdvance;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3372::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3372::RESID c1) { return (uint16_t) c1 == c2; }
	