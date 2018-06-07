#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id10253 {
/* \brief Class for object 10253 - Confidential Data
 *  This LWM2M Object is used for reporting data, but in a confidential way
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Object public key provided from the server side
    Opaque<30> PublicKey;
    
    // 1 - Application Data encrypted by the Public Key
    Opaque<30> ApplicationData;
    
    enum class RESID {
        PublicKey = 0,
        ApplicationData = 1,
        
    };
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
inline bool operator== (id10253::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id10253::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	