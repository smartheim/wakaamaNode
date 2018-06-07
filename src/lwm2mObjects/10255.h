#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id10255 {
/* \brief Class for object 10255 - Device Metadata
 *  This object provides a range of information related to device metadata
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Manifest protocol supported
    int Protocolsupported;
    
    // 1 - Hash of the bootloader. This is used for tracking the version of the bootloader used.
    Opaque<30> Bootloaderhash;
    
    // 2 - If the end-user has modified the bootloader the hash of the modified bootloader is recorded here
    Opaque<30> OEMbootloaderhash;
    
    // 3 - Vendor Class UUID
    PreallocString<30> Vendor;
    
    // 4 - Class UUID
    PreallocString<30> Class;
    
    // 5 - Device UUID
    PreallocString<30> Device;
    
    enum class RESID {
        Protocolsupported = 0,
        Bootloaderhash = 1,
        OEMbootloaderhash = 2,
        Vendor = 3,
        Class = 4,
        Device = 5,
        
    };
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
inline bool operator== (id10255::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id10255::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	