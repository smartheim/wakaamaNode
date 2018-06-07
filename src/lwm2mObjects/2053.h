#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id2053 {
/* \brief Class for object 2053 - CmdhLimits
 *  This Object represents limits for CMDH related parameter values.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains index indicating in which order the concerned CmdhLimits Object Instance will be treated by the CSE to determine a value for the limit parameters.
    int Order;
    
    // 1 - List of zero or more Local AE-IDs, App-IDs, or the strings “localAE” or “thisCSE”
    PreallocString<30> RequestOrigin;
    
    // Optional resource
    // 2 - Represents the Dynamic Context condition under which CMDH parameter limits defined inside the concerned CmdhLimits Object Instance is applicable.
    PreallocString<30> RequestContext;
    
    // Optional resource
    // 3 - Contains true/false flag indicating whether or not notification procedures apply.
    bool RequestContextNotificatio;
    
    // Optional resource
    // 4 - Represents conditions pertaining to the request itself, (e.g. the requested Response Type  ) than needs to be matched
    PreallocString<30> RequestCharacteristics;
    
    // 5 - Allowed values for the Event Category parameter in a request of any of the Originators indicated in the requestOrigin attribute.
    int LimitsEventCategory;
    
    // 6 - Defines a range of values for the Request Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime 
    int LimitsRequestExpTime;
    
    // 7 - Defines a range of values for the Result Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    int LimitsResultExpTime;
    
    // 8 - Defines a range of values for the Operation Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    int LimitsOptExpTime;
    
    // 9 - Defines a range of values for the Result Persistence parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    int LimitsRespPersistence;
    
    // 10 - Contains the permitted settings of the DeliveryAggregation parameter of request primitives. '0' means 'False' '1' means 'True' '0 1' means 'False' or 'True'
    PreallocString<30> LimitsDelAggregation;
    
    enum class RESID {
        Order = 0,
        RequestOrigin = 1,
        RequestContext = 2,
        RequestContextNotificatio = 3,
        RequestCharacteristics = 4,
        LimitsEventCategory = 5,
        LimitsRequestExpTime = 6,
        LimitsResultExpTime = 7,
        LimitsOptExpTime = 8,
        LimitsRespPersistence = 9,
        LimitsDelAggregation = 10,
        
    };
};

/* \brief Class for object 2053 - CmdhLimits
 *  This Object represents limits for CMDH related parameter values.
 */
class object : public Lwm2mObject<2053, object, instance> {
public:

    // 0 - Contains index indicating in which order the concerned CmdhLimits Object Instance will be treated by the CSE to determine a value for the limit parameters.
    Resource(0, &instance::Order, O_RES_RW) Order;
    
    // 1 - List of zero or more Local AE-IDs, App-IDs, or the strings “localAE” or “thisCSE”
    Resource(1, &instance::RequestOrigin, O_RES_RW) RequestOrigin;
    
    // Optional resource
    // 2 - Represents the Dynamic Context condition under which CMDH parameter limits defined inside the concerned CmdhLimits Object Instance is applicable.
    Resource(2, &instance::RequestContext, O_RES_RW) RequestContext;
    
    // Optional resource
    // 3 - Contains true/false flag indicating whether or not notification procedures apply.
    Resource(3, &instance::RequestContextNotificatio, O_RES_RW) RequestContextNotificatio;
    
    // Optional resource
    // 4 - Represents conditions pertaining to the request itself, (e.g. the requested Response Type  ) than needs to be matched
    Resource(4, &instance::RequestCharacteristics, O_RES_RW) RequestCharacteristics;
    
    // 5 - Allowed values for the Event Category parameter in a request of any of the Originators indicated in the requestOrigin attribute.
    Resource(5, &instance::LimitsEventCategory, O_RES_RW) LimitsEventCategory;
    
    // 6 - Defines a range of values for the Request Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime 
    Resource(6, &instance::LimitsRequestExpTime, O_RES_RW) LimitsRequestExpTime;
    
    // 7 - Defines a range of values for the Result Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    Resource(7, &instance::LimitsResultExpTime, O_RES_RW) LimitsResultExpTime;
    
    // 8 - Defines a range of values for the Operation Expiration Time parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    Resource(8, &instance::LimitsOptExpTime, O_RES_RW) LimitsOptExpTime;
    
    // 9 - Defines a range of values for the Result Persistence parameter for a request of any Originator indicated in the requestOrigin ResourceInst 0 : minTimeInst 1:  maxTime
    Resource(9, &instance::LimitsRespPersistence, O_RES_RW) LimitsRespPersistence;
    
    // 10 - Contains the permitted settings of the DeliveryAggregation parameter of request primitives. '0' means 'False' '1' means 'True' '0 1' means 'False' or 'True'
    Resource(10, &instance::LimitsDelAggregation, O_RES_RW) LimitsDelAggregation;
    
};

} // end of id namespace
inline bool operator== (id2053::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id2053::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	