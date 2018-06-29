#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10286 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ULdata10286
    class ULdataType : public Opaque<30> {};
    #endif
    
    #ifndef DLdata10286
    class DLdataType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10286 - App Fota Container
 *  This LWM2M Object is used to download the firmware package of a device's application.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Running firmware package information of a device's application,e.g. version of firmare package.
    ULdataType ULdata;
    
    // 1 - Package URI and the data sequence of firmware package.
    DLdataType DLdata;
    
};

enum class RESID {
    ULdata = 0,
    DLdata = 1,
    
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
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10286::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10286::RESID c1) { return (uint16_t) c1 == c2; }
	