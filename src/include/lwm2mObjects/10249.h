#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10249 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10249 - Connected UE Report
 *  This LWM2M Object provides a range of information related to the connected UEs.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - MMEC signalled by the UE to the eNB in the RRCConnectionRequest message (see TS 36.331).
    int ConnectedUserMMEC;
    
    // 1 - M-TMSI signalled by the UE to the eNB in the RRCConnectionRequest message (see TS 36.331).
    int ConnectedUserMTMSI;
    
    // 2 - The RSRP of the CrowdBox eNB, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    int ServingCellCrowdBoxeNBRSRP;
    
    // 3 - The RSRQ of the CrowdBox eNB, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    int ServingCellCrowdBoxeNBRSRQ;
    
    // Optional resource
    // 4 - The cumulative timing advance signalled by the eNB to each currently connected UE. This is the sum of the initial timing advance signalled in the MAC payload of the Random Access Response (11 bits, 0 .. 1282) and subsequent adjustments signalled in the MAC PDU of DL-SCH transmissions (6 bits, -31 .. 32). See TS 36.321 for details.
    int CumulativeTimingAdvanceperConnectedUser;
    
    // 5 - The last downlink wideband CQI reported by a connected user the eNB. The CQI format is defined in Table 7.2.3-1 of TS 36.213.
    int LastdownlinkCQIreportperConnectedUser;
    
    // 6 - The total number of MAC bytes sent to the connected user over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    int CumulativeDownlinkThroughputperConnectedUser;
    
    // 7 - The total number of MAC bytes received from the connected user over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    int CumulativeUplinkThroughputperConnectedUser;
    
    // 8 - A link to the "Neighbour Cell Report" object for each neighbour cell reported to the CrowdBox by the connected UE
    // Objlnk resources are not supported yet - NeighbourCellReport;
    
};

enum class RESID {
    ConnectedUserMMEC = 0,
    ConnectedUserMTMSI = 1,
    ServingCellCrowdBoxeNBRSRP = 2,
    ServingCellCrowdBoxeNBRSRQ = 3,
    CumulativeTimingAdvanceperConnectedUser = 4,
    LastdownlinkCQIreportperConnectedUser = 5,
    CumulativeDownlinkThroughputperConnectedUser = 6,
    CumulativeUplinkThroughputperConnectedUser = 7,
    NeighbourCellReport = 8,
    
};

/* \brief Class for object 10249 - Connected UE Report
 *  This LWM2M Object provides a range of information related to the connected UEs.
 */
class object : public Lwm2mObject<10249, object, instance> {
public:

    // 0 - MMEC signalled by the UE to the eNB in the RRCConnectionRequest message (see TS 36.331).
    Resource(0, &instance::ConnectedUserMMEC, O_RES_R) ConnectedUserMMEC;
    
    // 1 - M-TMSI signalled by the UE to the eNB in the RRCConnectionRequest message (see TS 36.331).
    Resource(1, &instance::ConnectedUserMTMSI, O_RES_R) ConnectedUserMTMSI;
    
    // 2 - The RSRP of the CrowdBox eNB, as defined in TS 36.133, Section 9.1.4. Range: RSRP_00; RSRP_01 .. RSRP_97
    Resource(2, &instance::ServingCellCrowdBoxeNBRSRP, O_RES_R) ServingCellCrowdBoxeNBRSRP;
    
    // 3 - The RSRQ of the CrowdBox eNB, as defined in TS 36.133, Section 9.1.7. Range: RSRQ_-30; RSRQ_-29 .. RSRQ_46
    Resource(3, &instance::ServingCellCrowdBoxeNBRSRQ, O_RES_R) ServingCellCrowdBoxeNBRSRQ;
    
    // Optional resource
    // 4 - The cumulative timing advance signalled by the eNB to each currently connected UE. This is the sum of the initial timing advance signalled in the MAC payload of the Random Access Response (11 bits, 0 .. 1282) and subsequent adjustments signalled in the MAC PDU of DL-SCH transmissions (6 bits, -31 .. 32). See TS 36.321 for details.
    Resource(4, &instance::CumulativeTimingAdvanceperConnectedUser, O_RES_R) CumulativeTimingAdvanceperConnectedUser;
    
    // 5 - The last downlink wideband CQI reported by a connected user the eNB. The CQI format is defined in Table 7.2.3-1 of TS 36.213.
    Resource(5, &instance::LastdownlinkCQIreportperConnectedUser, O_RES_R) LastdownlinkCQIreportperConnectedUser;
    
    // 6 - The total number of MAC bytes sent to the connected user over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    Resource(6, &instance::CumulativeDownlinkThroughputperConnectedUser, O_RES_R) CumulativeDownlinkThroughputperConnectedUser;
    
    // 7 - The total number of MAC bytes received from the connected user over the immediately preceding period specified by the "Cumulative Measurement Window" field.
    Resource(7, &instance::CumulativeUplinkThroughputperConnectedUser, O_RES_R) CumulativeUplinkThroughputperConnectedUser;
    
    // 8 - A link to the "Neighbour Cell Report" object for each neighbour cell reported to the CrowdBox by the connected UE
    // Objlnk resources are not supported yet - NeighbourCellReport;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10249::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10249::RESID c1) { return (uint16_t) c1 == c2; }
	