#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3203 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3203
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3203 - Analog Output
 *  This IPSO object is a generic object that can be used with any kind of analog output interface.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5650 - The current state of the analogue output.
    float AnalogOutputCurrentValue;
    
    // Optional resource
    // 5750 - If present, the application type of the actuator as a string, for instance, “Thermostat”
    ApplicationTypeType ApplicationType;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    float MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    float MaxRangeValue;
    
};

enum class RESID {
    AnalogOutputCurrentValue = 5650,
    ApplicationType = 5750,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    
};

/* \brief Class for object 3203 - Analog Output
 *  This IPSO object is a generic object that can be used with any kind of analog output interface.
 */
class object : public Lwm2mObject<3203, object, instance> {
public:

    // 5650 - The current state of the analogue output.
    Resource(5650, &instance::AnalogOutputCurrentValue, O_RES_RW) AnalogOutputCurrentValue;
    
    // Optional resource
    // 5750 - If present, the application type of the actuator as a string, for instance, “Thermostat”
    Resource(5750, &instance::ApplicationType, O_RES_R) ApplicationType;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    Resource(5603, &instance::MinRangeValue, O_RES_R) MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    Resource(5604, &instance::MaxRangeValue, O_RES_R) MaxRangeValue;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3203::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3203::RESID c1) { return (uint16_t) c1 == c2; }
	