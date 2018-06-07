#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id10241 {
/* \brief Class for object 10241 - HostDeviceInfo
 *  This LWM2M Object provides a range of host device related information which can be queried
 *  by the LWM2M Server. The host device is any integrated device with an embedded cellular
 *  radio module.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5905 - Human readable host device manufacturer name
    PreallocString<30> HostDeviceManufacturer;
    
    // 5906 - A host device model identifier (manufacturer specified string)
    PreallocString<30> HostDeviceModelNumber;
    
    // 5907 - The host device unique ID as assigned by an OEM, MNO, or other as the Device ID in the onboarding or manufacturing process.
    PreallocString<30> HostDeviceUniqueID;
    
    // 5908 - Current software version of the host device. (manufacturer specified string).
    PreallocString<30> HostDeviceSoftwareVersion;
    
    enum class RESID {
        HostDeviceManufacturer = 5905,
        HostDeviceModelNumber = 5906,
        HostDeviceUniqueID = 5907,
        HostDeviceSoftwareVersion = 5908,
        
    };
};

/* \brief Class for object 10241 - HostDeviceInfo
 *  This LWM2M Object provides a range of host device related information which can be queried
 *  by the LWM2M Server. The host device is any integrated device with an embedded cellular
 *  radio module.
 */
class object : public Lwm2mObject<10241, object, instance> {
public:

    // 5905 - Human readable host device manufacturer name
    Resource(5905, &instance::HostDeviceManufacturer, O_RES_R) HostDeviceManufacturer;
    
    // 5906 - A host device model identifier (manufacturer specified string)
    Resource(5906, &instance::HostDeviceModelNumber, O_RES_R) HostDeviceModelNumber;
    
    // 5907 - The host device unique ID as assigned by an OEM, MNO, or other as the Device ID in the onboarding or manufacturing process.
    Resource(5907, &instance::HostDeviceUniqueID, O_RES_R) HostDeviceUniqueID;
    
    // 5908 - Current software version of the host device. (manufacturer specified string).
    Resource(5908, &instance::HostDeviceSoftwareVersion, O_RES_R) HostDeviceSoftwareVersion;
    
};

} // end of id namespace
inline bool operator== (id10241::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id10241::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	