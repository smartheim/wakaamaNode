#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3312 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3312 - Power Control
 *  Description: This Object is used to control a power source, such as a Smart Plug. It allows
 *  a power relay to be turned on or off and its dimmer setting to be control as a % between 0
 *  and 100.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5850 - This resource represents a power relay, which can be controlled, the setting of which is a Boolean value (1,0) where 1 is on and 0 is off.
    bool OnOff;
    
    // Optional resource
    // 5851 - This resource represents a power dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    int Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the power relay has been on. Writing a value of 0 resets the counter.
    int OnTime;
    
    // Optional resource
    // 5805 - The total power in Wh that has been used by the load.
    float Cumulativeactivepower;
    
    // Optional resource
    // 5820 - The power factor of the load.
    float PowerFactor;
    
};

enum class RESID {
    OnOff = 5850,
    Dimmer = 5851,
    OnTime = 5852,
    Cumulativeactivepower = 5805,
    PowerFactor = 5820,
    
};

/* \brief Class for object 3312 - Power Control
 *  Description: This Object is used to control a power source, such as a Smart Plug. It allows
 *  a power relay to be turned on or off and its dimmer setting to be control as a % between 0
 *  and 100.
 */
class object : public Lwm2mObject<3312, object, instance> {
public:

    // 5850 - This resource represents a power relay, which can be controlled, the setting of which is a Boolean value (1,0) where 1 is on and 0 is off.
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5851 - This resource represents a power dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_W) Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the power relay has been on. Writing a value of 0 resets the counter.
    Resource(5852, &instance::OnTime, O_RES_RW) OnTime;
    
    // Optional resource
    // 5805 - The total power in Wh that has been used by the load.
    Resource(5805, &instance::Cumulativeactivepower, O_RES_R) Cumulativeactivepower;
    
    // Optional resource
    // 5820 - The power factor of the load.
    Resource(5820, &instance::PowerFactor, O_RES_R) PowerFactor;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3312::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3312::RESID c1) { return (uint16_t) c1 == c2; }
	