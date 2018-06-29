#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3306 {
// Custom, overrideable types for Opaque and String resources

    #ifndef MutistateOutput3306
    class MutistateOutputType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3306
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3306 - Actuation
 *  This IPSO object is dedicated to remote actuation such as ON/OFF action or dimming.
 *  A multi-state output can also be described as a string. This is useful to send pilot wire
 *  orders for instance. It also provides a resource to reflect the time that the device
 *  has been switched on.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5850 - On/Off
    bool OnOff;
    
    // Optional resource
    // 5851 - This resource represents a light dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    int Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the device has been on. Writing a value of 0 resets the counter.
    int OnTime;
    
    // Optional resource
    // 5853 - A string describing a state for multiple level output such as Pilot Wire
    MutistateOutputType MutistateOutput;
    
    // Optional resource
    // 5750 - The Application type of the device, for example “Motion Closure”.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    OnOff = 5850,
    Dimmer = 5851,
    OnTime = 5852,
    MutistateOutput = 5853,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3306 - Actuation
 *  This IPSO object is dedicated to remote actuation such as ON/OFF action or dimming.
 *  A multi-state output can also be described as a string. This is useful to send pilot wire
 *  orders for instance. It also provides a resource to reflect the time that the device
 *  has been switched on.
 */
class object : public Lwm2mObject<3306, object, instance> {
public:

    // 5850 - On/Off
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5851 - This resource represents a light dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the device has been on. Writing a value of 0 resets the counter.
    Resource(5852, &instance::OnTime, O_RES_RW) OnTime;
    
    // Optional resource
    // 5853 - A string describing a state for multiple level output such as Pilot Wire
    Resource(5853, &instance::MutistateOutput, O_RES_RW) MutistateOutput;
    
    // Optional resource
    // 5750 - The Application type of the device, for example “Motion Closure”.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3306::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3306::RESID c1) { return (uint16_t) c1 == c2; }
	