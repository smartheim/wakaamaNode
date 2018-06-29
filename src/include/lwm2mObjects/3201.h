#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3201 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3201
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3201 - Digital Output
 *  Generic digital output for non-specific actuators
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5550 - The current state of a digital output.
    bool DigitalOutputState;
    
    // Optional resource
    // 5551 - The polarity of a digital ouput as a Boolean (0 = Normal, 1= Reversed).
    bool DigitalOutputPolarity;
    
    // Optional resource
    // 5750 - The application type of the output as a string, for instance, “LED”
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    DigitalOutputState = 5550,
    DigitalOutputPolarity = 5551,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3201 - Digital Output
 *  Generic digital output for non-specific actuators
 */
class object : public Lwm2mObject<3201, object, instance> {
public:

    // 5550 - The current state of a digital output.
    Resource(5550, &instance::DigitalOutputState, O_RES_RW) DigitalOutputState;
    
    // Optional resource
    // 5551 - The polarity of a digital ouput as a Boolean (0 = Normal, 1= Reversed).
    Resource(5551, &instance::DigitalOutputPolarity, O_RES_RW) DigitalOutputPolarity;
    
    // Optional resource
    // 5750 - The application type of the output as a string, for instance, “LED”
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3201::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3201::RESID c1) { return (uint16_t) c1 == c2; }
	