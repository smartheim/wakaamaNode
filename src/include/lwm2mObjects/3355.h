#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3355 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3355 - handoverEvent
 *  handover event information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Modem time when handover is initiated
    int timeHandoverStart;
    
    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
    // 6033 - Cell Identity
    int CellID;
    
    // 3 - 0 = Pass1 = InvalidCfg (Validation failure)2 = PhysicalFailure (Physical layer failure on the target cell)3 = Rach (T304 expiry due to RACH failure on target cell)4 = RachMeasConfigIncluded (T304 expiry due to RACH failure on target cell when MeasConfig IE was included)5 = Other (other failure reason than ones above)
    int handoverResult;
    
    // 4 - Target EARFCN
    int TargetEarfcn;
    
    // 5 - Target Physical Cell ID
    int TargetPhysicalCellID;
    
    // 6 - Target Cell RSRP in dBm
    int targetCellRsrp;
    
};

enum class RESID {
    timeHandoverStart = 0,
    dlEarfcn = 6032,
    CellID = 6033,
    handoverResult = 3,
    TargetEarfcn = 4,
    TargetPhysicalCellID = 5,
    targetCellRsrp = 6,
    
};

/* \brief Class for object 3355 - handoverEvent
 *  handover event information
 */
class object : public Lwm2mObject<3355, object, instance> {
public:

    // 0 - Modem time when handover is initiated
    Resource(0, &instance::timeHandoverStart, O_RES_R) timeHandoverStart;
    
    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
    // 6033 - Cell Identity
    Resource(6033, &instance::CellID, O_RES_R) CellID;
    
    // 3 - 0 = Pass1 = InvalidCfg (Validation failure)2 = PhysicalFailure (Physical layer failure on the target cell)3 = Rach (T304 expiry due to RACH failure on target cell)4 = RachMeasConfigIncluded (T304 expiry due to RACH failure on target cell when MeasConfig IE was included)5 = Other (other failure reason than ones above)
    Resource(3, &instance::handoverResult, O_RES_R) handoverResult;
    
    // 4 - Target EARFCN
    Resource(4, &instance::TargetEarfcn, O_RES_R) TargetEarfcn;
    
    // 5 - Target Physical Cell ID
    Resource(5, &instance::TargetPhysicalCellID, O_RES_R) TargetPhysicalCellID;
    
    // 6 - Target Cell RSRP in dBm
    Resource(6, &instance::targetCellRsrp, O_RES_R) targetCellRsrp;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3355::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3355::RESID c1) { return (uint16_t) c1 == c2; }
	