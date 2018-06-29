#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3347 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3347
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3347 - Push button
 *  This IPSO object is used to report the state of a momentary action push button control
 *  and to count the number of times the control has been operated since the last observation.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5500 - The current state of a digital input.
    bool DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    int DigitalInputStateTransitions;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    DigitalInputState = 5500,
    DigitalInputStateTransitions = 5501,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3347 - Push button
 *  This IPSO object is used to report the state of a momentary action push button control
 *  and to count the number of times the control has been operated since the last observation.
 */
class object : public Lwm2mObject<3347, object, instance> {
public:

    // 5500 - The current state of a digital input.
    Resource(5500, &instance::DigitalInputState, O_RES_R) DigitalInputState;
    
    // Optional resource
    // 5501 - The number of times the input transitions from 0 to 1.
    Resource(5501, &instance::DigitalInputStateTransitions, O_RES_R) DigitalInputStateTransitions;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3347::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3347::RESID c1) { return (uint16_t) c1 == c2; }
	