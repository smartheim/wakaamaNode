#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3340 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Trigger3340
    class TriggerType : public Opaque<30> {};
    #endif
    
    #ifndef ApplicationType3340
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3340 - Timer
 *  This IPSO object is used to time events and actions, using patterns common to industrial
 *  timers. A POST to the trigger resource or On/Off input state change starts the timing
 *  operation, and the timer remaining time shows zero when the operation is complete.
 *  The patterns supported are One-Shot (mode 1), On-Time or Interval (mode 2), Time delay
 *  on pick-up or TDPU (tmode 3), and Time Delay on Drop-Out or TDDO (mode 4). Mode 0 disables
 *  the timer, so the output follows the input with no delay. A counter is provided to count
 *  occurrences of the timer output changing from 0 to 1. Writing a value of zero resets the
 *  counter. The Digital Input State resource reports the state of the timer output.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5521 - The duration of the time delay.
    float Duration;
    
    // Optional resource
    // 5538 - The time remaining in an operation.
    float RemainingTime;
    
    // Optional resource
    // 5525 - The duration of the rearm delay (i.e. the delay from the end of one cycle until the beginning of the next, the inhibit time).
    float MinimumOfftime;
    
    // Optional resource
    // 5523 - Trigger initiating actuation.
    Executable Trigger;

    // Optional resource
    // 5850 - On/off control for the timer input, 0=OFF, 1=ON.
    bool OnOff;
    
    // Optional resource
    // 5501 - The number of times the input.
    int DigitalInputCounter;
    
    // Optional resource
    // 5544 - The total time in seconds that the timer input is true. Writing a 0 resets the time.
    float CumulativeTime;
    
    // Optional resource
    // 5543 - The current state of the timer output.
    bool DigitalState;
    
    // Optional resource
    // 5534 - Counts the number of times the timer output transitions from 0 to 1.
    int Counter;
    
    // Optional resource
    // 5526 - Type of timer pattern used by the patterns.
    int Mode;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Duration = 5521,
    RemainingTime = 5538,
    MinimumOfftime = 5525,
    Trigger = 5523,
    OnOff = 5850,
    DigitalInputCounter = 5501,
    CumulativeTime = 5544,
    DigitalState = 5543,
    Counter = 5534,
    Mode = 5526,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3340 - Timer
 *  This IPSO object is used to time events and actions, using patterns common to industrial
 *  timers. A POST to the trigger resource or On/Off input state change starts the timing
 *  operation, and the timer remaining time shows zero when the operation is complete.
 *  The patterns supported are One-Shot (mode 1), On-Time or Interval (mode 2), Time delay
 *  on pick-up or TDPU (tmode 3), and Time Delay on Drop-Out or TDDO (mode 4). Mode 0 disables
 *  the timer, so the output follows the input with no delay. A counter is provided to count
 *  occurrences of the timer output changing from 0 to 1. Writing a value of zero resets the
 *  counter. The Digital Input State resource reports the state of the timer output.
 */
class object : public Lwm2mObject<3340, object, instance> {
public:

    // 5521 - The duration of the time delay.
    Resource(5521, &instance::Duration, O_RES_RW) Duration;
    
    // Optional resource
    // 5538 - The time remaining in an operation.
    Resource(5538, &instance::RemainingTime, O_RES_RW) RemainingTime;
    
    // Optional resource
    // 5525 - The duration of the rearm delay (i.e. the delay from the end of one cycle until the beginning of the next, the inhibit time).
    Resource(5525, &instance::MinimumOfftime, O_RES_RW) MinimumOfftime;
    
    // Optional resource
    // 5523 - Trigger initiating actuation.
    Resource(5523, &instance::Trigger) Trigger;
    
    // Optional resource
    // 5850 - On/off control for the timer input, 0=OFF, 1=ON.
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5501 - The number of times the input.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5544 - The total time in seconds that the timer input is true. Writing a 0 resets the time.
    Resource(5544, &instance::CumulativeTime, O_RES_RW) CumulativeTime;
    
    // Optional resource
    // 5543 - The current state of the timer output.
    Resource(5543, &instance::DigitalState, O_RES_R) DigitalState;
    
    // Optional resource
    // 5534 - Counts the number of times the timer output transitions from 0 to 1.
    Resource(5534, &instance::Counter, O_RES_RW) Counter;
    
    // Optional resource
    // 5526 - Type of timer pattern used by the patterns.
    Resource(5526, &instance::Mode, O_RES_RW) Mode;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3340::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3340::RESID c1) { return (uint16_t) c1 == c2; }
	