#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3367 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3367 - macRachAttemptReasonEvent
 *  RACH Information - reason for initiating RACH
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 = Connection-Request2 = Radio-Link-Failure3 = UL-Data-Arrival4 = DL-Data-Arrival5 = Handover
    int MacRachAttemptReasonType;
    
    // 1 - UE ID
    int ueID;
    
    // 2 - 1 = Contention based0 = otherwise
    bool contentionBased;
    
    // 3 - preamble= The random access preambles are generated from Zadoff-Chu sequences with zero correlation zone (3GPP TS 36.211)
    int preamble;
    
    // 4 - 0: Group A, 1: Group B
    bool preambleGroupChosen;
    
};

enum class RESID {
    MacRachAttemptReasonType = 0,
    ueID = 1,
    contentionBased = 2,
    preamble = 3,
    preambleGroupChosen = 4,
    
};

/* \brief Class for object 3367 - macRachAttemptReasonEvent
 *  RACH Information - reason for initiating RACH
 */
class object : public Lwm2mObject<3367, object, instance> {
public:

    // 0 - 1 = Connection-Request2 = Radio-Link-Failure3 = UL-Data-Arrival4 = DL-Data-Arrival5 = Handover
    Resource(0, &instance::MacRachAttemptReasonType, O_RES_R) MacRachAttemptReasonType;
    
    // 1 - UE ID
    Resource(1, &instance::ueID, O_RES_R) ueID;
    
    // 2 - 1 = Contention based0 = otherwise
    Resource(2, &instance::contentionBased, O_RES_R) contentionBased;
    
    // 3 - preamble= The random access preambles are generated from Zadoff-Chu sequences with zero correlation zone (3GPP TS 36.211)
    Resource(3, &instance::preamble, O_RES_R) preamble;
    
    // 4 - 0: Group A, 1: Group B
    Resource(4, &instance::preambleGroupChosen, O_RES_R) preambleGroupChosen;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3367::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3367::RESID c1) { return (uint16_t) c1 == c2; }
	