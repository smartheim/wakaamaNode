#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3380 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3380 - PrachReport
 *  PRACH report information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    bool subFrameNumber;
    
    // 2 - PRACH tx power in dB (-112..23)
    int rachTxPower;
    
    // 3 - ZadOFF Sequence Number (0..837)
    int zadOffSeqNum;
    
    // 4 - Random access preamble timing for a range of preamble formats (0..64)
    int prachConfig;
    
    // 5 - Preamble Format (0..4)
    int preambleFormat;
    
    // 6 - Max number of HARQ re-transmissions from UE for RACH message 3 (1..8)
    int maxTransmissionMsg3;
    
    // 7 - Window size for reception of RACH message 2 (2..10)
    int raResponseWindowSize;
    
    // 8 - RACH Request success/failure - 0=fail, 1=pass
    bool RachRequestResult;
    
    // 9 - CE_mode
    int cemode;
    
    // 10 - CE level
    int celevel;
    
    // 11 - Number of PRACH Repetitions
    int numprachrepetition;
    
    // 12 - PRACH Repetition seq
    int prachrepetitionseq;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    rachTxPower = 2,
    zadOffSeqNum = 3,
    prachConfig = 4,
    preambleFormat = 5,
    maxTransmissionMsg3 = 6,
    raResponseWindowSize = 7,
    RachRequestResult = 8,
    cemode = 9,
    celevel = 10,
    numprachrepetition = 11,
    prachrepetitionseq = 12,
    
};

/* \brief Class for object 3380 - PrachReport
 *  PRACH report information
 */
class object : public Lwm2mObject<3380, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 2 - PRACH tx power in dB (-112..23)
    Resource(2, &instance::rachTxPower, O_RES_R) rachTxPower;
    
    // 3 - ZadOFF Sequence Number (0..837)
    Resource(3, &instance::zadOffSeqNum, O_RES_R) zadOffSeqNum;
    
    // 4 - Random access preamble timing for a range of preamble formats (0..64)
    Resource(4, &instance::prachConfig, O_RES_R) prachConfig;
    
    // 5 - Preamble Format (0..4)
    Resource(5, &instance::preambleFormat, O_RES_R) preambleFormat;
    
    // 6 - Max number of HARQ re-transmissions from UE for RACH message 3 (1..8)
    Resource(6, &instance::maxTransmissionMsg3, O_RES_R) maxTransmissionMsg3;
    
    // 7 - Window size for reception of RACH message 2 (2..10)
    Resource(7, &instance::raResponseWindowSize, O_RES_R) raResponseWindowSize;
    
    // 8 - RACH Request success/failure - 0=fail, 1=pass
    Resource(8, &instance::RachRequestResult, O_RES_R) RachRequestResult;
    
    // 9 - CE_mode
    Resource(9, &instance::cemode, O_RES_R) cemode;
    
    // 10 - CE level
    Resource(10, &instance::celevel, O_RES_R) celevel;
    
    // 11 - Number of PRACH Repetitions
    Resource(11, &instance::numprachrepetition, O_RES_R) numprachrepetition;
    
    // 12 - PRACH Repetition seq
    Resource(12, &instance::prachrepetitionseq, O_RES_R) prachrepetitionseq;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3380::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3380::RESID c1) { return (uint16_t) c1 == c2; }
	