#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10246 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10246 - CrowdBox Measurements
 *  This LWM2M Object provides CrowdBox-related measurements such as serving cell parameters,
 *  backhaul timing advance, and neighbour cell reports.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Serving cell ID as specified by the cellIdentity field broadcast in SIB1 of the serving cell (see TS 36.331).
    int ServingCellID;
    
    // 1 - Serving cell RSRP, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    int ServingCellRSRP;
    
    // 2 - Serving cell RSRQ, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    int ServingCellRSRQ;
    
    // 3 - SINR of serving cell as estimated by the CrowdBox. Note that this is a proprietary measurement dependent on the UE chipset manufacturer. The UE chipset used should be stated in the accompanying product documentation.
    int ServingCellSINR;
    
    // Optional resource
    // 4 - The cumulative timing advance signalled by the current serving cell to the CrowdBox. This is the sum of the initial timing advance signalled in the MAC payload of the Random Access Response (11 bits, 0 .. 1282) and subsequent adjustments signalled in the MAC PDU of DL-SCH transmissions (6 bits, -31 .. 32). See TS 36.321 for details.
    int CumulativeBackhaulTimingAdvance;
    
    // 5 - A link to the "Neighbour Cell Report" object for each neighbour cell of the CrowdBox.
    // Objlnk resources are not supported yet - NeighbourCellReport;
    
};

enum class RESID {
    ServingCellID = 0,
    ServingCellRSRP = 1,
    ServingCellRSRQ = 2,
    ServingCellSINR = 3,
    CumulativeBackhaulTimingAdvance = 4,
    NeighbourCellReport = 5,
    
};

/* \brief Class for object 10246 - CrowdBox Measurements
 *  This LWM2M Object provides CrowdBox-related measurements such as serving cell parameters,
 *  backhaul timing advance, and neighbour cell reports.
 */
class object : public Lwm2mObject<10246, object, instance> {
public:

    // 0 - Serving cell ID as specified by the cellIdentity field broadcast in SIB1 of the serving cell (see TS 36.331).
    Resource(0, &instance::ServingCellID, O_RES_R) ServingCellID;
    
    // 1 - Serving cell RSRP, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    Resource(1, &instance::ServingCellRSRP, O_RES_R) ServingCellRSRP;
    
    // 2 - Serving cell RSRQ, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    Resource(2, &instance::ServingCellRSRQ, O_RES_R) ServingCellRSRQ;
    
    // 3 - SINR of serving cell as estimated by the CrowdBox. Note that this is a proprietary measurement dependent on the UE chipset manufacturer. The UE chipset used should be stated in the accompanying product documentation.
    Resource(3, &instance::ServingCellSINR, O_RES_R) ServingCellSINR;
    
    // Optional resource
    // 4 - The cumulative timing advance signalled by the current serving cell to the CrowdBox. This is the sum of the initial timing advance signalled in the MAC payload of the Random Access Response (11 bits, 0 .. 1282) and subsequent adjustments signalled in the MAC PDU of DL-SCH transmissions (6 bits, -31 .. 32). See TS 36.321 for details.
    Resource(4, &instance::CumulativeBackhaulTimingAdvance, O_RES_R) CumulativeBackhaulTimingAdvance;
    
    // 5 - A link to the "Neighbour Cell Report" object for each neighbour cell of the CrowdBox.
    // Objlnk resources are not supported yet - NeighbourCellReport;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10246::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10246::RESID c1) { return (uint16_t) c1 == c2; }
	