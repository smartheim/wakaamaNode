#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2054 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2054 - CmdhNetworkAccessRules
 *  This Object defines the usage of underlying networks for forwarding information to
 *  other CSEs during processing of CMDH-related requests in a CSE.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains  a list of Event Category values
    int ApplicableEventCategories;
    
    // Optional resource
    // 1 - Contains 0 or more references to CmdhNwAccessRule Object Instances 
    // Objlnk resources are not supported yet - NetworkAccessRule;
    
};

enum class RESID {
    ApplicableEventCategories = 0,
    NetworkAccessRule = 1,
    
};

/* \brief Class for object 2054 - CmdhNetworkAccessRules
 *  This Object defines the usage of underlying networks for forwarding information to
 *  other CSEs during processing of CMDH-related requests in a CSE.
 */
class object : public Lwm2mObject<2054, object, instance> {
public:

    // 0 - Contains  a list of Event Category values
    Resource(0, &instance::ApplicableEventCategories, O_RES_RW) ApplicableEventCategories;
    
    // Optional resource
    // 1 - Contains 0 or more references to CmdhNwAccessRule Object Instances 
    // Objlnk resources are not supported yet - NetworkAccessRule;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2054::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2054::RESID c1) { return (uint16_t) c1 == c2; }
	