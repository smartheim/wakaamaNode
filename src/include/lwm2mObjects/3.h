#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Manufacturer3
    class ManufacturerType : public PreallocString<30> {};
    #endif
    
    #ifndef ModelNumber3
    class ModelNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef SerialNumber3
    class SerialNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef FirmwareVersion3
    class FirmwareVersionType : public PreallocString<30> {};
    #endif
    
    #ifndef CurrentTime3
    class CurrentTimeType : public PreallocString<30> {};
    #endif
    
    #ifndef UTCOffset3
    class UTCOffsetType : public PreallocString<30> {};
    #endif
    
    #ifndef Timezone3
    class TimezoneType : public PreallocString<30> {};
    #endif
    
    #ifndef SupportedBindingandModes3
    class SupportedBindingandModesType : public PreallocString<30> {};
    #endif
    
    #ifndef DeviceType3
    class DeviceTypeType : public PreallocString<30> {};
    #endif
    
    #ifndef HardwareVersion3
    class HardwareVersionType : public PreallocString<30> {};
    #endif
    
    #ifndef SoftwareVersion3
    class SoftwareVersionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3 - Device
 *  This LwM2M Object provides a range of device related information which can be queried
 *  by the LwM2M Server, and a device reboot and factory reset function.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Human readable manufacturer name
    ManufacturerType Manufacturer;
    
    // Optional resource
    // 1 - A model identifier (manufacturer specified string)
    ModelNumberType ModelNumber;
    
    // Optional resource
    // 2 - Serial Number
    SerialNumberType SerialNumber;
    
    // Optional resource
    // 3 - Current firmware version of the Device.The Firmware Management function could rely on this resource.
    FirmwareVersionType FirmwareVersion;
    
    // 4 - Reboot the LwM2M Device to restore the Device from unexpected firmware failure.
    Executable Reboot;

    // Optional resource
    // 5 - Perform factory reset of the LwM2M Device to make the LwM2M Device to go through initial deployment sequence where provisioning and bootstrap sequence is performed. This requires client ensuring post factory reset to have minimal information to allow it to carry out one of the bootstrap methods specified in section 5.2.3. When this Resource is executed, “De-register” operation MAY be sent to the LwM2M Server(s) before factory reset of the LwM2M Device.
    Executable FactoryReset;

    // Optional resource
    // 6 - 0 – DC power1 – Internal Battery2 – External Battery4 – Power over Ethernet5 – USB6 – AC (Mains) power7 – SolarThe same Resource Instance ID MUST be used to associate a given Power Source (Resource ID:6) with its Present Voltage (Resource ID:7) and its Present Current (Resource ID:8)
    int AvailablePowerSources;
    
    // Optional resource
    // 7 - Present voltage for each Available Power Sources Resource Instance.
    int PowerSourceVoltage;
    
    // Optional resource
    // 8 - Present current for each Available Power Source.
    int PowerSourceCurrent;
    
    // Optional resource
    // 9 - Contains the current battery level as a percentage (with a range from 0 to 100). This value is only valid for the Device internal Battery if present (one Available Power Sources Resource Instance is 1).
    int BatteryLevel;
    
    // Optional resource
    // 10 - Estimated current available amount of storage space which can store data and software in the LwM2M Device (expressed in kilobytes).
    int MemoryFree;
    
    // 11 - 0=No error1=Low battery power2=External power supply off3=GPS module failure4=Low received signal strength5=Out of memory6=SMS failure7=IP connectivity failure8=Peripheral malfunctionWhen the single Device Object Instance is initiated, there is only one error code Resource Instance whose value is equal to 0 that means no error. When the first error happens, the LwM2M Client changes error code Resource Instance to any non-zero value to indicate the error type. When any other error happens, a new error code Resource Instance is created.This error code Resource MAY be observed by the LwM2M Server. How to deal with LwM2M Client’s error report depends on the policy of the LwM2M Server.
    int ErrorCode;
    
    // Optional resource
    // 12 - Delete all error code Resource Instances and create only one zero-value error code that implies no error.
    Executable ResetErrorCode;

    // Optional resource
    // 13 - Current UNIX time of the LwM2M Client.The LwM2M Client should be responsible to increase this time value as every second elapses.The LwM2M Server is able to write this Resource to make the LwM2M Client synchronized with the LwM2M Server.
    CurrentTimeType CurrentTime; // Time
    
    // Optional resource
    // 14 - Indicates the UTC offset currently in effect for this LwM2M Device. UTC+X [ISO 8601].
    UTCOffsetType UTCOffset;
    
    // Optional resource
    // 15 - Indicates in which time zone the LwM2M Device is located, in IANA Timezone (TZ) database format.
    TimezoneType Timezone;
    
    // 16 - Indicates which bindings and modes are supported in the LwM2M Client. The possible values of Resource are combination of "U" or "UQ" and "S" or "SQ".
    SupportedBindingandModesType SupportedBindingandModes;
    
    // Optional resource
    // 17 - Type of the device (manufacturer specified string: e.g., smart meters / dev Class…)
    DeviceTypeType DeviceType;
    
    // Optional resource
    // 18 - Current hardware version of the device
    HardwareVersionType HardwareVersion;
    
    // Optional resource
    // 19 - Current software version of the device (manufacturer specified string). On elaborated LwM2M device, SW could be split in 2 parts: a firmware one and a higher level software on top.Both pieces of Software are together managed by LwM2M Firmware Update Object (Object ID 5)
    SoftwareVersionType SoftwareVersion;
    
    // Optional resource
    // 20 - This value is only valid for the Device Internal Battery if present (one Available Power Sources Resource Instance value is 1).BatteryStatus	Meaning	Description0	Normal	The battery is operating normally and not on power.1	Charging	The battery is currently charging.2	Charge Complete	The battery is fully charged and still on power.3	Damaged	The battery has some problem.4	Low Battery	The battery is low on charge.5	Not Installed	The battery is not installed.6	Unknown	The battery information is not available.
    int BatteryStatus;
    
    // Optional resource
    // 21 - Total amount of storage space which can store data and software in the LwM2M Device (expressed in kilobytes).
    int MemoryTotal;
    
    // Optional resource
    // 22 - Reference to external “Device” object instance containing information. For example, such an external device can be a Host Device, which is a device into which the Device containing the LwM2M client is embedded. This Resource may be used to retrieve information about the Host Device.
    // Objlnk resources are not supported yet - ExtDevInfo;
    
};

enum class RESID {
    Manufacturer = 0,
    ModelNumber = 1,
    SerialNumber = 2,
    FirmwareVersion = 3,
    Reboot = 4,
    FactoryReset = 5,
    AvailablePowerSources = 6,
    PowerSourceVoltage = 7,
    PowerSourceCurrent = 8,
    BatteryLevel = 9,
    MemoryFree = 10,
    ErrorCode = 11,
    ResetErrorCode = 12,
    CurrentTime = 13,
    UTCOffset = 14,
    Timezone = 15,
    SupportedBindingandModes = 16,
    DeviceType = 17,
    HardwareVersion = 18,
    SoftwareVersion = 19,
    BatteryStatus = 20,
    MemoryTotal = 21,
    ExtDevInfo = 22,
    
};

/* \brief Class for object 3 - Device
 *  This LwM2M Object provides a range of device related information which can be queried
 *  by the LwM2M Server, and a device reboot and factory reset function.
 */
class object : public Lwm2mObject<3, object, instance> {
public:

    // Optional resource
    // 0 - Human readable manufacturer name
    Resource(0, &instance::Manufacturer, O_RES_R) Manufacturer;
    
    // Optional resource
    // 1 - A model identifier (manufacturer specified string)
    Resource(1, &instance::ModelNumber, O_RES_R) ModelNumber;
    
    // Optional resource
    // 2 - Serial Number
    Resource(2, &instance::SerialNumber, O_RES_R) SerialNumber;
    
    // Optional resource
    // 3 - Current firmware version of the Device.The Firmware Management function could rely on this resource.
    Resource(3, &instance::FirmwareVersion, O_RES_R) FirmwareVersion;
    
    // 4 - Reboot the LwM2M Device to restore the Device from unexpected firmware failure.
    Resource(4, &instance::Reboot) Reboot;
    
    // Optional resource
    // 5 - Perform factory reset of the LwM2M Device to make the LwM2M Device to go through initial deployment sequence where provisioning and bootstrap sequence is performed. This requires client ensuring post factory reset to have minimal information to allow it to carry out one of the bootstrap methods specified in section 5.2.3. When this Resource is executed, “De-register” operation MAY be sent to the LwM2M Server(s) before factory reset of the LwM2M Device.
    Resource(5, &instance::FactoryReset) FactoryReset;
    
    // Optional resource
    // 6 - 0 – DC power1 – Internal Battery2 – External Battery4 – Power over Ethernet5 – USB6 – AC (Mains) power7 – SolarThe same Resource Instance ID MUST be used to associate a given Power Source (Resource ID:6) with its Present Voltage (Resource ID:7) and its Present Current (Resource ID:8)
    Resource(6, &instance::AvailablePowerSources, O_RES_R) AvailablePowerSources;
    
    // Optional resource
    // 7 - Present voltage for each Available Power Sources Resource Instance.
    Resource(7, &instance::PowerSourceVoltage, O_RES_R) PowerSourceVoltage;
    
    // Optional resource
    // 8 - Present current for each Available Power Source.
    Resource(8, &instance::PowerSourceCurrent, O_RES_R) PowerSourceCurrent;
    
    // Optional resource
    // 9 - Contains the current battery level as a percentage (with a range from 0 to 100). This value is only valid for the Device internal Battery if present (one Available Power Sources Resource Instance is 1).
    Resource(9, &instance::BatteryLevel, O_RES_R) BatteryLevel;
    
    // Optional resource
    // 10 - Estimated current available amount of storage space which can store data and software in the LwM2M Device (expressed in kilobytes).
    Resource(10, &instance::MemoryFree, O_RES_R) MemoryFree;
    
    // 11 - 0=No error1=Low battery power2=External power supply off3=GPS module failure4=Low received signal strength5=Out of memory6=SMS failure7=IP connectivity failure8=Peripheral malfunctionWhen the single Device Object Instance is initiated, there is only one error code Resource Instance whose value is equal to 0 that means no error. When the first error happens, the LwM2M Client changes error code Resource Instance to any non-zero value to indicate the error type. When any other error happens, a new error code Resource Instance is created.This error code Resource MAY be observed by the LwM2M Server. How to deal with LwM2M Client’s error report depends on the policy of the LwM2M Server.
    Resource(11, &instance::ErrorCode, O_RES_R) ErrorCode;
    
    // Optional resource
    // 12 - Delete all error code Resource Instances and create only one zero-value error code that implies no error.
    Resource(12, &instance::ResetErrorCode) ResetErrorCode;
    
    // Optional resource
    // 13 - Current UNIX time of the LwM2M Client.The LwM2M Client should be responsible to increase this time value as every second elapses.The LwM2M Server is able to write this Resource to make the LwM2M Client synchronized with the LwM2M Server.
    Resource(13, &instance::CurrentTime, O_RES_RW) CurrentTime;
    
    // Optional resource
    // 14 - Indicates the UTC offset currently in effect for this LwM2M Device. UTC+X [ISO 8601].
    Resource(14, &instance::UTCOffset, O_RES_RW) UTCOffset;
    
    // Optional resource
    // 15 - Indicates in which time zone the LwM2M Device is located, in IANA Timezone (TZ) database format.
    Resource(15, &instance::Timezone, O_RES_RW) Timezone;
    
    // 16 - Indicates which bindings and modes are supported in the LwM2M Client. The possible values of Resource are combination of "U" or "UQ" and "S" or "SQ".
    Resource(16, &instance::SupportedBindingandModes, O_RES_R) SupportedBindingandModes;
    
    // Optional resource
    // 17 - Type of the device (manufacturer specified string: e.g., smart meters / dev Class…)
    Resource(17, &instance::DeviceType, O_RES_R) DeviceType;
    
    // Optional resource
    // 18 - Current hardware version of the device
    Resource(18, &instance::HardwareVersion, O_RES_R) HardwareVersion;
    
    // Optional resource
    // 19 - Current software version of the device (manufacturer specified string). On elaborated LwM2M device, SW could be split in 2 parts: a firmware one and a higher level software on top.Both pieces of Software are together managed by LwM2M Firmware Update Object (Object ID 5)
    Resource(19, &instance::SoftwareVersion, O_RES_R) SoftwareVersion;
    
    // Optional resource
    // 20 - This value is only valid for the Device Internal Battery if present (one Available Power Sources Resource Instance value is 1).BatteryStatus	Meaning	Description0	Normal	The battery is operating normally and not on power.1	Charging	The battery is currently charging.2	Charge Complete	The battery is fully charged and still on power.3	Damaged	The battery has some problem.4	Low Battery	The battery is low on charge.5	Not Installed	The battery is not installed.6	Unknown	The battery information is not available.
    Resource(20, &instance::BatteryStatus, O_RES_R) BatteryStatus;
    
    // Optional resource
    // 21 - Total amount of storage space which can store data and software in the LwM2M Device (expressed in kilobytes).
    Resource(21, &instance::MemoryTotal, O_RES_R) MemoryTotal;
    
    // Optional resource
    // 22 - Reference to external “Device” object instance containing information. For example, such an external device can be a Host Device, which is a device into which the Device containing the LwM2M client is embedded. This Resource may be used to retrieve information about the Host Device.
    // Objlnk resources are not supported yet - ExtDevInfo;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3::RESID c1) { return (uint16_t) c1 == c2; }
	