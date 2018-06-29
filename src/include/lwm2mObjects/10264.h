#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10264 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ScheduleUTCOffset10264
    class ScheduleUTCOffsetType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10264 - Delivery Schedule
 *  The Delivery Schedule object provides a means for controlling the periodic delivery
 *  of interval and event data to the LwM2M server.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Schedule Start Time is a readable and writable resource representing the number of seconds past midnight for which this schedule commences
    int ScheduleStartTime;
    
    // 1 - The Schedule UTC Offset resource is a readable and writable resource representing the time zone offset for the Schedule Start Time Resource for this Delivery Schedule instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided.  UTC+X [ISO 8601].
    ScheduleUTCOffsetType ScheduleUTCOffset;
    
    // 2 - The Delivery Frequency resource is a readable and writable resource representing the number of seconds between deliveries. It is recommended that the Delivery Frequency be set to a devisor of 24 hours (86400 seconds) to provide a consistent interval period. Examples of Delivery Frequency include:-30 = Every 30 seconds600 = Every 10 minutes1800 = Every 30 minutes3600 = Hourly7200 = Every 2 hours14400 = Every 4 hours43200 = Every 12 hours86400 = Every Day172600 = Every Second Day
    int DeliveryFrequency;
    
    // Optional resource
    // 3 - The Randomised Delivery Window resource is a readable and writable resource representing a randomisation widow in seconds for the triggering of the notification delivery to the LwM2M server. If not provided, the randomised delivery window should default to 0 and the Notification should be sent immediately. The Randomised Delivery Window resource should be set to a value smaller than the delivery frequency.
    int RandomisedDeliveryWindow;
    
    // Optional resource
    // 4 - The Number of Retries resource is a readable and writable resource representing the number of retry attempts that should be attempted when the delivery notification is not successful. If not provided, this value defaults to 0 and no retries are attempted. This retry behaviour is at an application level and should be set with consideration of standard CoAP retry behaviour.
    int NumberofRetries;
    
    // Optional resource
    // 5 - The Retry Period resource is a readable and writable resource representing the number of seconds between each application level retry. 
    int RetryPeriod;
    
};

enum class RESID {
    ScheduleStartTime = 0,
    ScheduleUTCOffset = 1,
    DeliveryFrequency = 2,
    RandomisedDeliveryWindow = 3,
    NumberofRetries = 4,
    RetryPeriod = 5,
    
};

/* \brief Class for object 10264 - Delivery Schedule
 *  The Delivery Schedule object provides a means for controlling the periodic delivery
 *  of interval and event data to the LwM2M server.
 */
class object : public Lwm2mObject<10264, object, instance> {
public:

    // 0 - Schedule Start Time is a readable and writable resource representing the number of seconds past midnight for which this schedule commences
    Resource(0, &instance::ScheduleStartTime, O_RES_RW) ScheduleStartTime;
    
    // 1 - The Schedule UTC Offset resource is a readable and writable resource representing the time zone offset for the Schedule Start Time Resource for this Delivery Schedule instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided.  UTC+X [ISO 8601].
    Resource(1, &instance::ScheduleUTCOffset, O_RES_RW) ScheduleUTCOffset;
    
    // 2 - The Delivery Frequency resource is a readable and writable resource representing the number of seconds between deliveries. It is recommended that the Delivery Frequency be set to a devisor of 24 hours (86400 seconds) to provide a consistent interval period. Examples of Delivery Frequency include:-30 = Every 30 seconds600 = Every 10 minutes1800 = Every 30 minutes3600 = Hourly7200 = Every 2 hours14400 = Every 4 hours43200 = Every 12 hours86400 = Every Day172600 = Every Second Day
    Resource(2, &instance::DeliveryFrequency, O_RES_RW) DeliveryFrequency;
    
    // Optional resource
    // 3 - The Randomised Delivery Window resource is a readable and writable resource representing a randomisation widow in seconds for the triggering of the notification delivery to the LwM2M server. If not provided, the randomised delivery window should default to 0 and the Notification should be sent immediately. The Randomised Delivery Window resource should be set to a value smaller than the delivery frequency.
    Resource(3, &instance::RandomisedDeliveryWindow, O_RES_RW) RandomisedDeliveryWindow;
    
    // Optional resource
    // 4 - The Number of Retries resource is a readable and writable resource representing the number of retry attempts that should be attempted when the delivery notification is not successful. If not provided, this value defaults to 0 and no retries are attempted. This retry behaviour is at an application level and should be set with consideration of standard CoAP retry behaviour.
    Resource(4, &instance::NumberofRetries, O_RES_RW) NumberofRetries;
    
    // Optional resource
    // 5 - The Retry Period resource is a readable and writable resource representing the number of seconds between each application level retry. 
    Resource(5, &instance::RetryPeriod, O_RES_RW) RetryPeriod;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10264::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10264::RESID c1) { return (uint16_t) c1 == c2; }
	