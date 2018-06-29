#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3332 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3332
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3332 - Direction
 *  This IPSO object is used to report the direction indicated by a compass, wind vane, or
 *  other directional indicator. The units of measure is plane angle degrees (ucum:deg).
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5705 - This indicates the compass direction of some phenomenon (i.e. direction of travel, wind direction…).
    float CompassDirection;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since power ON or reset.
    float MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since power ON or reset.
    float MaxMeasuredValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Executable ResetMinandMaxMeasuredValues;

    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    CompassDirection = 5705,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    ResetMinandMaxMeasuredValues = 5605,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3332 - Direction
 *  This IPSO object is used to report the direction indicated by a compass, wind vane, or
 *  other directional indicator. The units of measure is plane angle degrees (ucum:deg).
 */
class object : public Lwm2mObject<3332, object, instance> {
public:

    // 5705 - This indicates the compass direction of some phenomenon (i.e. direction of travel, wind direction…).
    Resource(5705, &instance::CompassDirection, O_RES_R) CompassDirection;
    
    // Optional resource
    // 5601 - The minimum value measured by the sensor since power ON or reset.
    Resource(5601, &instance::MinMeasuredValue, O_RES_R) MinMeasuredValue;
    
    // Optional resource
    // 5602 - The maximum value measured by the sensor since power ON or reset.
    Resource(5602, &instance::MaxMeasuredValue, O_RES_R) MaxMeasuredValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3332::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3332::RESID c1) { return (uint16_t) c1 == c2; }
	