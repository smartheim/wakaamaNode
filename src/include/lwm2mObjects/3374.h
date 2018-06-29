#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3374 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3374 - radioLinkMonitoring
 *  Radio Link monitoring information maintained by RRC
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    int subFrameNumber;
    
    // 2 - out of sync count
    int outOfSyncCount;
    
    // 3 - in Sync Count
    int inSyncCount;
    
    // 4 - 0=stopped, 1=running
    bool t310Timer;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    outOfSyncCount = 2,
    inSyncCount = 3,
    t310Timer = 4,
    
};

/* \brief Class for object 3374 - radioLinkMonitoring
 *  Radio Link monitoring information maintained by RRC
 */
class object : public Lwm2mObject<3374, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - out of sync count
    Resource(2, &instance::outOfSyncCount, O_RES_R) outOfSyncCount;
    
    // 3 - in Sync Count
    Resource(3, &instance::inSyncCount, O_RES_R) inSyncCount;
    
    // 4 - 0=stopped, 1=running
    Resource(4, &instance::t310Timer, O_RES_R) t310Timer;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3374::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3374::RESID c1) { return (uint16_t) c1 == c2; }
	