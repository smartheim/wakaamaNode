#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3369 {
/* \brief Class for object 3369 - macTimingAdvanceEvent
 *  Timing advance information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Timer Value
    int timerValue;
    
    // 1 - Timing Advance
    int timingAdvance;
    
    enum class RESID {
        timerValue = 0,
        timingAdvance = 1,
        
    };
};

/* \brief Class for object 3369 - macTimingAdvanceEvent
 *  Timing advance information
 */
class object : public Lwm2mObject<3369, object, instance> {
public:

    // 0 - Timer Value
    Resource(0, &instance::timerValue, O_RES_R) timerValue;
    
    // 1 - Timing Advance
    Resource(1, &instance::timingAdvance, O_RES_R) timingAdvance;
    
};

} // end of id namespace
inline bool operator== (id3369::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3369::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	