#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3335 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Colour3335
    class ColourType : public PreallocString<30> {};
    #endif
    
    #ifndef SensorUnits3335
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3335
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3335 - Colour
 *  This IPSO object should be used to report the measured value of a colour sensor in some
 *  colour space described by the units resource.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5706 - A string representing a value in some colour space.
    ColourType Colour;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    SensorUnitsType SensorUnits;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Colour = 5706,
    SensorUnits = 5701,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3335 - Colour
 *  This IPSO object should be used to report the measured value of a colour sensor in some
 *  colour space described by the units resource.
 */
class object : public Lwm2mObject<3335, object, instance> {
public:

    // 5706 - A string representing a value in some colour space.
    Resource(5706, &instance::Colour, O_RES_RW) Colour;
    
    // Optional resource
    // 5701 - Measurement Units Definition e.g. “Cel” for Temperature in Celsius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3335::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3335::RESID c1) { return (uint16_t) c1 == c2; }
	