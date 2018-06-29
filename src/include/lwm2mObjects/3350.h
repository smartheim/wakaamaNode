#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3350 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3350
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3350 - Stopwatch
 *  An ascending timer that counts how long time has passed since the timer was started after
 *  reset.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5544 - The total time in seconds that the stopwatch has been on. Writing a 0 resets the time.
    float CumulativeTime;
    
    // Optional resource
    // 5850 - On/Off control for the stopwatch, True=ON, False=OFF.
    bool OnOff;
    
    // Optional resource
    // 5501 - The number of times the input transitions from off to on.
    int DigitalInputCounter;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    CumulativeTime = 5544,
    OnOff = 5850,
    DigitalInputCounter = 5501,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3350 - Stopwatch
 *  An ascending timer that counts how long time has passed since the timer was started after
 *  reset.
 */
class object : public Lwm2mObject<3350, object, instance> {
public:

    // 5544 - The total time in seconds that the stopwatch has been on. Writing a 0 resets the time.
    Resource(5544, &instance::CumulativeTime, O_RES_RW) CumulativeTime;
    
    // Optional resource
    // 5850 - On/Off control for the stopwatch, True=ON, False=OFF.
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5501 - The number of times the input transitions from off to on.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3350::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3350::RESID c1) { return (uint16_t) c1 == c2; }
	