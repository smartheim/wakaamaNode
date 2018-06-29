#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3386 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3386 - VoLTErtpPacketLoss
 *  Log is generated at the receiving end of RTP flow when newReceivedSequenceNumber -
 *  lastReceivedSequenceNumber > 1
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - id of RTP stream
    int ssrc;
    
    // 1 - Number of RTP packets lost
    int packetsLost;
    
};

enum class RESID {
    ssrc = 0,
    packetsLost = 1,
    
};

/* \brief Class for object 3386 - VoLTErtpPacketLoss
 *  Log is generated at the receiving end of RTP flow when newReceivedSequenceNumber -
 *  lastReceivedSequenceNumber > 1
 */
class object : public Lwm2mObject<3386, object, instance> {
public:

    // 0 - id of RTP stream
    Resource(0, &instance::ssrc, O_RES_R) ssrc;
    
    // 1 - Number of RTP packets lost
    Resource(1, &instance::packetsLost, O_RES_R) packetsLost;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3386::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3386::RESID c1) { return (uint16_t) c1 == c2; }
	