#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3377 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3377 - Message3Report
 *  RACH message 3 report information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - TPC
    int tpc;
    
    // 1 - Resource Indicator Value
    int resourceIndicatorValue;
    
    // 2 - CQI
    int cqi;
    
    // 3 - 0=no delay, 1=delay
    bool uplinkDelay;
    
    // 4 - 0=Disabled, 1=Enabled
    bool hoppingEnabled;
    
    // 5 - num RB
    int numRb;
    
    // 6 - Transport Block Size Index
    int transportBlockSizeIndex;
    
    // 7 - Modulation Type
    int ModulationType;
    
    // 8 - Redundancy Version Index
    int redundancyVersionIndex;
    
};

enum class RESID {
    tpc = 0,
    resourceIndicatorValue = 1,
    cqi = 2,
    uplinkDelay = 3,
    hoppingEnabled = 4,
    numRb = 5,
    transportBlockSizeIndex = 6,
    ModulationType = 7,
    redundancyVersionIndex = 8,
    
};

/* \brief Class for object 3377 - Message3Report
 *  RACH message 3 report information
 */
class object : public Lwm2mObject<3377, object, instance> {
public:

    // 0 - TPC
    Resource(0, &instance::tpc, O_RES_R) tpc;
    
    // 1 - Resource Indicator Value
    Resource(1, &instance::resourceIndicatorValue, O_RES_R) resourceIndicatorValue;
    
    // 2 - CQI
    Resource(2, &instance::cqi, O_RES_R) cqi;
    
    // 3 - 0=no delay, 1=delay
    Resource(3, &instance::uplinkDelay, O_RES_R) uplinkDelay;
    
    // 4 - 0=Disabled, 1=Enabled
    Resource(4, &instance::hoppingEnabled, O_RES_R) hoppingEnabled;
    
    // 5 - num RB
    Resource(5, &instance::numRb, O_RES_R) numRb;
    
    // 6 - Transport Block Size Index
    Resource(6, &instance::transportBlockSizeIndex, O_RES_R) transportBlockSizeIndex;
    
    // 7 - Modulation Type
    Resource(7, &instance::ModulationType, O_RES_R) ModulationType;
    
    // 8 - Redundancy Version Index
    Resource(8, &instance::redundancyVersionIndex, O_RES_R) redundancyVersionIndex;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3377::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3377::RESID c1) { return (uint16_t) c1 == c2; }
	