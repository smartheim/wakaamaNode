#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10254 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ResetMinandMaxMeasuredValues10254
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    
    #ifndef SensorUnits10254
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType10254
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10254 - Current Loop Input
 *  This LWM2M Object provides a representation of a current loop sensor, which indicates
 *  the value emitted by a current source.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The current value of the current loop input. A value of 0 indicates the not-connected state and/or invalid (i.e. out-of-range) values.
    float CurrentLoopInputCurrentValue;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since it is ON or Reset.
    float MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since it is ON or Reset
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
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    SensorUnitsType SensorUnits;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”.
    ApplicationTypeType ApplicationType;
    
    // Optional resource
    // 5821 - Read or Write the current calibration coefficient
    float CurrentCalibration;
    
};

enum class RESID {
    CurrentLoopInputCurrentValue = 0,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ResetMinandMaxMeasuredValues = 5605,
    SensorUnits = 5701,
    ApplicationType = 5750,
    CurrentCalibration = 5821,
    
};

/* \brief Class for object 10254 - Current Loop Input
 *  This LWM2M Object provides a representation of a current loop sensor, which indicates
 *  the value emitted by a current source.
 */
class object : public Lwm2mObject<10254, object, instance> {
public:

    // 0 - The current value of the current loop input. A value of 0 indicates the not-connected state and/or invalid (i.e. out-of-range) values.
    Resource(0, &instance::CurrentLoopInputCurrentValue, O_RES_R) CurrentLoopInputCurrentValue;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since it is ON or Reset.
    Resource(5601, &instance::MinMeasuredValue, O_RES_R) MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since it is ON or Reset
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
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
    // Optional resource
    // 5821 - Read or Write the current calibration coefficient
    Resource(5821, &instance::CurrentCalibration, O_RES_RW) CurrentCalibration;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10254::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10254::RESID c1) { return (uint16_t) c1 == c2; }
	