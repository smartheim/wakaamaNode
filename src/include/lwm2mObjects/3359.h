#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3359 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3359 - cellBlacklistEvent
 *  Cell blacklist information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
    // 6033 - cell Identity
    int cellID;
    
};

enum class RESID {
    dlEarfcn = 6032,
    cellID = 6033,
    
};

/* \brief Class for object 3359 - cellBlacklistEvent
 *  Cell blacklist information
 */
class object : public Lwm2mObject<3359, object, instance> {
public:

    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
    // 6033 - cell Identity
    Resource(6033, &instance::cellID, O_RES_R) cellID;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3359::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3359::RESID c1) { return (uint16_t) c1 == c2; }
	