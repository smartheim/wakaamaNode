#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3302 {
// Custom, overrideable types for Opaque and String resources

    #ifndef DigitalInputCounterReset3302
    class DigitalInputCounterResetType : public Opaque<30> {};
    #endif
    
    #ifndef SensorType3302
    class SensorTypeType : public PreallocString<30> {};
    #endif
    

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
    SensorTypeType SensorType;
    
    // Optional resource
    // 5903 - Delay from the detection state to the clear state in ms
    int BusytoCleardelay;
    
    // Optional resource
    // 5904 - Delay from the clear state to the busy state in ms
    int CleartoBusydelay;
    
};

enum class RESID {
    DigitalInputState = 5500,
    DigitalInputCounter = 5501,
    DigitalInputCounterReset = 5505,
    SensorType = 5751,
    BusytoCleardelay = 5903,
    CleartoBusydelay = 5904,
    
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
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3302::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3302::RESID c1) { return (uint16_t) c1 == c2; }
	