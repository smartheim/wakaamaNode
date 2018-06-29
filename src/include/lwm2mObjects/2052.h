#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2052 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2052 - CmdhEcDefParamValues
 *  This Object represents a specific set of default values for the CMDH related parameters
 *  Request Expiration Timestamp, Result Expiration Timestamp, Operational Execution
 *  Time, Result Persistence and Delivery Aggregation that are applicable for a given
 *  Event Category if these parameters are not specified in the message.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains  list of Event Category values
    int ApplicableEventCategory;
    
    // 1 - Contains the default value for the Request Expiration Timestamp parameter when such a parameter is not set in the request
    int DefaultRequestExpTime;
    
    // 2 - Contains the default value of the Result  Expiration Timestamp parameter when such a parameter is not set in the request  
    int DefaultResultExpTime;
    
    // 3 - Contains the default value of the Operation Execution Time parameter when such a parameter is not set in the request
    int DefaultOpExecTime;
    
    // 4 - Contains the default value of the Result  Persistence parameter when such a parameter is not set in the request  
    int DefaultRespPersistence;
    
    // 5 - Contains the default value of the Delivery Aggregation  parameter when such a parameter is not set in the request  
    int DefaultDelAggregation;
    
};

enum class RESID {
    ApplicableEventCategory = 0,
    DefaultRequestExpTime = 1,
    DefaultResultExpTime = 2,
    DefaultOpExecTime = 3,
    DefaultRespPersistence = 4,
    DefaultDelAggregation = 5,
    
};

/* \brief Class for object 2052 - CmdhEcDefParamValues
 *  This Object represents a specific set of default values for the CMDH related parameters
 *  Request Expiration Timestamp, Result Expiration Timestamp, Operational Execution
 *  Time, Result Persistence and Delivery Aggregation that are applicable for a given
 *  Event Category if these parameters are not specified in the message.
 */
class object : public Lwm2mObject<2052, object, instance> {
public:

    // 0 - Contains  list of Event Category values
    Resource(0, &instance::ApplicableEventCategory, O_RES_RW) ApplicableEventCategory;
    
    // 1 - Contains the default value for the Request Expiration Timestamp parameter when such a parameter is not set in the request
    Resource(1, &instance::DefaultRequestExpTime, O_RES_RW) DefaultRequestExpTime;
    
    // 2 - Contains the default value of the Result  Expiration Timestamp parameter when such a parameter is not set in the request  
    Resource(2, &instance::DefaultResultExpTime, O_RES_RW) DefaultResultExpTime;
    
    // 3 - Contains the default value of the Operation Execution Time parameter when such a parameter is not set in the request
    Resource(3, &instance::DefaultOpExecTime, O_RES_RW) DefaultOpExecTime;
    
    // 4 - Contains the default value of the Result  Persistence parameter when such a parameter is not set in the request  
    Resource(4, &instance::DefaultRespPersistence, O_RES_RW) DefaultRespPersistence;
    
    // 5 - Contains the default value of the Delivery Aggregation  parameter when such a parameter is not set in the request  
    Resource(5, &instance::DefaultDelAggregation, O_RES_RW) DefaultDelAggregation;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2052::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2052::RESID c1) { return (uint16_t) c1 == c2; }
	