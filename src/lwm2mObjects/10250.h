#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id10250 {
/* \brief Class for object 10250 - App Data Container
 *  This LWM2M Object is used for reporting application data of a device.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Uplink application data, e.g. gas meter reporting data.
    Opaque<30> ULdata;
    
    // 1 - Downlink application data, e.g. application response message of uplink data.
    Opaque<30> DLdata;
    
    enum class RESID {
        ULdata = 0,
        DLdata = 1,
        
    };
};

/* \brief Class for object 10250 - App Data Container
 *  This LWM2M Object is used for reporting application data of a device.
 */
class object : public Lwm2mObject<10250, object, instance> {
public:

    // 0 - Uplink application data, e.g. gas meter reporting data.
    Resource(0, &instance::ULdata, O_RES_R) ULdata;
    
    // 1 - Downlink application data, e.g. application response message of uplink data.
    Resource(1, &instance::DLdata, O_RES_W) DLdata;
    
};

} // end of id namespace
inline bool operator== (id10250::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id10250::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	