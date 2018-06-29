#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id2049 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 2049 - ActiveCmdhPolicy
 *  This Object provides a link to the currently active set of CMDH policies
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains the reference to the CMDH policies (CmdhPolicy Object Instance) currently active for the associated CSE.
    // Objlnk resources are not supported yet - ActiveLink;
    
};

enum class RESID {
    ActiveLink = 0,
    
};

/* \brief Class for object 2049 - ActiveCmdhPolicy
 *  This Object provides a link to the currently active set of CMDH policies
 */
class object : public Lwm2mObject<2049, object, instance> {
public:

    // 0 - Contains the reference to the CMDH policies (CmdhPolicy Object Instance) currently active for the associated CSE.
    // Objlnk resources are not supported yet - ActiveLink;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id2049::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id2049::RESID c1) { return (uint16_t) c1 == c2; }
	