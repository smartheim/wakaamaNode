#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10253 {
// Custom, overrideable types for Opaque and String resources

    #ifndef PublicKey10253
    class PublicKeyType : public Opaque<30> {};
    #endif
    
    #ifndef ApplicationData10253
    class ApplicationDataType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10253 - Confidential Data
 *  This LWM2M Object is used for reporting data, but in a confidential way
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Object public key provided from the server side
    PublicKeyType PublicKey;
    
    // 1 - Application Data encrypted by the Public Key
    ApplicationDataType ApplicationData;
    
};

enum class RESID {
    PublicKey = 0,
    ApplicationData = 1,
    
};

/* \brief Class for object 10253 - Confidential Data
 *  This LWM2M Object is used for reporting data, but in a confidential way
 */
class object : public Lwm2mObject<10253, object, instance> {
public:

    // 0 - Object public key provided from the server side
    Resource(0, &instance::PublicKey, O_RES_RW) PublicKey;
    
    // 1 - Application Data encrypted by the Public Key
    Resource(1, &instance::ApplicationData, O_RES_R) ApplicationData;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10253::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10253::RESID c1) { return (uint16_t) c1 == c2; }
	