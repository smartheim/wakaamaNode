#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id8 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Locktarget8
    class LocktargetType : public PreallocString<30> {};
    #endif
    
    #ifndef Wipeitem8
    class WipeitemType : public PreallocString<30> {};
    #endif
    
    #ifndef Wipetarget8
    class WipetargetType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 8 - Lock and Wipe
 *  This LWM2M objects provides the resources needed to perform the lock and wipe operations.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - State of the device:0: unlocked state Normal operation.1: partially locked stateTo render the device inoperable the device has been partially locked. The “lock target” resource allows specifying the target(s) for this operation.2: fully locked stateTo render the device fully inoperable the device has been fully locked.
    int State;
    
    // 1 - To specify one or several targets for the lock operation. This allows partially locking the device by selecting specific components or interfaces to be locked.
    LocktargetType Locktarget;
    
    // Optional resource
    // 2 - Indicates which data can be wiped from the device. This resource could be e.g. representing a directory.
    WipeitemType Wipeitem;
    
    // 3 - To permanently erase data from the device.
    Executable Wipe;

    // 4 - To specify one or several targets for the wipe operation. This allows selecting specific data, or, memory areas for the wipe operation.
    WipetargetType Wipetarget;
    
    // 5 - Contains the result of a lock and wipe operation0: Default1: Partially Lock operation successful2: Fully Lock operation successful3: Unlock operation successful4: Wipe operation successful5: Partially Lock operation failed6: Fully Lock operation failed7: Unlock operation failed 8: Wipe operation failedThis Resource MAY be reported by sending Observe operation.
    int LockorWipeOperationResult;
    
};

enum class RESID {
    State = 0,
    Locktarget = 1,
    Wipeitem = 2,
    Wipe = 3,
    Wipetarget = 4,
    LockorWipeOperationResult = 5,
    
};

/* \brief Class for object 8 - Lock and Wipe
 *  This LWM2M objects provides the resources needed to perform the lock and wipe operations.
 */
class object : public Lwm2mObject<8, object, instance> {
public:

    // 0 - State of the device:0: unlocked state Normal operation.1: partially locked stateTo render the device inoperable the device has been partially locked. The “lock target” resource allows specifying the target(s) for this operation.2: fully locked stateTo render the device fully inoperable the device has been fully locked.
    Resource(0, &instance::State, O_RES_RW) State;
    
    // 1 - To specify one or several targets for the lock operation. This allows partially locking the device by selecting specific components or interfaces to be locked.
    Resource(1, &instance::Locktarget, O_RES_W) Locktarget;
    
    // Optional resource
    // 2 - Indicates which data can be wiped from the device. This resource could be e.g. representing a directory.
    Resource(2, &instance::Wipeitem, O_RES_R) Wipeitem;
    
    // 3 - To permanently erase data from the device.
    Resource(3, &instance::Wipe) Wipe;
    
    // 4 - To specify one or several targets for the wipe operation. This allows selecting specific data, or, memory areas for the wipe operation.
    Resource(4, &instance::Wipetarget, O_RES_W) Wipetarget;
    
    // 5 - Contains the result of a lock and wipe operation0: Default1: Partially Lock operation successful2: Fully Lock operation successful3: Unlock operation successful4: Wipe operation successful5: Partially Lock operation failed6: Fully Lock operation failed7: Unlock operation failed 8: Wipe operation failedThis Resource MAY be reported by sending Observe operation.
    Resource(5, &instance::LockorWipeOperationResult, O_RES_R) LockorWipeOperationResult;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id8::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id8::RESID c1) { return (uint16_t) c1 == c2; }
	