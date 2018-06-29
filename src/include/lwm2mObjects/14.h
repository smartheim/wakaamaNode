#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id14 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ComponentIdentity14
    class ComponentIdentityType : public PreallocString<30> {};
    #endif
    
    #ifndef ComponentPack14
    class ComponentPackType : public Opaque<30> {};
    #endif
    
    #ifndef ComponentVersion14
    class ComponentVersionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 14 - LWM2M Software Component
 *  If some Objects are not supported after software update, the LwM2M Client MUST delete
 *  all the Object Instances of the Objects that are not supported.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Name or identifier of the software component
    ComponentIdentityType ComponentIdentity;
    
    // Optional resource
    // 1 - Software components is stored in this resource
    ComponentPackType ComponentPack;
    
    // Optional resource
    // 2 - Version of the software component.
    ComponentVersionType ComponentVersion;
    
    // Optional resource
    // 3 - This action activates the software previously successfully installed (the SW Update Package Installation State Machine is currently in the INSTALLED state).
    Executable Activate;

    // Optional resource
    // 4 - This action deactivates software if the SW Update Package Installation State Machine is currently in the INSTALLED state.
    Executable Deactivate;

    // Optional resource
    // 5 - Indicates the current activation state of this software component:0: DISABLEDActivation State is DISABLED if the Software Component Activation State Machine is in the INACTIVE state or not alive.1: ENABLEDActivation State is ENABLED only if the Software Component Activation State Machine is in the ACTIVE state.
    bool ActivationState;
    
};

enum class RESID {
    ComponentIdentity = 0,
    ComponentPack = 1,
    ComponentVersion = 2,
    Activate = 3,
    Deactivate = 4,
    ActivationState = 5,
    
};

/* \brief Class for object 14 - LWM2M Software Component
 *  If some Objects are not supported after software update, the LwM2M Client MUST delete
 *  all the Object Instances of the Objects that are not supported.
 */
class object : public Lwm2mObject<14, object, instance> {
public:

    // Optional resource
    // 0 - Name or identifier of the software component
    Resource(0, &instance::ComponentIdentity, O_RES_R) ComponentIdentity;
    
    // Optional resource
    // 1 - Software components is stored in this resource
    Resource(1, &instance::ComponentPack, O_RES_R) ComponentPack;
    
    // Optional resource
    // 2 - Version of the software component.
    Resource(2, &instance::ComponentVersion, O_RES_R) ComponentVersion;
    
    // Optional resource
    // 3 - This action activates the software previously successfully installed (the SW Update Package Installation State Machine is currently in the INSTALLED state).
    Resource(3, &instance::Activate) Activate;
    
    // Optional resource
    // 4 - This action deactivates software if the SW Update Package Installation State Machine is currently in the INSTALLED state.
    Resource(4, &instance::Deactivate) Deactivate;
    
    // Optional resource
    // 5 - Indicates the current activation state of this software component:0: DISABLEDActivation State is DISABLED if the Software Component Activation State Machine is in the INACTIVE state or not alive.1: ENABLEDActivation State is ENABLED only if the Software Component Activation State Machine is in the ACTIVE state.
    Resource(5, &instance::ActivationState, O_RES_R) ActivationState;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id14::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id14::RESID c1) { return (uint16_t) c1 == c2; }
	