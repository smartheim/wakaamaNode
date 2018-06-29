#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3354 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3354 - cellReselectionEvent
 *  cell reselection event information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Modem time when reselection is initiated
    int timeReselectionStart;
    
    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
    // 6033 - Cell Identity
    int CellID;
    
    // 3 - 0 = Pass1= S-Failure2 =  Sib-Read-Failure3 = Weak-Downlink-Indicator4 = Cell-Barred5 = Non-Valid-Plmn6 = Forbidden-Tracking-Area7 = Aborted8 = Forbidden-CSG-Id9 = IRAT-Reselection-Failure10 = Frequency-Barred
    int failureType;
    
};

enum class RESID {
    timeReselectionStart = 0,
    dlEarfcn = 6032,
    CellID = 6033,
    failureType = 3,
    
};

/* \brief Class for object 3354 - cellReselectionEvent
 *  cell reselection event information
 */
class object : public Lwm2mObject<3354, object, instance> {
public:

    // 0 - Modem time when reselection is initiated
    Resource(0, &instance::timeReselectionStart, O_RES_R) timeReselectionStart;
    
    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
    // 6033 - Cell Identity
    Resource(6033, &instance::CellID, O_RES_R) CellID;
    
    // 3 - 0 = Pass1= S-Failure2 =  Sib-Read-Failure3 = Weak-Downlink-Indicator4 = Cell-Barred5 = Non-Valid-Plmn6 = Forbidden-Tracking-Area7 = Aborted8 = Forbidden-CSG-Id9 = IRAT-Reselection-Failure10 = Frequency-Barred
    Resource(3, &instance::failureType, O_RES_R) failureType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3354::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3354::RESID c1) { return (uint16_t) c1 == c2; }
	