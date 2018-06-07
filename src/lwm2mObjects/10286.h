#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id10286 {
/* \brief Class for object 10286 - App Fota Container
 *  This LWM2M Object is used to download the firmware package of a device's application.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Running firmware package information of a device's application,e.g. version of firmare package.
    Opaque<30> ULdata;
    
    // 1 - Package URI and the data sequence of firmware package.
    Opaque<30> DLdata;
    
    enum class RESID {
        ULdata = 0,
        DLdata = 1,
        
    };
};

/* \brief Class for object 10286 - App Fota Container
 *  This LWM2M Object is used to download the firmware package of a device's application.
 */
class object : public Lwm2mObject<10286, object, instance> {
public:

    // 0 - Running firmware package information of a device's application,e.g. version of firmare package.
    Resource(0, &instance::ULdata, O_RES_R) ULdata;
    
    // 1 - Package URI and the data sequence of firmware package.
    Resource(1, &instance::DLdata, O_RES_W) DLdata;
    
};

} // end of id namespace
inline bool operator== (id10286::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id10286::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	