#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id2050 {
/* \brief Class for object 2050 - CmdhDefaults
 *  Defines which CMDH related parameters will be used by default.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 or more references to  CmdhDefEcValue Object Instances containing default values for the ec (event category) parameter of an incoming request or response when this parameter is not indicated in the message itself 
    // Objlnk resources are not supported yet - DefaultEcRules;
    
    // 1 - 1 or more references to CmdhEcDefParamValues Object Instances 
    // Objlnk resources are not supported yet - DefaultEcParamRules;
    
    enum class RESID {
        DefaultEcRules = 0,
        DefaultEcParamRules = 1,
        
    };
};

/* \brief Class for object 2050 - CmdhDefaults
 *  Defines which CMDH related parameters will be used by default.
 */
class object : public Lwm2mObject<2050, object, instance> {
public:

    // 0 - 1 or more references to  CmdhDefEcValue Object Instances containing default values for the ec (event category) parameter of an incoming request or response when this parameter is not indicated in the message itself 
    // Objlnk resources are not supported yet - DefaultEcRules;
    
    // 1 - 1 or more references to CmdhEcDefParamValues Object Instances 
    // Objlnk resources are not supported yet - DefaultEcParamRules;
    
};

} // end of id namespace
inline bool operator== (id2050::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id2050::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	