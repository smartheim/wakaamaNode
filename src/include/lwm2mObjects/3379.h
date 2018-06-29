#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3379 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3379 - pucchPowerControl
 *  PUCCH TX power control information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    int subFrameNumber;
    
    // 2 - PUCCH Tx power measurement in dB (-112..23) 
    int pucchTxPowerValue;
    
    // 3 - Downlink path loss calculated in UE (0..255)
    int dlPathLoss;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    pucchTxPowerValue = 2,
    dlPathLoss = 3,
    
};

/* \brief Class for object 3379 - pucchPowerControl
 *  PUCCH TX power control information
 */
class object : public Lwm2mObject<3379, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - PUCCH Tx power measurement in dB (-112..23) 
    Resource(2, &instance::pucchTxPowerValue, O_RES_R) pucchTxPowerValue;
    
    // 3 - Downlink path loss calculated in UE (0..255)
    Resource(3, &instance::dlPathLoss, O_RES_R) dlPathLoss;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3379::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3379::RESID c1) { return (uint16_t) c1 == c2; }
	