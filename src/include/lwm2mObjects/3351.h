#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3351 {
// Custom, overrideable types for Opaque and String resources

    #ifndef deviceName3351
    class deviceNameType : public PreallocString<30> {};
    #endif
    
    #ifndef toolVersion3351
    class toolVersionType : public PreallocString<30> {};
    #endif
    
    #ifndef IMEI3351
    class IMEIType : public PreallocString<30> {};
    #endif
    
    #ifndef IMSI3351
    class IMSIType : public PreallocString<30> {};
    #endif
    
    #ifndef MSISDN3351
    class MSISDNType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3351 - powerupLog
 *  One time event sent by the device at power up.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Human-readable name of the device
    deviceNameType deviceName;
    
    // 1 - The tool version that the device supports - used to determine the logging object/resource version to be used for parsing
    toolVersionType toolVersion;
    
    // 2 - IMEI of device
    IMEIType IMEI;
    
    // 3 - IMSI of device
    IMSIType IMSI;
    
    // 4 - MSISDN of device
    MSISDNType MSISDN;
    
};

enum class RESID {
    deviceName = 0,
    toolVersion = 1,
    IMEI = 2,
    IMSI = 3,
    MSISDN = 4,
    
};

/* \brief Class for object 3351 - powerupLog
 *  One time event sent by the device at power up.
 */
class object : public Lwm2mObject<3351, object, instance> {
public:

    // 0 - Human-readable name of the device
    Resource(0, &instance::deviceName, O_RES_R) deviceName;
    
    // 1 - The tool version that the device supports - used to determine the logging object/resource version to be used for parsing
    Resource(1, &instance::toolVersion, O_RES_R) toolVersion;
    
    // 2 - IMEI of device
    Resource(2, &instance::IMEI, O_RES_R) IMEI;
    
    // 3 - IMSI of device
    Resource(3, &instance::IMSI, O_RES_R) IMSI;
    
    // 4 - MSISDN of device
    Resource(4, &instance::MSISDN, O_RES_R) MSISDN;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3351::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3351::RESID c1) { return (uint16_t) c1 == c2; }
	