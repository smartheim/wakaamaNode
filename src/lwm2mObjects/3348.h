#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3348 {
/* \brief Class for object 3348 - Multi-state Selector
 *  This IPSO object is used to represent the state of a Multi-state selector switch with
 *  a number of fixed positions.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5547 - The current state of a Multi-state input or selector.
    int MultistateInput;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    PreallocString<30> ApplicationType;
    
    enum class RESID {
        MultistateInput = 5547,
        ApplicationType = 5750,
        
    };
};

/* \brief Class for object 3348 - Multi-state Selector
 *  This IPSO object is used to represent the state of a Multi-state selector switch with
 *  a number of fixed positions.
 */
class object : public Lwm2mObject<3348, object, instance> {
public:

    // 5547 - The current state of a Multi-state input or selector.
    Resource(5547, &instance::MultistateInput, O_RES_R) MultistateInput;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
inline bool operator== (id3348::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3348::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	