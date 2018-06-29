#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3343 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3343
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3343 - Dimmer
 *  This IPSO object should be used with a dimmer or level control to report the state of the
 *  control.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    float Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the dimmer has been on (Dimmer value has to be > 0). Writing a value of 0 resets the counter.
    int OnTime;
    
    // Optional resource
    // 5854 - The time in seconds that the dimmer has been off  (dimmer value less or equal to 0) Writing a value of 0 resets the counter. 
    int OffTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Dimmer = 5851,
    OnTime = 5852,
    OffTime = 5854,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3343 - Dimmer
 *  This IPSO object should be used with a dimmer or level control to report the state of the
 *  control.
 */
class object : public Lwm2mObject<3343, object, instance> {
public:

    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the dimmer has been on (Dimmer value has to be > 0). Writing a value of 0 resets the counter.
    Resource(5852, &instance::OnTime, O_RES_RW) OnTime;
    
    // Optional resource
    // 5854 - The time in seconds that the dimmer has been off  (dimmer value less or equal to 0) Writing a value of 0 resets the counter. 
    Resource(5854, &instance::OffTime, O_RES_RW) OffTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3343::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3343::RESID c1) { return (uint16_t) c1 == c2; }
	