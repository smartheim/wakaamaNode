#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10245 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10245 - Relay Management
 *  This LWM2M Object provides a range of eNB related measurements and parameters of which
 *  several are changeable. Furthermore, it includes Resources to enable/disable the
 *  eNB.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - This field indicates to the CCC whether or not the eNB of the CrowdBox is available for activation: AVAILABLE = TRUE; UNAVAILABLE = FALSE This is set by the CrowdBox itself using an algorithm specific to the use case and based on parameters known to the CrowdBox which may not necessarily be signalled to the network. In the absence of a more specific algorithm, this parameter should be set to AVAILABLE, unless a fault is detected which would prevent activation of the eNB, in which case it should be set to UNAVAILABLE.
    bool eNBAvailability;
    
    // 1 - States whether the CrowdBox GPS receiver is synchronised to GPS time or not: UNSYCHRONISED = FALSE; SYNCHRONISED = TRUE If more than one GPS receiver is used by the CrowdBox, then SYNCHRONISED should be reported only if all receivers are synchronised.
    bool GPSStatus;
    
    // Optional resource
    // 2 - Orientation of CrowdBox with respect to magnetic north. The reference orientation of the CrowdBox shall be the pointing direction of the eNB antenna(s) or, in the case of an omni-directional CrowdBox antenna, as defined in the accompanying product documentation.
    int Orientation;
    
    // 3 - EARFCN currently used by the eNB. Highest valid value in 3GPP is currently 46589. If the requested EARFCN is not supported by the eNB, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int eNBEARFCN;
    
    // 4 - Bandwidth of the currently used eNB carrier. If the requested bandwidth is not supported by the eNB, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int eNBBandwidth;
    
    // 5 - EARFCN of primary cell used for the backhaul. If the requested EARFCN is not supported by the CrowdBox UE, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int BackhaulPrimaryEARFCN;
    
    // 6 - EARFCN of any secondary cells used for the backhaul, in the event that carrier aggregation is being used. If the requested EARFCN is not supported by the CrowdBox UE, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int BackhaulSecondaryEARFCN;
    
    // 7 - The current measurement interval over which cumulative statistics are collected for the following resources: Cumulative Number of Unique Users, Cumulative Downlink Throughput per Connected User, Cumulative Uplink Throughput per Connected User. Note that this measurement period is a sliding window rather than a granularity period. Measurements should never be reset, but rather old measurements should be removed from the cumulative total as they fall outside of the window. A value of 0 shall be interpreted as meaning only the current value should be reported. A value of 65535 shall be interpreted as an infinite window size (i.e. old measurements are never discarded).
    int CumulativeMeasurementWindow;
    
    // 8 - A 28 bit E-UTRAN Cell Identifier (ECI)
    int eNBECI;
    
    // 9 - This resource indicates the current status of the eNB and can be used by the CCC to change the state from enabled to disabled. TRUE = eNB enabled FALSE = eNB disabled
    bool eNBStatus;
    
    // 10 - Enables the eNB. In addition the CrowdBox shall also update its configuration to reflect the current state of other relevant parameters. This might require a reboot.
    Executable EnableeNB;

    // 11 - Maximum power for the eNB measured as the sum of input powers to all antenna connectors. The maximum power per antenna port is equal to the maximum eNB power divided by the number of antenna ports. If the requested power is above or below the maximum or minimum power levels of the eNB, then the power level should be set to the maximum or minimum respectively. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int eNBMaximumPower;
    
    // 12 - q-OffsetFreq parameter for the backhaul primary EARFCN in SIB5 of the CrowdBox eNB BCCH. See TS 36.331 for details. Range: dB-24; dB-22 .. dB24 The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int BackhaulPrimaryqOffsetFreq;
    
    // 13 - q-OffsetFreq parameter for the backhaul secondary EARFCN in SIB5 of the CrowdBox eNB BCCH. See TS 36.331 for details Range: dB-24; dB-22 .. dB24 The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int BackhaulSecondaryqOffsetFreq;
    
    // 14 - EARFCN of a neighbour CrowdBox. Each instance of this resource relates to the same instance of resource ID 15.
    int NeighbourCrowdBoxEARFCN;
    
    // 15 - q-OffsetFreq parameter of the Neighbour CrowdBox EARFCN in SIB5 of the Neighbour CrowdBox eNB BCCH. See TS 36.331 for details Range: dB-24; dB-22 .. dB24 Each instance of this resource relates to the same instance of resource ID 14. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int NeighbourCrowdBoxqOffsetFreq;
    
    // 16 - Specifies the value of the cellIndividualOffset parameter applicable to the CrowdBox macro serving cell that is to be signalled to connected UEs in their measurement configuration information . See TS 36.331 for details. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    int ServingMacroeNBcellIndividualOffset;
    
};

enum class RESID {
    eNBAvailability = 0,
    GPSStatus = 1,
    Orientation = 2,
    eNBEARFCN = 3,
    eNBBandwidth = 4,
    BackhaulPrimaryEARFCN = 5,
    BackhaulSecondaryEARFCN = 6,
    CumulativeMeasurementWindow = 7,
    eNBECI = 8,
    eNBStatus = 9,
    EnableeNB = 10,
    eNBMaximumPower = 11,
    BackhaulPrimaryqOffsetFreq = 12,
    BackhaulSecondaryqOffsetFreq = 13,
    NeighbourCrowdBoxEARFCN = 14,
    NeighbourCrowdBoxqOffsetFreq = 15,
    ServingMacroeNBcellIndividualOffset = 16,
    
};

/* \brief Class for object 10245 - Relay Management
 *  This LWM2M Object provides a range of eNB related measurements and parameters of which
 *  several are changeable. Furthermore, it includes Resources to enable/disable the
 *  eNB.
 */
class object : public Lwm2mObject<10245, object, instance> {
public:

    // 0 - This field indicates to the CCC whether or not the eNB of the CrowdBox is available for activation: AVAILABLE = TRUE; UNAVAILABLE = FALSE This is set by the CrowdBox itself using an algorithm specific to the use case and based on parameters known to the CrowdBox which may not necessarily be signalled to the network. In the absence of a more specific algorithm, this parameter should be set to AVAILABLE, unless a fault is detected which would prevent activation of the eNB, in which case it should be set to UNAVAILABLE.
    Resource(0, &instance::eNBAvailability, O_RES_R) eNBAvailability;
    
    // 1 - States whether the CrowdBox GPS receiver is synchronised to GPS time or not: UNSYCHRONISED = FALSE; SYNCHRONISED = TRUE If more than one GPS receiver is used by the CrowdBox, then SYNCHRONISED should be reported only if all receivers are synchronised.
    Resource(1, &instance::GPSStatus, O_RES_R) GPSStatus;
    
    // Optional resource
    // 2 - Orientation of CrowdBox with respect to magnetic north. The reference orientation of the CrowdBox shall be the pointing direction of the eNB antenna(s) or, in the case of an omni-directional CrowdBox antenna, as defined in the accompanying product documentation.
    Resource(2, &instance::Orientation, O_RES_R) Orientation;
    
    // 3 - EARFCN currently used by the eNB. Highest valid value in 3GPP is currently 46589. If the requested EARFCN is not supported by the eNB, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(3, &instance::eNBEARFCN, O_RES_RW) eNBEARFCN;
    
    // 4 - Bandwidth of the currently used eNB carrier. If the requested bandwidth is not supported by the eNB, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(4, &instance::eNBBandwidth, O_RES_RW) eNBBandwidth;
    
    // 5 - EARFCN of primary cell used for the backhaul. If the requested EARFCN is not supported by the CrowdBox UE, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(5, &instance::BackhaulPrimaryEARFCN, O_RES_RW) BackhaulPrimaryEARFCN;
    
    // 6 - EARFCN of any secondary cells used for the backhaul, in the event that carrier aggregation is being used. If the requested EARFCN is not supported by the CrowdBox UE, the response should be "Bad Request". The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(6, &instance::BackhaulSecondaryEARFCN, O_RES_RW) BackhaulSecondaryEARFCN;
    
    // 7 - The current measurement interval over which cumulative statistics are collected for the following resources: Cumulative Number of Unique Users, Cumulative Downlink Throughput per Connected User, Cumulative Uplink Throughput per Connected User. Note that this measurement period is a sliding window rather than a granularity period. Measurements should never be reset, but rather old measurements should be removed from the cumulative total as they fall outside of the window. A value of 0 shall be interpreted as meaning only the current value should be reported. A value of 65535 shall be interpreted as an infinite window size (i.e. old measurements are never discarded).
    Resource(7, &instance::CumulativeMeasurementWindow, O_RES_RW) CumulativeMeasurementWindow;
    
    // 8 - A 28 bit E-UTRAN Cell Identifier (ECI)
    Resource(8, &instance::eNBECI, O_RES_R) eNBECI;
    
    // 9 - This resource indicates the current status of the eNB and can be used by the CCC to change the state from enabled to disabled. TRUE = eNB enabled FALSE = eNB disabled
    Resource(9, &instance::eNBStatus, O_RES_RW) eNBStatus;
    
    // 10 - Enables the eNB. In addition the CrowdBox shall also update its configuration to reflect the current state of other relevant parameters. This might require a reboot.
    Resource(10, &instance::EnableeNB) EnableeNB;
    
    // 11 - Maximum power for the eNB measured as the sum of input powers to all antenna connectors. The maximum power per antenna port is equal to the maximum eNB power divided by the number of antenna ports. If the requested power is above or below the maximum or minimum power levels of the eNB, then the power level should be set to the maximum or minimum respectively. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(11, &instance::eNBMaximumPower, O_RES_RW) eNBMaximumPower;
    
    // 12 - q-OffsetFreq parameter for the backhaul primary EARFCN in SIB5 of the CrowdBox eNB BCCH. See TS 36.331 for details. Range: dB-24; dB-22 .. dB24 The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(12, &instance::BackhaulPrimaryqOffsetFreq, O_RES_RW) BackhaulPrimaryqOffsetFreq;
    
    // 13 - q-OffsetFreq parameter for the backhaul secondary EARFCN in SIB5 of the CrowdBox eNB BCCH. See TS 36.331 for details Range: dB-24; dB-22 .. dB24 The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(13, &instance::BackhaulSecondaryqOffsetFreq, O_RES_RW) BackhaulSecondaryqOffsetFreq;
    
    // 14 - EARFCN of a neighbour CrowdBox. Each instance of this resource relates to the same instance of resource ID 15.
    Resource(14, &instance::NeighbourCrowdBoxEARFCN, O_RES_RW) NeighbourCrowdBoxEARFCN;
    
    // 15 - q-OffsetFreq parameter of the Neighbour CrowdBox EARFCN in SIB5 of the Neighbour CrowdBox eNB BCCH. See TS 36.331 for details Range: dB-24; dB-22 .. dB24 Each instance of this resource relates to the same instance of resource ID 14. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(15, &instance::NeighbourCrowdBoxqOffsetFreq, O_RES_RW) NeighbourCrowdBoxqOffsetFreq;
    
    // 16 - Specifies the value of the cellIndividualOffset parameter applicable to the CrowdBox macro serving cell that is to be signalled to connected UEs in their measurement configuration information . See TS 36.331 for details. The CrowdBox shall only apply a change of this resource upon execution of the “Enable eNB” command.
    Resource(16, &instance::ServingMacroeNBcellIndividualOffset, O_RES_RW) ServingMacroeNBcellIndividualOffset;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10245::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10245::RESID c1) { return (uint16_t) c1 == c2; }
	