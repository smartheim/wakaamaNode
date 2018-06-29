#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3339 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Clip3339
    class ClipType : public Opaque<30> {};
    #endif
    
    #ifndef Trigger3339
    class TriggerType : public Opaque<30> {};
    #endif
    
    #ifndef ApplicationType3339
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3339 - Audio Clip
 *  This IPSO object should be used for a speaker that plays a pre-recorded audio clip or
 *  an audio output that is sent elsewhere. For example, an elevator which announces the
 *  floor of the building. A resource is provided to store the clip, a dimmer resource controls
 *  the relative sound level of the playback, and a duration resource limits the maximum
 *  playback time. After the duration time is reached, any remaining samples in the clip
 *  are ignored, and the clip player will be ready to play another clip.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5522 - Audio Clip that is playable (i.e. short audio recording indicating the floor in an elevator).
    ClipType Clip;
    
    // Optional resource
    // 5523 - Trigger initiating actuation.
    Executable Trigger;

    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    int Dimmer;
    
    // Optional resource
    // 5524 - The duration of the sound once trigger.
    float Duration;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Clip = 5522,
    Trigger = 5523,
    Dimmer = 5851,
    Duration = 5524,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3339 - Audio Clip
 *  This IPSO object should be used for a speaker that plays a pre-recorded audio clip or
 *  an audio output that is sent elsewhere. For example, an elevator which announces the
 *  floor of the building. A resource is provided to store the clip, a dimmer resource controls
 *  the relative sound level of the playback, and a duration resource limits the maximum
 *  playback time. After the duration time is reached, any remaining samples in the clip
 *  are ignored, and the clip player will be ready to play another clip.
 */
class object : public Lwm2mObject<3339, object, instance> {
public:

    // 5522 - Audio Clip that is playable (i.e. short audio recording indicating the floor in an elevator).
    Resource(5522, &instance::Clip, O_RES_RW) Clip;
    
    // Optional resource
    // 5523 - Trigger initiating actuation.
    Resource(5523, &instance::Trigger) Trigger;
    
    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5524 - The duration of the sound once trigger.
    Resource(5524, &instance::Duration, O_RES_RW) Duration;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3339::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3339::RESID c1) { return (uint16_t) c1 == c2; }
	