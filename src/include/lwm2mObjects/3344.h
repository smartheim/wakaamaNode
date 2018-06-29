#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3344 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3344
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3344 - Up/Down Control
 *  This IPSO object is used to report the state of an up/down control element like a pair
 *  of push buttons or a rotary encoder. Counters for increase and decrease operations
 *  are provided for counting pulses from a quadrature encoder.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5532 - Indicates an increase control action.
    bool IncreaseInputState;
    
    // 5533 - Indicates a decrease control action.
    bool DecreaseInputState;
    
    // Optional resource
    // 5541 - Counts the number of times the increase control has been operated. Writing a 0 resets the counter.
    int UpCounter;
    
    // Optional resource
    // 5542 - Counts the times the decrease control has been operated. Writing a 0 resets the counter.
    int DownCounter;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    IncreaseInputState = 5532,
    DecreaseInputState = 5533,
    UpCounter = 5541,
    DownCounter = 5542,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3344 - Up/Down Control
 *  This IPSO object is used to report the state of an up/down control element like a pair
 *  of push buttons or a rotary encoder. Counters for increase and decrease operations
 *  are provided for counting pulses from a quadrature encoder.
 */
class object : public Lwm2mObject<3344, object, instance> {
public:

    // 5532 - Indicates an increase control action.
    Resource(5532, &instance::IncreaseInputState, O_RES_R) IncreaseInputState;
    
    // 5533 - Indicates a decrease control action.
    Resource(5533, &instance::DecreaseInputState, O_RES_R) DecreaseInputState;
    
    // Optional resource
    // 5541 - Counts the number of times the increase control has been operated. Writing a 0 resets the counter.
    Resource(5541, &instance::UpCounter, O_RES_RW) UpCounter;
    
    // Optional resource
    // 5542 - Counts the times the decrease control has been operated. Writing a 0 resets the counter.
    Resource(5542, &instance::DownCounter, O_RES_RW) DownCounter;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3344::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3344::RESID c1) { return (uint16_t) c1 == c2; }
	