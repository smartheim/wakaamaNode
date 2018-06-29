#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3334 {
// Custom, overrideable types for Opaque and String resources

    #ifndef SensorUnits3334
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3334
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3334 - Gyrometer
 *  This IPSO Object is used to report the current reading of a gyrometer sensor in 3 axes.
 *  It provides tracking of the minimum and maximum angular rate in all 3 axes. An example
 *  unit of measure is radians per second (ucum:rad/s).
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
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    SensorUnitsType SensorUnits;
    
    // Optional resource
    // 5508 - The minimum measured value along the X axis
    float MinXValue;
    
    // Optional resource
    // 5509 - The maximum measured value along the X axis
    float MaxXValue;
    
    // Optional resource
    // 5510 - The minimum measured value along the Y axis
    float MinYValue;
    
    // Optional resource
    // 5511 - The maximum measured value along the Y axis
    float MaxYValue;
    
    // Optional resource
    // 5512 - The minimum measured value along the Z axis
    float MinZValue;
    
    // Optional resource
    // 5513 - The maximum measured value along the Z axis
    float MaxZValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Executable ResetMinandMaxMeasuredValues;

    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    float MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    float MaxRangeValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    XValue = 5702,
    YValue = 5703,
    ZValue = 5704,
    SensorUnits = 5701,
    MinXValue = 5508,
    MaxXValue = 5509,
    MinYValue = 5510,
    MaxYValue = 5511,
    MinZValue = 5512,
    MaxZValue = 5513,
    ResetMinandMaxMeasuredValues = 5605,
    MinRangeValue = 5603,
    MaxRangeValue = 5604,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3334 - Gyrometer
 *  This IPSO Object is used to report the current reading of a gyrometer sensor in 3 axes.
 *  It provides tracking of the minimum and maximum angular rate in all 3 axes. An example
 *  unit of measure is radians per second (ucum:rad/s).
 */
class object : public Lwm2mObject<3334, object, instance> {
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
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
    // Optional resource
    // 5508 - The minimum measured value along the X axis
    Resource(5508, &instance::MinXValue, O_RES_R) MinXValue;
    
    // Optional resource
    // 5509 - The maximum measured value along the X axis
    Resource(5509, &instance::MaxXValue, O_RES_R) MaxXValue;
    
    // Optional resource
    // 5510 - The minimum measured value along the Y axis
    Resource(5510, &instance::MinYValue, O_RES_R) MinYValue;
    
    // Optional resource
    // 5511 - The maximum measured value along the Y axis
    Resource(5511, &instance::MaxYValue, O_RES_R) MaxYValue;
    
    // Optional resource
    // 5512 - The minimum measured value along the Z axis
    Resource(5512, &instance::MinZValue, O_RES_R) MinZValue;
    
    // Optional resource
    // 5513 - The maximum measured value along the Z axis
    Resource(5513, &instance::MaxZValue, O_RES_R) MaxZValue;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value.
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
    // Optional resource
    // 5603 - The minimum value that can be measured by the sensor
    Resource(5603, &instance::MinRangeValue, O_RES_R) MinRangeValue;
    
    // Optional resource
    // 5604 - The maximum value that can be measured by the sensor
    Resource(5604, &instance::MaxRangeValue, O_RES_R) MaxRangeValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3334::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3334::RESID c1) { return (uint16_t) c1 == c2; }
	