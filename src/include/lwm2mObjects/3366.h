#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3366 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3366 - macRachAttemptEvent
 *  RACH information. Logged at RACH TX
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - RACH Attempt Counter
    int rachAttemptCounter;
    
    // 1 - 0 = Success1 = Failure-At-Msg-22 = Failure-At-Msg-4-CT-Timer-Expired3 = Failure-At-Msg-4-CT-Resolution-Not-Passed4 = Aborted
    int MacRachAttemptEventType;
    
    // 2 - 1 = Contention based0 = otherwise
    bool contentionBased;
    
    // 3 - 1 = MSG 12 = MSG 23 = MSG 3
    int rachMessage;
    
    // 4 - preambleIndex=There are 64 preambles available in each cell. Range is from 0-63. (3GPP 36.211)
    int preambleIndex;
    
    // 5 - preamblePowerOffset= stepsize*preamble transmission number
    int preamblePowerOffset;
    
    // 6 - Backoff Time
    int backoffTime;
    
    // 7 - 1 = pass0 = fail
    bool msg2Result;
    
    // 8 - Timing Adjustment Value
    int timingAdjustmentValue;
    
};

enum class RESID {
    rachAttemptCounter = 0,
    MacRachAttemptEventType = 1,
    contentionBased = 2,
    rachMessage = 3,
    preambleIndex = 4,
    preamblePowerOffset = 5,
    backoffTime = 6,
    msg2Result = 7,
    timingAdjustmentValue = 8,
    
};

/* \brief Class for object 3366 - macRachAttemptEvent
 *  RACH information. Logged at RACH TX
 */
class object : public Lwm2mObject<3366, object, instance> {
public:

    // 0 - RACH Attempt Counter
    Resource(0, &instance::rachAttemptCounter, O_RES_R) rachAttemptCounter;
    
    // 1 - 0 = Success1 = Failure-At-Msg-22 = Failure-At-Msg-4-CT-Timer-Expired3 = Failure-At-Msg-4-CT-Resolution-Not-Passed4 = Aborted
    Resource(1, &instance::MacRachAttemptEventType, O_RES_R) MacRachAttemptEventType;
    
    // 2 - 1 = Contention based0 = otherwise
    Resource(2, &instance::contentionBased, O_RES_R) contentionBased;
    
    // 3 - 1 = MSG 12 = MSG 23 = MSG 3
    Resource(3, &instance::rachMessage, O_RES_R) rachMessage;
    
    // 4 - preambleIndex=There are 64 preambles available in each cell. Range is from 0-63. (3GPP 36.211)
    Resource(4, &instance::preambleIndex, O_RES_R) preambleIndex;
    
    // 5 - preamblePowerOffset= stepsize*preamble transmission number
    Resource(5, &instance::preamblePowerOffset, O_RES_R) preamblePowerOffset;
    
    // 6 - Backoff Time
    Resource(6, &instance::backoffTime, O_RES_R) backoffTime;
    
    // 7 - 1 = pass0 = fail
    Resource(7, &instance::msg2Result, O_RES_R) msg2Result;
    
    // 8 - Timing Adjustment Value
    Resource(8, &instance::timingAdjustmentValue, O_RES_R) timingAdjustmentValue;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3366::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3366::RESID c1) { return (uint16_t) c1 == c2; }
	