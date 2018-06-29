#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2057 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2057 - CmdhBackOffParametersSet
 *  This Object defines set of parameters which can be referenced by a specific Instance
 *  of the CmdhNwAccessRule Object (ID: 2055)
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Contains specific action actually  attempted on the network (e.g. cellular-registration)
    int NetworkAction;
    
    // 1 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for the Initial wait time. 
    int InitialBackoffTime;
    
    // 2 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for an additional wait tme.
    int AdditionalBackoffTime;
    
    // 3 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for the maximum wait time
    int MaximumBackoffTime;
    
    // Optional resource
    // 4 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for an optional random wait time.
    int OptionalRandomBackoffTime;
    
};

enum class RESID {
    NetworkAction = 0,
    InitialBackoffTime = 1,
    AdditionalBackoffTime = 2,
    MaximumBackoffTime = 3,
    OptionalRandomBackoffTime = 4,
    
};

/* \brief Class for object 2057 - CmdhBackOffParametersSet
 *  This Object defines set of parameters which can be referenced by a specific Instance
 *  of the CmdhNwAccessRule Object (ID: 2055)
 */
class object : public Lwm2mObject<2057, object, instance> {
public:

    // Optional resource
    // 0 - Contains specific action actually  attempted on the network (e.g. cellular-registration)
    Resource(0, &instance::NetworkAction, O_RES_RW) NetworkAction;
    
    // 1 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for the Initial wait time. 
    Resource(1, &instance::InitialBackoffTime, O_RES_RW) InitialBackoffTime;
    
    // 2 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for an additional wait tme.
    Resource(2, &instance::AdditionalBackoffTime, O_RES_RW) AdditionalBackoffTime;
    
    // 3 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for the maximum wait time
    Resource(3, &instance::MaximumBackoffTime, O_RES_RW) MaximumBackoffTime;
    
    // Optional resource
    // 4 - Regarding the BackOffParameters of a certain CmdhNwAccessRule  Object Instance, this Resource contains the value for an optional random wait time.
    Resource(4, &instance::OptionalRandomBackoffTime, O_RES_RW) OptionalRandomBackoffTime;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2057::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2057::RESID c1) { return (uint16_t) c1 == c2; }
	