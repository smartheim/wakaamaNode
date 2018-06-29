#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10255 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Bootloaderhash10255
    class BootloaderhashType : public Opaque<30> {};
    #endif
    
    #ifndef OEMbootloaderhash10255
    class OEMbootloaderhashType : public Opaque<30> {};
    #endif
    
    #ifndef Vendor10255
    class VendorType : public PreallocString<30> {};
    #endif
    
    #ifndef Class10255
    class ClassType : public PreallocString<30> {};
    #endif
    
    #ifndef Device10255
    class DeviceType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10255 - Device Metadata
 *  This object provides a range of information related to device metadata
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Manifest protocol supported
    int Protocolsupported;
    
    // 1 - Hash of the bootloader. This is used for tracking the version of the bootloader used.
    BootloaderhashType Bootloaderhash;
    
    // 2 - If the end-user has modified the bootloader the hash of the modified bootloader is recorded here
    OEMbootloaderhashType OEMbootloaderhash;
    
    // 3 - Vendor Class UUID
    VendorType Vendor;
    
    // 4 - Class UUID
    ClassType Class;
    
    // 5 - Device UUID
    DeviceType Device;
    
};

enum class RESID {
    Protocolsupported = 0,
    Bootloaderhash = 1,
    OEMbootloaderhash = 2,
    Vendor = 3,
    Class = 4,
    Device = 5,
    
};

/* \brief Class for object 10255 - Device Metadata
 *  This object provides a range of information related to device metadata
 */
class object : public Lwm2mObject<10255, object, instance> {
public:

    // 0 - Manifest protocol supported
    Resource(0, &instance::Protocolsupported, O_RES_R) Protocolsupported;
    
    // 1 - Hash of the bootloader. This is used for tracking the version of the bootloader used.
    Resource(1, &instance::Bootloaderhash, O_RES_R) Bootloaderhash;
    
    // 2 - If the end-user has modified the bootloader the hash of the modified bootloader is recorded here
    Resource(2, &instance::OEMbootloaderhash, O_RES_R) OEMbootloaderhash;
    
    // 3 - Vendor Class UUID
    Resource(3, &instance::Vendor, O_RES_R) Vendor;
    
    // 4 - Class UUID
    Resource(4, &instance::Class, O_RES_R) Class;
    
    // 5 - Device UUID
    Resource(5, &instance::Device, O_RES_R) Device;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10255::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10255::RESID c1) { return (uint16_t) c1 == c2; }
	