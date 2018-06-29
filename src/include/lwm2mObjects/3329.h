#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3329 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ResetMinandMaxMeasuredValues3329
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    
    #ifndef CurrentCalibration3329
    class CurrentCalibrationType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3329
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3329 - Power Factor
 *  This IPSO object should be used to report a measurement or calculation of the power factor
 *  of a reactive electrical load. Power Factor is normally the ratio of non-reactive power
 *  to total power. This object also provides resources for minimum and maximum measured
 *  values, as well as the minimum and maximum range that can be measured by the sensor.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5700 - Last or Current Measured Value from the Sensor
    float SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius
    float SensorUnits;
    
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
    // 5821 - Read or Write the current calibration coefficient
    CurrentCalibrationType CurrentCalibration;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    SensorValue = 5700,
    SensorUnits = 5701,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ResetMinandMaxMeasuredValues = 5605,
    CurrentCalibration = 5821,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3329 - Power Factor
 *  This IPSO object should be used to report a measurement or calculation of the power factor
 *  of a reactive electrical load. Power Factor is normally the ratio of non-reactive power
 *  to total power. This object also provides resources for minimum and maximum measured
 *  values, as well as the minimum and maximum range that can be measured by the sensor.
 */
class object : public Lwm2mObject<3329, object, instance> {
public:

    // 5700 - Last or Current Measured Value from the Sensor
    Resource(5700, &instance::SensorValue, O_RES_R) SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
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
    // 5821 - Read or Write the current calibration coefficient
    Resource(5821, &instance::CurrentCalibration, O_RES_RW) CurrentCalibration;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3329::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3329::RESID c1) { return (uint16_t) c1 == c2; }
	