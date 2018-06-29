#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3314 {
// Custom, overrideable types for Opaque and String resources

    #ifndef SensorUnits3314
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3314 - Magnetometer
 *  Description: This IPSO object can be used to represent a 1-3 axis magnetometer with
 *  optional compass direction.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5702 - The measured value along the X axis.
    float XValue;
    
    // Optional resource
    // 5703 - The measured value along the Y axis.
    float YValue;
    
    // Optional resource
    // 5704 - The measured value along the Z axis.
    float ZValue;
    
    // Optional resource
    // 5705 - The compass direction
    float CompassDirection;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    SensorUnitsType SensorUnits;
    
};

enum class RESID {
    XValue = 5702,
    YValue = 5703,
    ZValue = 5704,
    CompassDirection = 5705,
    SensorUnits = 5701,
    
};

/* \brief Class for object 3314 - Magnetometer
 *  Description: This IPSO object can be used to represent a 1-3 axis magnetometer with
 *  optional compass direction.
 */
class object : public Lwm2mObject<3314, object, instance> {
public:

    // 5702 - The measured value along the X axis.
    Resource(5702, &instance::XValue, O_RES_R) XValue;
    
    // Optional resource
    // 5703 - The measured value along the Y axis.
    Resource(5703, &instance::YValue, O_RES_R) YValue;
    
    // Optional resource
    // 5704 - The measured value along the Z axis.
    Resource(5704, &instance::ZValue, O_RES_R) ZValue;
    
    // Optional resource
    // 5705 - The compass direction
    Resource(5705, &instance::CompassDirection, O_RES_R) CompassDirection;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3314::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3314::RESID c1) { return (uint16_t) c1 == c2; }
	