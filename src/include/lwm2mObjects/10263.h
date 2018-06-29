#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10263 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Name10263
    class NameType : public PreallocString<30> {};
    #endif
    
    #ifndef LatestEventlog10263
    class LatestEventlogType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10263 - Event Data Delivery
 *  The Event Data Delivery object provides a simple means for managing the delivery of
 *  event data from multiple Event Data Object instances.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The Name resource provides a way to identify different Event Data Delivery instances. Name is a readable and writable attribute. Name is defined as an arbitrary length text string
    NameType Name;
    
    // 1 - The Event Data Links resource is a set of object links that point to each of the Event Data Object Instances that are managed by this Event Data Delivery Object Instance. An Object Link is two 16-bit integer values representing the Object ID and the Object Instance ID. This resource can have multiple instances allowing this Event Data Delivery object to manage many Event Data instances.
    // Objlnk resources are not supported yet - EventDataLinks;
    
    // 2 - The Latest Eventlog resource is a multiple instance resource representing the Latest Eventlog resource from each of the Event Data objects defined in the Event Data Links Resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Event Time for each of the Event Data objects defined in the Event Data Links Resource must be updated. When no new event data exists for any of the linked Event Data instances an empty Opaque value should be provided.If this resource has an LwM2M server observation and one of the Event Data Instance is configured as Realtime and has been triggered, the Event Data Delivery object must send all undelivered events for all linked Event Data objects. 
    LatestEventlogType LatestEventlog;
    
    // 3 - The Schedule resource provides link to a schedule object. This Schedule object is used to provide fine grain control the Notification schedule delivery when the default LwM2M NOTIFICATION attributes do not provide sufficient control. If no schedule is required, an Object Link referencing no Object Instance will contain the concatenation of 2 MAX-ID values (null link).
    // Objlnk resources are not supported yet - Schedule;
    
};

enum class RESID {
    Name = 0,
    EventDataLinks = 1,
    LatestEventlog = 2,
    Schedule = 3,
    
};

/* \brief Class for object 10263 - Event Data Delivery
 *  The Event Data Delivery object provides a simple means for managing the delivery of
 *  event data from multiple Event Data Object instances.
 */
class object : public Lwm2mObject<10263, object, instance> {
public:

    // 0 - The Name resource provides a way to identify different Event Data Delivery instances. Name is a readable and writable attribute. Name is defined as an arbitrary length text string
    Resource(0, &instance::Name, O_RES_RW) Name;
    
    // 1 - The Event Data Links resource is a set of object links that point to each of the Event Data Object Instances that are managed by this Event Data Delivery Object Instance. An Object Link is two 16-bit integer values representing the Object ID and the Object Instance ID. This resource can have multiple instances allowing this Event Data Delivery object to manage many Event Data instances.
    // Objlnk resources are not supported yet - EventDataLinks;
    
    // 2 - The Latest Eventlog resource is a multiple instance resource representing the Latest Eventlog resource from each of the Event Data objects defined in the Event Data Links Resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Event Time for each of the Event Data objects defined in the Event Data Links Resource must be updated. When no new event data exists for any of the linked Event Data instances an empty Opaque value should be provided.If this resource has an LwM2M server observation and one of the Event Data Instance is configured as Realtime and has been triggered, the Event Data Delivery object must send all undelivered events for all linked Event Data objects. 
    Resource(2, &instance::LatestEventlog, O_RES_R) LatestEventlog;
    
    // 3 - The Schedule resource provides link to a schedule object. This Schedule object is used to provide fine grain control the Notification schedule delivery when the default LwM2M NOTIFICATION attributes do not provide sufficient control. If no schedule is required, an Object Link referencing no Object Instance will contain the concatenation of 2 MAX-ID values (null link).
    // Objlnk resources are not supported yet - Schedule;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10263::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10263::RESID c1) { return (uint16_t) c1 == c2; }
	