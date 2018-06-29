#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2048 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Name2048
    class NameType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 2048 - CmdhPolicy
 *  This Object provides links to a set of rules associated with a specific CSE that governs
 *  the behavior of that CSE regarding rejecting, buffering and sending request or response
 *  messages via the Mcc reference point.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains the name of a CmdhPolicy Object Instance 
    NameType Name;
    
    // 1 - 1 reference to CmdhDefaults Object  Instance
    // Objlnk resources are not supported yet - DefaultRule;
    
    // 2 - 1 or more references to CmdhLimits Object Instances
    // Objlnk resources are not supported yet - LimiRules;
    
    // 3 - 1 or more references to CmdhNetworkAccessRules Object Instances
    // Objlnk resources are not supported yet - NetworkAccessECRules;
    
    // 4 - 1 or more references to CmdhBuffer Object Instances
    // Objlnk resources are not supported yet - BufferRules;
    
};

enum class RESID {
    Name = 0,
    DefaultRule = 1,
    LimiRules = 2,
    NetworkAccessECRules = 3,
    BufferRules = 4,
    
};

/* \brief Class for object 2048 - CmdhPolicy
 *  This Object provides links to a set of rules associated with a specific CSE that governs
 *  the behavior of that CSE regarding rejecting, buffering and sending request or response
 *  messages via the Mcc reference point.
 */
class object : public Lwm2mObject<2048, object, instance> {
public:

    // 0 - Contains the name of a CmdhPolicy Object Instance 
    Resource(0, &instance::Name, O_RES_RW) Name;
    
    // 1 - 1 reference to CmdhDefaults Object  Instance
    // Objlnk resources are not supported yet - DefaultRule;
    
    // 2 - 1 or more references to CmdhLimits Object Instances
    // Objlnk resources are not supported yet - LimiRules;
    
    // 3 - 1 or more references to CmdhNetworkAccessRules Object Instances
    // Objlnk resources are not supported yet - NetworkAccessECRules;
    
    // 4 - 1 or more references to CmdhBuffer Object Instances
    // Objlnk resources are not supported yet - BufferRules;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2048::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2048::RESID c1) { return (uint16_t) c1 == c2; }
	