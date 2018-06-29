#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3357 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3357 - rrcStateChangeEvent
 *  Current RRC state change information, including the event that triggered the state
 *  change
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - RRC state       0 =  null        1 = idleCampedOnAnyCell        2 = idleCampedNormally       3 =  idlConnecting        4 = connectedNormally        5 = releasing(when going from connected to idle)
    int rrcState;
    
    // 1 - Trigger for RRC state change 0 = toNull (Generic cause for all state transitions to null state. From any stable state other than null to null state)1 = IdleFromUpperLayer (Camped due to connection aborted from upper layers. From any stable state to idlecampednormally)2 = idleT300Expiry (Camped due to T300expiry. From any stable state other than connectednormally to idlecampednormally)3= idleConnectionReject (Camped due to connection rejected from eNB. From any stable state other than connectednormally to idlecampednormally)4 = idleCellReselectionFailure (Camped due to cell reselection. From idlecampednormally to idlecampednormally)5 = idleBarred (Camped due to access barring. From any stable state to idlecampednormally)6 = idleOtherRrcFailue (Camped due to other reasons. From any stable state to idlecampednormally)7 = idleEnteringLte (From null to idlecampednormally)8 = connectingEmergencyCall (Enter connecting due to emergency call. Any stable state other than connectednormally to connectednormally)9 = connectingHighPriAccess (Enter connecting due to high priority access. From idlecampednormally to connectednormally)10 = connectingReceiveCall (Enter connecting due to receiving call. From idlecampednormally to connectednormally)11 = connectingMakingCall (Enter connecting due to making call. From idlecampednormally to connectednormally)12 = connectingMoData (Enter connecting due to originating a data session. From idlecampednormally to connectednormally)13 = connectedHoFailure (Camped on a cell in connected state due to handover failure. From connectednormally to idlecampednormally or idlecampedonanycell)14 = connectedOther (Camped on a cell in connected state due to other reasons. From connectednormally to idlecampednormally or idlecampedonanycell.15 = releasingT311Expriry (Enter releasing due to T311 expiry. From connected normally to idlecampednormally)16 = releasingT301Expriry (Enter releasing due to T301 expiry. From connected normally to idlecampednormally)17 = releasingReject (Enter releasing due to RRC connection reestablishment reject. From connected normally to idlecampednormally)18 = connectingOther (From idlecampednormally to connectednormally for other procedures like Extended service request, TAU, or RRC reestablishment
    int rrcStateChangeCause;
    
};

enum class RESID {
    rrcState = 0,
    rrcStateChangeCause = 1,
    
};

/* \brief Class for object 3357 - rrcStateChangeEvent
 *  Current RRC state change information, including the event that triggered the state
 *  change
 */
class object : public Lwm2mObject<3357, object, instance> {
public:

    // 0 - RRC state       0 =  null        1 = idleCampedOnAnyCell        2 = idleCampedNormally       3 =  idlConnecting        4 = connectedNormally        5 = releasing(when going from connected to idle)
    Resource(0, &instance::rrcState, O_RES_R) rrcState;
    
    // 1 - Trigger for RRC state change 0 = toNull (Generic cause for all state transitions to null state. From any stable state other than null to null state)1 = IdleFromUpperLayer (Camped due to connection aborted from upper layers. From any stable state to idlecampednormally)2 = idleT300Expiry (Camped due to T300expiry. From any stable state other than connectednormally to idlecampednormally)3= idleConnectionReject (Camped due to connection rejected from eNB. From any stable state other than connectednormally to idlecampednormally)4 = idleCellReselectionFailure (Camped due to cell reselection. From idlecampednormally to idlecampednormally)5 = idleBarred (Camped due to access barring. From any stable state to idlecampednormally)6 = idleOtherRrcFailue (Camped due to other reasons. From any stable state to idlecampednormally)7 = idleEnteringLte (From null to idlecampednormally)8 = connectingEmergencyCall (Enter connecting due to emergency call. Any stable state other than connectednormally to connectednormally)9 = connectingHighPriAccess (Enter connecting due to high priority access. From idlecampednormally to connectednormally)10 = connectingReceiveCall (Enter connecting due to receiving call. From idlecampednormally to connectednormally)11 = connectingMakingCall (Enter connecting due to making call. From idlecampednormally to connectednormally)12 = connectingMoData (Enter connecting due to originating a data session. From idlecampednormally to connectednormally)13 = connectedHoFailure (Camped on a cell in connected state due to handover failure. From connectednormally to idlecampednormally or idlecampedonanycell)14 = connectedOther (Camped on a cell in connected state due to other reasons. From connectednormally to idlecampednormally or idlecampedonanycell.15 = releasingT311Expriry (Enter releasing due to T311 expiry. From connected normally to idlecampednormally)16 = releasingT301Expriry (Enter releasing due to T301 expiry. From connected normally to idlecampednormally)17 = releasingReject (Enter releasing due to RRC connection reestablishment reject. From connected normally to idlecampednormally)18 = connectingOther (From idlecampednormally to connectednormally for other procedures like Extended service request, TAU, or RRC reestablishment
    Resource(1, &instance::rrcStateChangeCause, O_RES_R) rrcStateChangeCause;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3357::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3357::RESID c1) { return (uint16_t) c1 == c2; }
	