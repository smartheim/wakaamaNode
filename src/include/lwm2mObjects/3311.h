#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3311 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Colour3311
    class ColourType : public PreallocString<30> {};
    #endif
    
    #ifndef SensorUnits3311
    class SensorUnitsType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3311 - Light Control
 *  Description: This Object is used to control a light source, such as a LED or other light.
 *  It allows a light to be turned on or off and its dimmer setting to be control as a % between
 *  0 and 100. An optional colour setting enables a string to be used to indicate the desired
 *  colour.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5850 - This resource represents a light, which can be controlled, the setting of which is a Boolean value (1,0) where 1 is on and 0 is off.
    bool OnOff;
    
    // Optional resource
    // 5851 - This resource represents a light dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    int Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the light has been on. Writing a value of 0 resets the counter.
    int OnTime;
    
    // Optional resource
    // 5805 - The total power in Wh that the light has used.
    float Cumulativeactivepower;
    
    // Optional resource
    // 5820 - The power factor of the light.
    float PowerFactor;
    
    // Optional resource
    // 5706 - A string representing a value in some color space
    ColourType Colour;
    
    // Optional resource
    // 5701 - If present, the type of sensor defined as the UCUM Unit Definition e.g. “Cel” for Temperature in Celcius.
    SensorUnitsType SensorUnits;
    
};

enum class RESID {
    OnOff = 5850,
    Dimmer = 5851,
    OnTime = 5852,
    Cumulativeactivepower = 5805,
    PowerFactor = 5820,
    Colour = 5706,
    SensorUnits = 5701,
    
};

/* \brief Class for object 3311 - Light Control
 *  Description: This Object is used to control a light source, such as a LED or other light.
 *  It allows a light to be turned on or off and its dimmer setting to be control as a % between
 *  0 and 100. An optional colour setting enables a string to be used to indicate the desired
 *  colour.
 */
class object : public Lwm2mObject<3311, object, instance> {
public:

    // 5850 - This resource represents a light, which can be controlled, the setting of which is a Boolean value (1,0) where 1 is on and 0 is off.
    Resource(5850, &instance::OnOff, O_RES_RW) OnOff;
    
    // Optional resource
    // 5851 - This resource represents a light dimmer setting, which has an Integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5852 - The time in seconds that the light has been on. Writing a value of 0 resets the counter.
    Resource(5852, &instance::OnTime, O_RES_RW) OnTime;
    
    // Optional resource
    // 5805 - The total power in Wh that the light has used.
    Resource(5805, &instance::Cumulativeactivepower, O_RES_R) Cumulativeactivepower;
    
    // Optional resource
    // 5820 - The power factor of the light.
    Resource(5820, &instance::PowerFactor, O_RES_R) PowerFactor;
    
    // Optional resource
    // 5706 - A string representing a value in some color space
    Resource(5706, &instance::Colour, O_RES_RW) Colour;
    
    // Optional resource
    // 5701 - If present, the type of sensor defined as the UCUM Unit Definition e.g. “Cel” for Temperature in Celcius.
    Resource(5701, &instance::SensorUnits, O_RES_R) SensorUnits;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3311::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3311::RESID c1) { return (uint16_t) c1 == c2; }
	