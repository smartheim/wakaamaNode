#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3352 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3352 - plmnSearchEvent
 *  List of all PLMNs found during the initial search/scan
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Modem time when PLMN search is initiated
    int timeScanStart;
    
    // 6030 - PLMN - mcc/mnc
    int plmnID;
    
    // 6031 - Band Indicator
    int BandIndicator;
    
    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
};

enum class RESID {
    timeScanStart = 0,
    plmnID = 6030,
    BandIndicator = 6031,
    dlEarfcn = 6032,
    
};

/* \brief Class for object 3352 - plmnSearchEvent
 *  List of all PLMNs found during the initial search/scan
 */
class object : public Lwm2mObject<3352, object, instance> {
public:

    // 0 - Modem time when PLMN search is initiated
    Resource(0, &instance::timeScanStart, O_RES_R) timeScanStart;
    
    // 6030 - PLMN - mcc/mnc
    Resource(6030, &instance::plmnID, O_RES_R) plmnID;
    
    // 6031 - Band Indicator
    Resource(6031, &instance::BandIndicator, O_RES_R) BandIndicator;
    
    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3352::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3352::RESID c1) { return (uint16_t) c1 == c2; }
	