#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10258 {
// Custom, overrideable types for Opaque and String resources

    #ifndef SensorUnits10258
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType10258
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10258 - Current Loop Output
 *  This LWM2M Object provides a representation of a current loop source, which may be used
 *  to carry control signals.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The current value of the current loop output.
    float CurrentLoopOutputCurrentValue;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    float MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    float MaxRangeValue;
    
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
    CurrentLoopOutputCurrentValue = 0,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    SensorUnits = 5701,
    ApplicationType = 5750,
    CurrentCalibration = 5821,
    
};

/* \brief Class for object 10258 - Current Loop Output
 *  This LWM2M Object provides a representation of a current loop source, which may be used
 *  to carry control signals.
 */
class object : public Lwm2mObject<10258, object, instance> {
public:

    // 0 - The current value of the current loop output.
    Resource(0, &instance::CurrentLoopOutputCurrentValue, O_RES_RW) CurrentLoopOutputCurrentValue;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    Resource(5603, &instance::MinRangeValue, O_RES_R) MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    Resource(5604, &instance::MaxRangeValue, O_RES_R) MaxRangeValue;
    
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
inline bool operator== (KnownObjects::id10258::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10258::RESID c1) { return (uint16_t) c1 == c2; }
	