#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id7 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 7 - Connectivity Statistics
 *  This LwM2M Objects enables client to collect statistical information and enables
 *  the LwM2M Server to retrieve these information, set the collection duration and reset
 *  the statistical parameters.Note: When reporting the Tx Data or Rx Data, the LwM2M Client
 *  reports the total KB transmitted/received over IP bearer(s), including all protocol
 *  header bytes up to and including the IP header. This does not include lower level retransmissions/optimizations
 *  (e.g. RAN, header compression) or SMS messages.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Indicate the total number of SMS successfully transmitted during the collection period.
    int SMSTxCounter;
    
    // Optional resource
    // 1 - Indicate the total number of SMS successfully received during the collection period.
    int SMSRxCounter;
    
    // Optional resource
    // 2 - Indicate the total amount of IP data transmitted during the collection period.
    int TxData;
    
    // Optional resource
    // 3 - Indicate the total amount of IP data received during the collection period.
    int RxData;
    
    // Optional resource
    // 4 - The maximum IP message size that is used during the collection period.
    int MaxMessageSize;
    
    // Optional resource
    // 5 - The average IP message size that is used during the collection period.
    int AverageMessageSize;
    
    // 6 - Reset resources 0-5 to 0 and start to collect information, If resource 8 (Collection Period) value is 0, the client will keep collecting information until resource 7 (Stop) is executed, otherwise the client will stop collecting information after specified period ended.        Note:When reporting the Tx Data or Rx Data, the LwM2M Client reports the total KB transmitted/received over IP bearer(s), including all protocol header bytes up to and including the IP header. This does not include lower level retransmissions/optimizations (e.g. RAN, header compression) or SMS messages.
    Executable Start;

    // 7 - Stop collecting information, but do not reset resources 0-5.
    Executable Stop;

    // Optional resource
    // 8 - The default collection period in seconds. The value 0 indicates that the collection period is not set.
    int CollectionPeriod;
    
};

enum class RESID {
    SMSTxCounter = 0,
    SMSRxCounter = 1,
    TxData = 2,
    RxData = 3,
    MaxMessageSize = 4,
    AverageMessageSize = 5,
    Start = 6,
    Stop = 7,
    CollectionPeriod = 8,
    
};

/* \brief Class for object 7 - Connectivity Statistics
 *  This LwM2M Objects enables client to collect statistical information and enables
 *  the LwM2M Server to retrieve these information, set the collection duration and reset
 *  the statistical parameters.Note: When reporting the Tx Data or Rx Data, the LwM2M Client
 *  reports the total KB transmitted/received over IP bearer(s), including all protocol
 *  header bytes up to and including the IP header. This does not include lower level retransmissions/optimizations
 *  (e.g. RAN, header compression) or SMS messages.
 */
class object : public Lwm2mObject<7, object, instance> {
public:

    // Optional resource
    // 0 - Indicate the total number of SMS successfully transmitted during the collection period.
    Resource(0, &instance::SMSTxCounter, O_RES_R) SMSTxCounter;
    
    // Optional resource
    // 1 - Indicate the total number of SMS successfully received during the collection period.
    Resource(1, &instance::SMSRxCounter, O_RES_R) SMSRxCounter;
    
    // Optional resource
    // 2 - Indicate the total amount of IP data transmitted during the collection period.
    Resource(2, &instance::TxData, O_RES_R) TxData;
    
    // Optional resource
    // 3 - Indicate the total amount of IP data received during the collection period.
    Resource(3, &instance::RxData, O_RES_R) RxData;
    
    // Optional resource
    // 4 - The maximum IP message size that is used during the collection period.
    Resource(4, &instance::MaxMessageSize, O_RES_R) MaxMessageSize;
    
    // Optional resource
    // 5 - The average IP message size that is used during the collection period.
    Resource(5, &instance::AverageMessageSize, O_RES_R) AverageMessageSize;
    
    // 6 - Reset resources 0-5 to 0 and start to collect information, If resource 8 (Collection Period) value is 0, the client will keep collecting information until resource 7 (Stop) is executed, otherwise the client will stop collecting information after specified period ended.        Note:When reporting the Tx Data or Rx Data, the LwM2M Client reports the total KB transmitted/received over IP bearer(s), including all protocol header bytes up to and including the IP header. This does not include lower level retransmissions/optimizations (e.g. RAN, header compression) or SMS messages.
    Resource(6, &instance::Start) Start;
    
    // 7 - Stop collecting information, but do not reset resources 0-5.
    Resource(7, &instance::Stop) Stop;
    
    // Optional resource
    // 8 - The default collection period in seconds. The value 0 indicates that the collection period is not set.
    Resource(8, &instance::CollectionPeriod, O_RES_RW) CollectionPeriod;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id7::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id7::RESID c1) { return (uint16_t) c1 == c2; }
	