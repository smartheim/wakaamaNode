#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3360 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3360 - esmContextInfo
 *  ESM context information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 0=default1=dedicated
    int contextType;
    
    // 1 - Bearer State0 = null1 = activeWaiting2 = active3 = modifying
    int bearerState;
    
    // 2 - Radio bearer ID corresponding to EPS Bearer ID of the context
    int radioBearerId;
    
    // 3 - QoS Class Identifier (TS 23.203)
    int qci;
    
};

enum class RESID {
    contextType = 0,
    bearerState = 1,
    radioBearerId = 2,
    qci = 3,
    
};

/* \brief Class for object 3360 - esmContextInfo
 *  ESM context information
 */
class object : public Lwm2mObject<3360, object, instance> {
public:

    // 0 - 0=default1=dedicated
    Resource(0, &instance::contextType, O_RES_R) contextType;
    
    // 1 - Bearer State0 = null1 = activeWaiting2 = active3 = modifying
    Resource(1, &instance::bearerState, O_RES_R) bearerState;
    
    // 2 - Radio bearer ID corresponding to EPS Bearer ID of the context
    Resource(2, &instance::radioBearerId, O_RES_R) radioBearerId;
    
    // 3 - QoS Class Identifier (TS 23.203)
    Resource(3, &instance::qci, O_RES_R) qci;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3360::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3360::RESID c1) { return (uint16_t) c1 == c2; }
	