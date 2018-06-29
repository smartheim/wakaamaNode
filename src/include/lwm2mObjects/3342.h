#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3342 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3342
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3342 - On/Off switch
 *  This IPSO object should be used with an On/Off switch to report the state of the switch.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5500 - The current state of a digital input.
    bool DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    int DigitalInputCounter;
    
    // Optional resource
    // 5852 - The time in seconds since the On command was sent. Writing a value of 0 resets the counter.
    int OnTime;
    
    // Optional resource
    // 5854 - The time in seconds since the Off command was sent. Writing a value of 0 resets the counter.
    int OffTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    DigitalInputState = 5500,
    DigitalInputCounter = 5501,
    OnTime = 5852,
    OffTime = 5854,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3342 - On/Off switch
 *  This IPSO object should be used with an On/Off switch to report the state of the switch.
 */
class object : public Lwm2mObject<3342, object, instance> {
public:

    // 5500 - The current state of a digital input.
    Resource(5500, &instance::DigitalInputState, O_RES_R) DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5852 - The time in seconds since the On command was sent. Writing a value of 0 resets the counter.
    Resource(5852, &instance::OnTime, O_RES_RW) OnTime;
    
    // Optional resource
    // 5854 - The time in seconds since the Off command was sent. Writing a value of 0 resets the counter.
    Resource(5854, &instance::OffTime, O_RES_RW) OffTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3342::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3342::RESID c1) { return (uint16_t) c1 == c2; }
	