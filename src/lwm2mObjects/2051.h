#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id2051 {
/* \brief Class for object 2051 - CmdhDefEcValues
 *  This Object represents default set of values for the Event Category parameter of an
 *  incoming request or response message.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains an index defining the order of processing this CmdhDefEcValue Object Instance will be handled
    int Order;
    
    // 1 - Represents the default Event category value to be applied when the conditions given in this Object Instance are matched
    PreallocString<30> DefEcValue;
    
    // 2 - List of zero or more Local AE-IDs, App-IDs, or the strings “localAE” or “thisCSE”
    PreallocString<30> RequestOrigin;
    
    // Optional resource
    // 3 - Contains the requestContext information of this Object Instance which needs to be matched  
    PreallocString<30> RequestContext;
    
    // Optional resource
    // 4 - Contains true/false flag indicating whether or not notification procedures apply.
    bool RequestContextNotification;
    
    // Optional resource
    // 5 - Represents conditions pertaining to the request itself, (e.g. the requested Response Type  ) than needs to be matched
    PreallocString<30> RequestCharacteristics;
    
    enum class RESID {
        Order = 0,
        DefEcValue = 1,
        RequestOrigin = 2,
        RequestContext = 3,
        RequestContextNotification = 4,
        RequestCharacteristics = 5,
        
    };
};

/* \brief Class for object 2051 - CmdhDefEcValues
 *  This Object represents default set of values for the Event Category parameter of an
 *  incoming request or response message.
 */
class object : public Lwm2mObject<2051, object, instance> {
public:

    // 0 - Contains an index defining the order of processing this CmdhDefEcValue Object Instance will be handled
    Resource(0, &instance::Order, O_RES_RW) Order;
    
    // 1 - Represents the default Event category value to be applied when the conditions given in this Object Instance are matched
    Resource(1, &instance::DefEcValue, O_RES_RW) DefEcValue;
    
    // 2 - List of zero or more Local AE-IDs, App-IDs, or the strings “localAE” or “thisCSE”
    Resource(2, &instance::RequestOrigin, O_RES_RW) RequestOrigin;
    
    // Optional resource
    // 3 - Contains the requestContext information of this Object Instance which needs to be matched  
    Resource(3, &instance::RequestContext, O_RES_RW) RequestContext;
    
    // Optional resource
    // 4 - Contains true/false flag indicating whether or not notification procedures apply.
    Resource(4, &instance::RequestContextNotification, O_RES_RW) RequestContextNotification;
    
    // Optional resource
    // 5 - Represents conditions pertaining to the request itself, (e.g. the requested Response Type  ) than needs to be matched
    Resource(5, &instance::RequestCharacteristics, O_RES_RW) RequestCharacteristics;
    
};

} // end of id namespace
inline bool operator== (id2051::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id2051::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	