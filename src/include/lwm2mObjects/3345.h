#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3345 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3345
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3345 - Multiple Axis Joystick
 *  This IPSO object can be used to report the position of a shuttle or joystick control.
 *  A digital input is provided to report the state of an associated push button.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 5500 - The current state of a digital input.
    bool DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    int DigitalInputCounter;
    
    // Optional resource
    // 5702 - The measured value along the X axis.
    float XValue;
    
    // Optional resource
    // 5703 - The measured value along the Y axis.
    float YValue;
    
    // Optional resource
    // 5704 - The measured value along the Z axis.
    float ZValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    DigitalInputState = 5500,
    DigitalInputCounter = 5501,
    XValue = 5702,
    YValue = 5703,
    ZValue = 5704,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3345 - Multiple Axis Joystick
 *  This IPSO object can be used to report the position of a shuttle or joystick control.
 *  A digital input is provided to report the state of an associated push button.
 */
class object : public Lwm2mObject<3345, object, instance> {
public:

    // Optional resource
    // 5500 - The current state of a digital input.
    Resource(5500, &instance::DigitalInputState, O_RES_R) DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5702 - The measured value along the X axis.
    Resource(5702, &instance::XValue, O_RES_R) XValue;
    
    // Optional resource
    // 5703 - The measured value along the Y axis.
    Resource(5703, &instance::YValue, O_RES_R) YValue;
    
    // Optional resource
    // 5704 - The measured value along the Z axis.
    Resource(5704, &instance::ZValue, O_RES_R) ZValue;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3345::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3345::RESID c1) { return (uint16_t) c1 == c2; }
	