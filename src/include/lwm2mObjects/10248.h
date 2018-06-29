#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10248 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10248 - Connected UE Measurements
 *  This LWM2M Object provides a range of measurements of connected UEs and provides an
 *  Object link to the Connected UE report.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The number of different UEs currently connected to the eNB (i.e. in RRC_CONNECTED state).
    int NumberofConnectedUsers;
    
    // 1 - The number of different UEs that have connected to the eNB over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    int CumulativeNumberofUniqueUsers;
    
    // 2 - Provides an Object link to the Connected UE Report which provides a range of information related to the connected UEs.
    // Objlnk resources are not supported yet - ConnectedUEReport;
    
};

enum class RESID {
    NumberofConnectedUsers = 0,
    CumulativeNumberofUniqueUsers = 1,
    ConnectedUEReport = 2,
    
};

/* \brief Class for object 10248 - Connected UE Measurements
 *  This LWM2M Object provides a range of measurements of connected UEs and provides an
 *  Object link to the Connected UE report.
 */
class object : public Lwm2mObject<10248, object, instance> {
public:

    // 0 - The number of different UEs currently connected to the eNB (i.e. in RRC_CONNECTED state).
    Resource(0, &instance::NumberofConnectedUsers, O_RES_R) NumberofConnectedUsers;
    
    // 1 - The number of different UEs that have connected to the eNB over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    Resource(1, &instance::CumulativeNumberofUniqueUsers, O_RES_R) CumulativeNumberofUniqueUsers;
    
    // 2 - Provides an Object link to the Connected UE Report which provides a range of information related to the connected UEs.
    // Objlnk resources are not supported yet - ConnectedUEReport;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10248::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10248::RESID c1) { return (uint16_t) c1 == c2; }
	