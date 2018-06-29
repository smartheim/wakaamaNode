#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10262 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Name10262
    class NameType : public PreallocString<30> {};
    #endif
    
    #ifndef LatestPayload10262
    class LatestPayloadType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10262 - Interval Data Delivery
 *  The Interval Data Delivery object provides an optimised means for managing the delivery
 *  of interval data from multiple Interval Data Object instances.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The Name resource provides a way to identify different Interval Data Delivery instances. Name is a readable and writable attribute. Name is defined as an arbitrary length text string
    NameType Name;
    
    // 1 - The Interval Data Links resource is a set of object links that point to each of the Interval Data Object Instances that are managed by this Interval Data Delivery Object Instance. An Object Link is two 16-bit integer values representing the Object ID and the Object Instance ID. This resource can have multiple instances allowing this Interval Data Delivery object to manage many Interval Data instances.
    // Objlnk resources are not supported yet - IntervalDataLinks;
    
    // 2 - The Latest Payload resource is a multiple instance resource representing the Latest Payload resource from each of the Interval Data objects defined in the Interval Data Links Resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should for each of the Interval Data objects defined in the Interval Data Links Resource must be updated. When no new data exists for a specific Interval Data instance and empty Opaque value should be provided. When a specific Interval Data Instance is disabled (Recording Enabled Resource = 0), no payload data should be provided at all.
    LatestPayloadType LatestPayload;
    
    // Optional resource
    // 3 - The Schedule resource provides link to a schedule object. This Schedule object is used to provide fine grain control the Notification schedule delivery when the default LwM2M NOTIFICATION attributes do not provide sufficient control. If no schedule is required, an Object Link referencing no Object Instance will contain the concatenation of 2 MAX-ID values (null link).
    // Objlnk resources are not supported yet - Schedule;
    
};

enum class RESID {
    Name = 0,
    IntervalDataLinks = 1,
    LatestPayload = 2,
    Schedule = 3,
    
};

/* \brief Class for object 10262 - Interval Data Delivery
 *  The Interval Data Delivery object provides an optimised means for managing the delivery
 *  of interval data from multiple Interval Data Object instances.
 */
class object : public Lwm2mObject<10262, object, instance> {
public:

    // 0 - The Name resource provides a way to identify different Interval Data Delivery instances. Name is a readable and writable attribute. Name is defined as an arbitrary length text string
    Resource(0, &instance::Name, O_RES_RW) Name;
    
    // 1 - The Interval Data Links resource is a set of object links that point to each of the Interval Data Object Instances that are managed by this Interval Data Delivery Object Instance. An Object Link is two 16-bit integer values representing the Object ID and the Object Instance ID. This resource can have multiple instances allowing this Interval Data Delivery object to manage many Interval Data instances.
    // Objlnk resources are not supported yet - IntervalDataLinks;
    
    // 2 - The Latest Payload resource is a multiple instance resource representing the Latest Payload resource from each of the Interval Data objects defined in the Interval Data Links Resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should for each of the Interval Data objects defined in the Interval Data Links Resource must be updated. When no new data exists for a specific Interval Data instance and empty Opaque value should be provided. When a specific Interval Data Instance is disabled (Recording Enabled Resource = 0), no payload data should be provided at all.
    Resource(2, &instance::LatestPayload, O_RES_R) LatestPayload;
    
    // Optional resource
    // 3 - The Schedule resource provides link to a schedule object. This Schedule object is used to provide fine grain control the Notification schedule delivery when the default LwM2M NOTIFICATION attributes do not provide sufficient control. If no schedule is required, an Object Link referencing no Object Instance will contain the concatenation of 2 MAX-ID values (null link).
    // Objlnk resources are not supported yet - Schedule;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10262::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10262::RESID c1) { return (uint16_t) c1 == c2; }
	