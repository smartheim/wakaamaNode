#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3202 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3202
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    
    #ifndef SensorType3202
    class SensorTypeType : public PreallocString<30> {};
    #endif
    
    #ifndef ResetMinandMaxMeasuredValues3202
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 3202 - Analog Input
 *  Generic analog input for non-specific sensors
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5600 - The current value of the analog input.
    float AnalogInputCurrentValue;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since power ON or reset
    float MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since power ON or reset
    float MaxMeasuredValue;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    float MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    float MaxRangeValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”
    ApplicationTypeType ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor, for instance PIR type
    SensorTypeType SensorType;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Executable ResetMinandMaxMeasuredValues;

};

enum class RESID {
    AnalogInputCurrentValue = 5600,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ApplicationType = 5750,
    SensorType = 5751,
    ResetMinandMaxMeasuredValues = 5605,
    
};

/* \brief Class for object 3202 - Analog Input
 *  Generic analog input for non-specific sensors
 */
class object : public Lwm2mObject<3202, object, instance> {
public:

    // 5600 - The current value of the analog input.
    Resource(5600, &instance::AnalogInputCurrentValue, O_RES_R) AnalogInputCurrentValue;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since power ON or reset
    Resource(5601, &instance::MinMeasuredValue, O_RES_R) MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since power ON or reset
    Resource(5602, &instance::MaxMeasuredValue, O_RES_R) MaxMeasuredValue;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    Resource(5603, &instance::MinRangeValue, O_RES_R) MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    Resource(5604, &instance::MaxRangeValue, O_RES_R) MaxRangeValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor, for instance PIR type
    Resource(5751, &instance::SensorType, O_RES_R) SensorType;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3202::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3202::RESID c1) { return (uint16_t) c1 == c2; }
	