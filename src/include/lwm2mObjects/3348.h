#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3348 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ApplicationType3348
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

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
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    MultistateInput = 5547,
    ApplicationType = 5750,
    
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
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3348::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3348::RESID c1) { return (uint16_t) c1 == c2; }
	