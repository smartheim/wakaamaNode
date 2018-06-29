#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3301 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ResetMinandMaxMeasuredValues3301
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    
    #ifndef SensorUnits3301
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3301 - Illuminance
 *  Illuminance sensor, example units = lx
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5700 - The current value of the luminosity sensor.
    float SensorValue;
    
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
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Executable ResetMinandMaxMeasuredValues;

    // Optional resource
    // 5701 - If present, the type of sensor defined as the UCUM Unit Definition e.g. “Cel” for Temperature in Celcius.
    SensorUnitsType SensorUnits;
    
};

enum class RESID {
    SensorValue = 5700,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ResetMinandMaxMeasuredValues = 5605,
    SensorUnits = 5701,
    
};

/* \brief Class for object 3301 - Illuminance
 *  Illuminance sensor, example units = lx
 */
class object : public Lwm2mObject<3301, object, instance> {
public:

    // 5700 - The current value of the luminosity sensor.
    Resource(5700, &instance::SensorValue, O_RES_R) SensorValue;
    
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
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
    // Optional resource
    // 5701 - If present, the type of sensor defined as the UCUM Unit Definition e.g. “Cel” for Temperature in Celcius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3301::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3301::RESID c1) { return (uint16_t) c1 == c2; }
	