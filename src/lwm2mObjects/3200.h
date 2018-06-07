#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3200 {
/* \brief Class for object 3200 - Digital Input
 *  Generic digital input for non-specific sensors
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5500 - The current state of a digital input.
    bool DigitalInputState;
    
    // Optional resource
    // 5501 - The cumulative value of active state detected.
    int DigitalInputCounter;
    
    // Optional resource
    // 5502 - The polarity of the digital input as a Boolean (0 = Normal, 1= Reversed)
    bool DigitalInputPolarity;
    
    // Optional resource
    // 5503 - The debounce period in ms. .
    int DigitalInputDebounce;
    
    // Optional resource
    // 5504 - The edge selection as an integer (1 = Falling edge, 2 = Rising edge, 3 = Both Rising and Falling edge).
    int DigitalInputEdgeSelection;
    
    // Optional resource
    // 5505 - Reset the Counter value.
    Executable DigitalInputCounterReset;

    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”
    PreallocString<30> ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    PreallocString<30> SensorType;
    
    enum class RESID {
        DigitalInputState = 5500,
        DigitalInputCounter = 5501,
        DigitalInputPolarity = 5502,
        DigitalInputDebounce = 5503,
        DigitalInputEdgeSelection = 5504,
        DigitalInputCounterReset = 5505,
        ApplicationType = 5750,
        SensorType = 5751,
        
    };
};

/* \brief Class for object 3200 - Digital Input
 *  Generic digital input for non-specific sensors
 */
class object : public Lwm2mObject<3200, object, instance> {
public:

    // 5500 - The current state of a digital input.
    Resource(5500, &instance::DigitalInputState, O_RES_R) DigitalInputState;
    
    // Optional resource
    // 5501 - The cumulative value of active state detected.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5502 - The polarity of the digital input as a Boolean (0 = Normal, 1= Reversed)
    Resource(5502, &instance::DigitalInputPolarity, O_RES_RW) DigitalInputPolarity;
    
    // Optional resource
    // 5503 - The debounce period in ms. .
    Resource(5503, &instance::DigitalInputDebounce, O_RES_RW) DigitalInputDebounce;
    
    // Optional resource
    // 5504 - The edge selection as an integer (1 = Falling edge, 2 = Rising edge, 3 = Both Rising and Falling edge).
    Resource(5504, &instance::DigitalInputEdgeSelection, O_RES_RW) DigitalInputEdgeSelection;
    
    // Optional resource
    // 5505 - Reset the Counter value.
    Resource(5505, &instance::DigitalInputCounterReset) DigitalInputCounterReset;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string, for instance, “Air Pressure”
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    Resource(5751, &instance::SensorType, O_RES_R) SensorType;
    
};

} // end of id namespace
inline bool operator== (id3200::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3200::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	