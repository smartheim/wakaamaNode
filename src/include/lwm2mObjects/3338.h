#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3338 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3338
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3338 - Buzzer
 *  This IPSO object should be used to actuate an audible alarm such as a buzzer, beeper,
 *  or vibration alarm. There is a dimmer control for setting the relative loudness of the
 *  alarm, and an optional duration control to limit the length of time the alarm sounds
 *  when turned on. Each time a “1” is written to the On/Off resource, the alarm will sound
 *  again for the configured duration. If no duration is programmed or the setting is zero,
 *  writing a “1” to the On/Off resource will result in the alarm sounding continuously
 *  until a “0” is written to the On/Off resource.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5850 - On/Off control, 0=OFF, 1=ON.
    bool OnOff;
    
    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    int Dimmer;
    
    // Optional resource
    // 5521 - The duration of the time delay.
    float DelayDuration;
    
    // 5525 - The off time when On/Off control remains on.
    float MinimumOfftime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    OnOff = 5850,
    Dimmer = 5851,
    DelayDuration = 5521,
    MinimumOfftime = 5525,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3338 - Buzzer
 *  This IPSO object should be used to actuate an audible alarm such as a buzzer, beeper,
 *  or vibration alarm. There is a dimmer control for setting the relative loudness of the
 *  alarm, and an optional duration control to limit the length of time the alarm sounds
 *  when turned on. Each time a “1” is written to the On/Off resource, the alarm will sound
 *  again for the configured duration. If no duration is programmed or the setting is zero,
 *  writing a “1” to the On/Off resource will result in the alarm sounding continuously
 *  until a “0” is written to the On/Off resource.
 */
class object : public Lwm2mObject<3338, object, instance> {
public:

    // 5850 - On/Off control, 0=OFF, 1=ON.
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5521 - The duration of the time delay.
    Resource(5521, &instance::DelayDuration, O_RES_RW) DelayDuration;
    
    // 5525 - The off time when On/Off control remains on.
    Resource(5525, &instance::MinimumOfftime, O_RES_RW) MinimumOfftime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3338::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3338::RESID c1) { return (uint16_t) c1 == c2; }
	