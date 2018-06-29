#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3337 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3337
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3337 - Positioner
 *  This IPSO object should be used with a generic position actuator from 0 to 100%. This
 *  resource optionally allows setting the transition time for an operation that changes
 *  the position of the actuator, and for reading the remaining time of the currently active
 *  transition.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5536 - Current position or desired position of a positioner actuator.
    float CurrentPosition;
    
    // Optional resource
    // 5537 - The time expected to move the actuator to the new position.
    float TransitionTime;
    
    // Optional resource
    // 5538 - The time remaining in an operation.
    float RemainingTime;
    
    // Optional resource
    // 5601 - The minimum value set on the actuator since power ON or reset.
    float MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value set on the actuator since power ON or reset.
    float MaxMeasuredValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Executable ResetMinandMaxMeasuredValue;

    // Optional resource
    // 5519 - The minimum value that can be measured by the sensor.
    float MinLimit;
    
    // Optional resource
    // 5520 - The maximum value that can be measured by the sensor.
    float MaxLimit;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    CurrentPosition = 5536,
    TransitionTime = 5537,
    RemainingTime = 5538,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    ResetMinandMaxMeasuredValue = 5605,
    MinLimit = 5519,
    MaxLimit = 5520,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3337 - Positioner
 *  This IPSO object should be used with a generic position actuator from 0 to 100%. This
 *  resource optionally allows setting the transition time for an operation that changes
 *  the position of the actuator, and for reading the remaining time of the currently active
 *  transition.
 */
class object : public Lwm2mObject<3337, object, instance> {
public:

    // 5536 - Current position or desired position of a positioner actuator.
    Resource(5536, &instance::CurrentPosition, O_RES_RW) CurrentPosition;
    
    // Optional resource
    // 5537 - The time expected to move the actuator to the new position.
    Resource(5537, &instance::TransitionTime, O_RES_RW) TransitionTime;
    
    // Optional resource
    // 5538 - The time remaining in an operation.
    Resource(5538, &instance::RemainingTime, O_RES_R) RemainingTime;
    
    // Optional resource
    // 5601 - The minimum value set on the actuator since power ON or reset.
    Resource(5601, &instance::MinMeasuredValue, O_RES_R) MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value set on the actuator since power ON or reset.
    Resource(5602, &instance::MaxMeasuredValue, O_RES_R) MaxMeasuredValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Resource(5605, &instance::ResetMinandMaxMeasuredValue) ResetMinandMaxMeasuredValue;
    
    // Optional resource
    // 5519 - The minimum value that can be measured by the sensor.
    Resource(5519, &instance::MinLimit, O_RES_R) MinLimit;
    
    // Optional resource
    // 5520 - The maximum value that can be measured by the sensor.
    Resource(5520, &instance::MaxLimit, O_RES_R) MaxLimit;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3337::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3337::RESID c1) { return (uint16_t) c1 == c2; }
	