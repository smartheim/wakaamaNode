#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3302 {
/* \brief Class for object 3302 - Presence
 *  Presence sensor with digital sensing, optional delay parameters
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5500 - The current state of the presence sensor
    bool DigitalInputState;
    
    // Optional resource
    // 5501 - The cumulative value of active state detected.
    int DigitalInputCounter;
    
    // Optional resource
    // 5505 - Reset the Counter value
    Executable DigitalInputCounterReset;

    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    PreallocString<30> SensorType;
    
    // Optional resource
    // 5903 - Delay from the detection state to the clear state in ms
    int BusytoCleardelay;
    
    // Optional resource
    // 5904 - Delay from the clear state to the busy state in ms
    int CleartoBusydelay;
    
    enum class RESID {
        DigitalInputState = 5500,
        DigitalInputCounter = 5501,
        DigitalInputCounterReset = 5505,
        SensorType = 5751,
        BusytoCleardelay = 5903,
        CleartoBusydelay = 5904,
        
    };
};

/* \brief Class for object 3302 - Presence
 *  Presence sensor with digital sensing, optional delay parameters
 */
class object : public Lwm2mObject<3302, object, instance> {
public:

    // 5500 - The current state of the presence sensor
    Resource(5500, &instance::DigitalInputState, O_RES_R) DigitalInputState;
    
    // Optional resource
    // 5501 - The cumulative value of active state detected.
    Resource(5501, &instance::DigitalInputCounter, O_RES_R) DigitalInputCounter;
    
    // Optional resource
    // 5505 - Reset the Counter value
    Resource(5505, &instance::DigitalInputCounterReset) DigitalInputCounterReset;
    
    // Optional resource
    // 5751 - The type of the sensor (for instance PIR type)
    Resource(5751, &instance::SensorType, O_RES_R) SensorType;
    
    // Optional resource
    // 5903 - Delay from the detection state to the clear state in ms
    Resource(5903, &instance::BusytoCleardelay, O_RES_RW) BusytoCleardelay;
    
    // Optional resource
    // 5904 - Delay from the clear state to the busy state in ms
    Resource(5904, &instance::CleartoBusydelay, O_RES_RW) CleartoBusydelay;
    
};

} // end of id namespace
inline bool operator== (id3302::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3302::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	