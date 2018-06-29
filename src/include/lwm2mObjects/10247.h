#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10247 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10247 - Neighbour Cell Report
 *  This LWM2M Object provides the neighbour cell report. The CrowdBox Measurements Object
 *  and the Connected UE Report Object have both Objlnk Resources pointing to this Object.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Physical Cell ID of neighbouring LTE cell, as defined in TS 36.211
    int NeighbourPCI;
    
    // Optional resource
    // 1 - Neighbour cell ID as specified by the cellIdentity field broadcast in SIB1 of the neighbour cell (see TS 36.331).
    int NeighbourCellID;
    
    // 2 - Current neighbour cell rank. Neighbour cells should be ordered (ranked) by the CrowdBox according to neighbour cell RSRP, with a higher RSRP corresponding to a lower index. Hence the neighbouring cell with the highest RSRP should be neighbour cell 0, the second neighbour cell 1, and so on.
    int NeighbourCellRank;
    
    // 3 - Neighbour cell RSRP, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    int NeighbourCellRSRP;
    
    // 4 - Neighbour cell RSRQ, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    int NeighbourCellRSRQ;
    
};

enum class RESID {
    NeighbourPCI = 0,
    NeighbourCellID = 1,
    NeighbourCellRank = 2,
    NeighbourCellRSRP = 3,
    NeighbourCellRSRQ = 4,
    
};

/* \brief Class for object 10247 - Neighbour Cell Report
 *  This LWM2M Object provides the neighbour cell report. The CrowdBox Measurements Object
 *  and the Connected UE Report Object have both Objlnk Resources pointing to this Object.
 */
class object : public Lwm2mObject<10247, object, instance> {
public:

    // 0 - Physical Cell ID of neighbouring LTE cell, as defined in TS 36.211
    Resource(0, &instance::NeighbourPCI, O_RES_R) NeighbourPCI;
    
    // Optional resource
    // 1 - Neighbour cell ID as specified by the cellIdentity field broadcast in SIB1 of the neighbour cell (see TS 36.331).
    Resource(1, &instance::NeighbourCellID, O_RES_R) NeighbourCellID;
    
    // 2 - Current neighbour cell rank. Neighbour cells should be ordered (ranked) by the CrowdBox according to neighbour cell RSRP, with a higher RSRP corresponding to a lower index. Hence the neighbouring cell with the highest RSRP should be neighbour cell 0, the second neighbour cell 1, and so on.
    Resource(2, &instance::NeighbourCellRank, O_RES_R) NeighbourCellRank;
    
    // 3 - Neighbour cell RSRP, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    Resource(3, &instance::NeighbourCellRSRP, O_RES_R) NeighbourCellRSRP;
    
    // 4 - Neighbour cell RSRQ, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    Resource(4, &instance::NeighbourCellRSRQ, O_RES_R) NeighbourCellRSRQ;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10247::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10247::RESID c1) { return (uint16_t) c1 == c2; }
	