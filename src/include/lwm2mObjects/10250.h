#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10250 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ULdata10250
    class ULdataType : public Opaque<30> {};
    #endif
    
    #ifndef DLdata10250
    class DLdataType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10250 - App Data Container
 *  This LWM2M Object is used for reporting application data of a device.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Uplink application data, e.g. gas meter reporting data.
    ULdataType ULdata;
    
    // 1 - Downlink application data, e.g. application response message of uplink data.
    DLdataType DLdata;
    
};

enum class RESID {
    ULdata = 0,
    DLdata = 1,
    
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
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10250::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10250::RESID c1) { return (uint16_t) c1 == c2; }
	