#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3331 {
// Custom, overrideable types for Opaque and String resources

    #ifndef SensorUnits3331
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3331
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3331 - Energy
 *  This IPSO object should be used to report energy consumption (Cumulative Power) of
 *  an electrical load. An example measurement unit is Watt Hours (ucum:W*h).
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5805 - Last or Current Measured Value from the Sensor.
    float SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    SensorUnitsType SensorUnits;
    
    // Optional resource
    // 5822 - Reset both cumulative active/reactive power.
    Executable ResetCumulativeEnergy;

    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    SensorValue = 5805,
    SensorUnits = 5701,
    ResetCumulativeEnergy = 5822,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3331 - Energy
 *  This IPSO object should be used to report energy consumption (Cumulative Power) of
 *  an electrical load. An example measurement unit is Watt Hours (ucum:W*h).
 */
class object : public Lwm2mObject<3331, object, instance> {
public:

    // 5805 - Last or Current Measured Value from the Sensor.
    Resource(5805, &instance::SensorValue, O_RES_R) SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
    // Optional resource
    // 5822 - Reset both cumulative active/reactive power.
    Resource(5822, &instance::ResetCumulativeEnergy) ResetCumulativeEnergy;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3331::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3331::RESID c1) { return (uint16_t) c1 == c2; }
	