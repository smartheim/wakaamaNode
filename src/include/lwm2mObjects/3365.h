#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3365 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3365 - rachLatency_delay
 *  RACH Latency & delay information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - sub Frame Number
    int subFrameNumber;
    
    // 2 - time in ms between 1st preamble and response from NW in DL
    int rachLatencyVal;
    
    // 3 - time in ms
    int delay;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    rachLatencyVal = 2,
    delay = 3,
    
};

/* \brief Class for object 3365 - rachLatency_delay
 *  RACH Latency & delay information
 */
class object : public Lwm2mObject<3365, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - time in ms between 1st preamble and response from NW in DL
    Resource(2, &instance::rachLatencyVal, O_RES_R) rachLatencyVal;
    
    // 3 - time in ms
    Resource(3, &instance::delay, O_RES_R) delay;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3365::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3365::RESID c1) { return (uint16_t) c1 == c2; }
	