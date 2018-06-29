#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10260 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Key10260
    class KeyType : public PreallocString<30> {};
    #endif
    
    #ifndef Value10260
    class ValueType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10260 - RDB
 *  This object allows manipulation of Runtime Database variables.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The name of the RDB variable that this instance currently represents. Writing to this resource will not rename or otherwise modify the associated RDB variable, rather it will re-assign the instance to represent a different variable.
    KeyType Key;
    
    // Optional resource
    // 1 - The current value of the RDB variable associated with this instance. Reading this resource will return a "Not Found" response code if the associated variable does not exist. Writing to this resource will create the associated variable if it does not already exist.
    ValueType Value;
    
    // Optional resource
    // 2 - Indicates whether the RDB variable associated with this instance currently exists. Writing FALSE to this resource will delete the associated variable if it exists. Writing TRUE to this resource will create the associated variable if it does not already exist. Variables created by this resource will be initialised to an empty string.
    bool Exists;
    
    // Optional resource
    // 3 - Configure whether or not the RDB variable associated with this instance will be saved to persistent storage.
    bool Persistent;
    
};

enum class RESID {
    Key = 0,
    Value = 1,
    Exists = 2,
    Persistent = 3,
    
};

/* \brief Class for object 10260 - RDB
 *  This object allows manipulation of Runtime Database variables.
 */
class object : public Lwm2mObject<10260, object, instance> {
public:

    // 0 - The name of the RDB variable that this instance currently represents. Writing to this resource will not rename or otherwise modify the associated RDB variable, rather it will re-assign the instance to represent a different variable.
    Resource(0, &instance::Key, O_RES_RW) Key;
    
    // Optional resource
    // 1 - The current value of the RDB variable associated with this instance. Reading this resource will return a "Not Found" response code if the associated variable does not exist. Writing to this resource will create the associated variable if it does not already exist.
    Resource(1, &instance::Value, O_RES_RW) Value;
    
    // Optional resource
    // 2 - Indicates whether the RDB variable associated with this instance currently exists. Writing FALSE to this resource will delete the associated variable if it exists. Writing TRUE to this resource will create the associated variable if it does not already exist. Variables created by this resource will be initialised to an empty string.
    Resource(2, &instance::Exists, O_RES_RW) Exists;
    
    // Optional resource
    // 3 - Configure whether or not the RDB variable associated with this instance will be saved to persistent storage.
    Resource(3, &instance::Persistent, O_RES_RW) Persistent;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10260::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10260::RESID c1) { return (uint16_t) c1 == c2; }
	