#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2 - LwM2M Access Control
 *  Access Control Object is used to check whether the LwM2M Server has access right for
 *  performing an operation.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The Object ID and The Object Instance ID are applied for.
    int ObjectID;
    
    // 1 - See Table 20: LwM2M Identifiers.
    int ObjectInstanceID;
    
    // Optional resource
    // 2 - The Resource Instance ID MUST be the Short Server ID of a certain LwM2M Server for which associated access rights are contained in the Resource Instance value.The Resource Instance ID 0 is a specific ID, determining the ACL Instance which contains the default access rights.Each bit set in the Resource Instance value, grants an access right to the LwM2M Server to the corresponding operation.The bit order is specified as below.1st LSB: R(Read, Observe, Discover, Write-Attributes)2nd LSB: W(Write)3rd LSB: E(Execute)4th LSB: D(Delete)5th LSB: C(Create)Other bits are reserved for future use.
    int ACL;
    
    // 3 - Short Server ID of a certain LwM2M Server; only such an LwM2M Server can manage the Resources of this Object Instance. The specific value MAX_ID=65535 means this Access Control Object Instance is created and modified during a Bootstrap phase only.
    int AccessControlOwner;
    
};

enum class RESID {
    ObjectID = 0,
    ObjectInstanceID = 1,
    ACL = 2,
    AccessControlOwner = 3,
    
};

/* \brief Class for object 2 - LwM2M Access Control
 *  Access Control Object is used to check whether the LwM2M Server has access right for
 *  performing an operation.
 */
class object : public Lwm2mObject<2, object, instance> {
public:

    // 0 - The Object ID and The Object Instance ID are applied for.
    Resource(0, &instance::ObjectID, O_RES_R) ObjectID;
    
    // 1 - See Table 20: LwM2M Identifiers.
    Resource(1, &instance::ObjectInstanceID, O_RES_R) ObjectInstanceID;
    
    // Optional resource
    // 2 - The Resource Instance ID MUST be the Short Server ID of a certain LwM2M Server for which associated access rights are contained in the Resource Instance value.The Resource Instance ID 0 is a specific ID, determining the ACL Instance which contains the default access rights.Each bit set in the Resource Instance value, grants an access right to the LwM2M Server to the corresponding operation.The bit order is specified as below.1st LSB: R(Read, Observe, Discover, Write-Attributes)2nd LSB: W(Write)3rd LSB: E(Execute)4th LSB: D(Delete)5th LSB: C(Create)Other bits are reserved for future use.
    Resource(2, &instance::ACL, O_RES_RW) ACL;
    
    // 3 - Short Server ID of a certain LwM2M Server; only such an LwM2M Server can manage the Resources of this Object Instance. The specific value MAX_ID=65535 means this Access Control Object Instance is created and modified during a Bootstrap phase only.
    Resource(3, &instance::AccessControlOwner, O_RES_RW) AccessControlOwner;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2::RESID c1) { return (uint16_t) c1 == c2; }
	