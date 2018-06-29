#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3300 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3300
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    
    #ifndef SensorType3300
    class SensorTypeType : public PreallocString<30> {};
    #endif
    
    #ifndef ResetMinandMaxMeasuredValues3300
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 3300 - Generic Sensor
 *  This IPSO object allow the description of a generic sensor. It is based on the description
 *  of a value and a unit according to the UCUM specification. Thus, any type of value defined
 *  within this specification can be reporting using this object.Specific object for
 *  a given range of sensors is described later in the document, enabling to identify the
 *  type of sensors directly from its Object ID. This object may be used as a generic object
 *  if a dedicated one does not exist.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5700 - Last or Current Measured Value from the Sensor
    float SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
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
    // 5750 - If present, the application type of the sensor as a string, for instance, “CO2”
    ApplicationTypeType ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    SensorTypeType SensorType;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Executable ResetMinandMaxMeasuredValues;

};

enum class RESID {
    SensorValue = 5700,
    SensorUnits = 5701,
    MinMeasuredValue = 5601,
    MaxMeasuredValue = 5602,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ApplicationType = 5750,
    SensorType = 5751,
    ResetMinandMaxMeasuredValues = 5605,
    
};

/* \brief Class for object 3300 - Generic Sensor
 *  This IPSO object allow the description of a generic sensor. It is based on the description
 *  of a value and a unit according to the UCUM specification. Thus, any type of value defined
 *  within this specification can be reporting using this object.Specific object for
 *  a given range of sensors is described later in the document, enabling to identify the
 *  type of sensors directly from its Object ID. This object may be used as a generic object
 *  if a dedicated one does not exist.
 */
class object : public Lwm2mObject<3300, object, instance> {
public:

    // 5700 - Last or Current Measured Value from the Sensor
    Resource(5700, &instance::SensorValue, O_RES_R) SensorValue;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
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
    // 5750 - If present, the application type of the sensor as a string, for instance, “CO2”
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    Resource(5751, &instance::SensorType, O_RES_R) SensorType;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3300::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3300::RESID c1) { return (uint16_t) c1 == c2; }
	