#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3353 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3353 - scellID
 *  serving cell information that the RRC decides to camp on
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6030 - PLMN - mcc/mnc
    int plmnID;
    
    // 6031 - Band Indicator
    int BandIndicator;
    
    // 2 - Tracking Area Code
    int TrackingAreaCode;
    
    // 6033 - Cell ID
    int CellID;
    
};

enum class RESID {
    plmnID = 6030,
    BandIndicator = 6031,
    TrackingAreaCode = 2,
    CellID = 6033,
    
};

/* \brief Class for object 3353 - scellID
 *  serving cell information that the RRC decides to camp on
 */
class object : public Lwm2mObject<3353, object, instance> {
public:

    // 6030 - PLMN - mcc/mnc
    Resource(6030, &instance::plmnID, O_RES_R) plmnID;
    
    // 6031 - Band Indicator
    Resource(6031, &instance::BandIndicator, O_RES_R) BandIndicator;
    
    // 2 - Tracking Area Code
    Resource(2, &instance::TrackingAreaCode, O_RES_R) TrackingAreaCode;
    
    // 6033 - Cell ID
    Resource(6033, &instance::CellID, O_RES_R) CellID;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3353::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3353::RESID c1) { return (uint16_t) c1 == c2; }
	