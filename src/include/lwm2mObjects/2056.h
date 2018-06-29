#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2056 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2056 - CmdhBuffer
 *  This Object defines limits in usage of buffers for temporarily storing information
 *  that needs to be forwarded to other CSEs during processing of CMDH-related requests
 *  in a CSE.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains a list of event category values
    int ApplicableEventCategory;
    
    // 1 - Contains the max Buffer size of the CmdhBuffer Object Instance 
    int MaxBufferSize;
    
    // 2 - Storage priority for the buffered data associated to that CmdhBuffer Object Instance. t Buffered requests associated with a lower storage priority shall be purged before buffered requests with a higher storage priority.
    int StoragePriority;
    
};

enum class RESID {
    ApplicableEventCategory = 0,
    MaxBufferSize = 1,
    StoragePriority = 2,
    
};

/* \brief Class for object 2056 - CmdhBuffer
 *  This Object defines limits in usage of buffers for temporarily storing information
 *  that needs to be forwarded to other CSEs during processing of CMDH-related requests
 *  in a CSE.
 */
class object : public Lwm2mObject<2056, object, instance> {
public:

    // 0 - Contains a list of event category values
    Resource(0, &instance::ApplicableEventCategory, O_RES_RW) ApplicableEventCategory;
    
    // 1 - Contains the max Buffer size of the CmdhBuffer Object Instance 
    Resource(1, &instance::MaxBufferSize, O_RES_RW) MaxBufferSize;
    
    // 2 - Storage priority for the buffered data associated to that CmdhBuffer Object Instance. t Buffered requests associated with a lower storage priority shall be purged before buffered requests with a higher storage priority.
    Resource(2, &instance::StoragePriority, O_RES_RW) StoragePriority;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2056::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2056::RESID c1) { return (uint16_t) c1 == c2; }
	