#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id1 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Binding1
    class BindingType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 1 - LwM2M Server
 *  This LwM2M Objects provides the data related to a LwM2M Server. A Bootstrap-Server
 *  has no such an Object Instance associated to it.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Used as link to associate server Object Instance.
    int ShortServerID;
    
    // 1 - Specify the lifetime of the registration in seconds (see Section 5.3 Registration).
    int Lifetime;
    
    // Optional resource
    // 2 - The default value the LwM2M Client should use for the Minimum Period of an Observation in the absence of this parameter being included in an Observation.If this Resource doesn’t exist, the default value is 0.
    int DefaultMinimumPeriod;
    
    // Optional resource
    // 3 - The default value the LwM2M Client should use for the Maximum Period of an Observation in the absence of this parameter being included in an Observation.
    int DefaultMaximumPeriod;
    
    // Optional resource
    // 4 - If this Resource is executed, this LwM2M Server Object is disabled for a certain period defined in the Disabled Timeout Resource. After receiving “Execute” operation, LwM2M Client MUST send response of the operation and perform de-registration process, and underlying network connection between the Client and Server MUST be disconnected to disable the LwM2M Server account.After the above process, the LwM2M Client MUST NOT send any message to the Server and ignore all the messages from the LwM2M Server for the period.
    Executable Disable;

    // Optional resource
    // 5 - A period to disable the Server. After this period, the LwM2M Client MUST perform registration process to the Server. If this Resource is not set, a default timeout value is 86400 (1 day).
    int DisableTimeout;
    
    // 6 - If true, the LwM2M Client stores “Notify” operations to the LwM2M Server while the LwM2M Server account is disabled or the LwM2M Client is offline. After the LwM2M Server account is enabled or the LwM2M Client is online, the LwM2M Client reports the stored “Notify” operations to the Server.If false, the LwM2M Client discards all the “Notify” operations or temporarily disables the Observe function while the LwM2M Server is disabled or the LwM2M Client is offline.The default value is true.The maximum number of storing Notifications per Server is up to the implementation.
    bool NotificationStoringWhenDisabledorOffline;
    
    // 7 - This Resource defines the transport binding configured for the LwM2M Client.If the LwM2M Client supports the binding specified in this Resource, the LwM2M Client MUST use that transport for the Current Binding Mode.
    BindingType Binding;
    
    // 8 - If this Resource is executed the LwM2M Client MUST perform an “Update” operation with this LwM2M Server using that transport for the Current Binding Mode.
    Executable RegistrationUpdateTrigger;

};

enum class RESID {
    ShortServerID = 0,
    Lifetime = 1,
    DefaultMinimumPeriod = 2,
    DefaultMaximumPeriod = 3,
    Disable = 4,
    DisableTimeout = 5,
    NotificationStoringWhenDisabledorOffline = 6,
    Binding = 7,
    RegistrationUpdateTrigger = 8,
    
};

/* \brief Class for object 1 - LwM2M Server
 *  This LwM2M Objects provides the data related to a LwM2M Server. A Bootstrap-Server
 *  has no such an Object Instance associated to it.
 */
class object : public Lwm2mObject<1, object, instance> {
public:

    // 0 - Used as link to associate server Object Instance.
    Resource(0, &instance::ShortServerID, O_RES_R) ShortServerID;
    
    // 1 - Specify the lifetime of the registration in seconds (see Section 5.3 Registration).
    Resource(1, &instance::Lifetime, O_RES_RW) Lifetime;
    
    // Optional resource
    // 2 - The default value the LwM2M Client should use for the Minimum Period of an Observation in the absence of this parameter being included in an Observation.If this Resource doesn’t exist, the default value is 0.
    Resource(2, &instance::DefaultMinimumPeriod, O_RES_RW) DefaultMinimumPeriod;
    
    // Optional resource
    // 3 - The default value the LwM2M Client should use for the Maximum Period of an Observation in the absence of this parameter being included in an Observation.
    Resource(3, &instance::DefaultMaximumPeriod, O_RES_RW) DefaultMaximumPeriod;
    
    // Optional resource
    // 4 - If this Resource is executed, this LwM2M Server Object is disabled for a certain period defined in the Disabled Timeout Resource. After receiving “Execute” operation, LwM2M Client MUST send response of the operation and perform de-registration process, and underlying network connection between the Client and Server MUST be disconnected to disable the LwM2M Server account.After the above process, the LwM2M Client MUST NOT send any message to the Server and ignore all the messages from the LwM2M Server for the period.
    Resource(4, &instance::Disable) Disable;
    
    // Optional resource
    // 5 - A period to disable the Server. After this period, the LwM2M Client MUST perform registration process to the Server. If this Resource is not set, a default timeout value is 86400 (1 day).
    Resource(5, &instance::DisableTimeout, O_RES_RW) DisableTimeout;
    
    // 6 - If true, the LwM2M Client stores “Notify” operations to the LwM2M Server while the LwM2M Server account is disabled or the LwM2M Client is offline. After the LwM2M Server account is enabled or the LwM2M Client is online, the LwM2M Client reports the stored “Notify” operations to the Server.If false, the LwM2M Client discards all the “Notify” operations or temporarily disables the Observe function while the LwM2M Server is disabled or the LwM2M Client is offline.The default value is true.The maximum number of storing Notifications per Server is up to the implementation.
    Resource(6, &instance::NotificationStoringWhenDisabledorOffline, O_RES_RW) NotificationStoringWhenDisabledorOffline;
    
    // 7 - This Resource defines the transport binding configured for the LwM2M Client.If the LwM2M Client supports the binding specified in this Resource, the LwM2M Client MUST use that transport for the Current Binding Mode.
    Resource(7, &instance::Binding, O_RES_RW) Binding;
    
    // 8 - If this Resource is executed the LwM2M Client MUST perform an “Update” operation with this LwM2M Server using that transport for the Current Binding Mode.
    Resource(8, &instance::RegistrationUpdateTrigger) RegistrationUpdateTrigger;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id1::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id1::RESID c1) { return (uint16_t) c1 == c2; }
	
