#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10265 {
// Custom, overrideable types for Opaque and String resources

    #ifndef SampleUTCOffset10265
    class SampleUTCOffsetType : public PreallocString<30> {};
    #endif
    
    #ifndef FirmwareVersion10265
    class FirmwareVersionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10265 - Leakage Detection Configuration
 *  The leakage detection configuration object provides a means for configuring the timing
 *  and sampling frequency of a vibration based network leak detector
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Sample Times is a readable and writable multi value resource used to control when leak detection vibration sampling should occur. This is an integer value representing seconds since midnight
    int SampleTimes;
    
    // Optional resource
    // 1 - The Sample UTC Offset resource is a readable and writable resource representing the time zone offset for this Leakage Detection Schedule instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided.
    SampleUTCOffsetType SampleUTCOffset;
    
    // 2 - Detection Mode is a readable and writeable resource used to indicate which mode to run the leak detection sensor. Values are one of:-0. Disabled1. Alarm Only (default)2. Top Frequency Values3. All Frequency ValuesDisabled (0)  the leak detection function should be disabled.Alarm Only (1)  for this mode no detailed frequency data is provided to the LwM2M server and an alarm is raised if the Leakage Detection Daughter board indicates that leak was detected. Top Frequency Values (2)  for this mode, only the top (Top Frequency Count) values will be delivered to the LwM2M server via the Frequency Value ResourceAll Frequency Values(3)  for this mode, all frequency values for all frequency bands will be provided to the LwM2M server via the Frequency Value Resource
    int DetectionMode;
    
    // Optional resource
    // 3 - Top Frequency Count is a readable and writeable resource used represent the number of samples to provide if the Detection Mode is set to Mode 2 (Top Frequency Values). If not provided, this value should default to 3
    int TopFrequencyCount;
    
    // Optional resource
    // 4 - Frequency Thresholds is a multiple value readable and writeable resource used to represent upper bound thresholds for each of the frequency bands configured on the daughter board. Being a multiple value resource, this resource only needs to contain the values that are required to override the default values provided by the daughter board firmware.  As an example if the frequency threshold for band 7 and band 52 needs to be overridden, then this resource should just contain those two values:-/TBD/0/4/7 = 123/TBD/0/4/52 = 345
    int FrequencyThresholds;
    
    // Optional resource
    // 5 - Frequency Values is a multiple value readonly resource used represent the latest frequency values recorded by the daughter board. In Detection Mode 2 (Top Frequency Values) only the number of values configured in Top Frequency Count will be provided. As an example, if the Top Frequency Count is 3 and the top three frequency threshold deviations were on band 8, 44 and 101, this resource would present:-/TBD/0/5/8 = 434/TBD/0/5/44 = 39/TBD/0/5/101 = 349In Detection Mode 3, this resource would present all frequency readings from 1 through to the number of bands measured by the board.This resource can either be observed by the LwM2M server (and subsequently notified by the Client daily) or Read adhoc from the LwM2M server.
    int FrequencyValues;
    
    // 7 - Firmware Version is a readonly resource representing the current firmware version of the Daughter Board.
    FirmwareVersionType FirmwareVersion;
    
};

enum class RESID {
    SampleTimes = 0,
    SampleUTCOffset = 1,
    DetectionMode = 2,
    TopFrequencyCount = 3,
    FrequencyThresholds = 4,
    FrequencyValues = 5,
    FirmwareVersion = 7,
    
};

/* \brief Class for object 10265 - Leakage Detection Configuration
 *  The leakage detection configuration object provides a means for configuring the timing
 *  and sampling frequency of a vibration based network leak detector
 */
class object : public Lwm2mObject<10265, object, instance> {
public:

    // 0 - Sample Times is a readable and writable multi value resource used to control when leak detection vibration sampling should occur. This is an integer value representing seconds since midnight
    Resource(0, &instance::SampleTimes, O_RES_RW) SampleTimes;
    
    // Optional resource
    // 1 - The Sample UTC Offset resource is a readable and writable resource representing the time zone offset for this Leakage Detection Schedule instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided.
    Resource(1, &instance::SampleUTCOffset, O_RES_RW) SampleUTCOffset;
    
    // 2 - Detection Mode is a readable and writeable resource used to indicate which mode to run the leak detection sensor. Values are one of:-0. Disabled1. Alarm Only (default)2. Top Frequency Values3. All Frequency ValuesDisabled (0)  the leak detection function should be disabled.Alarm Only (1)  for this mode no detailed frequency data is provided to the LwM2M server and an alarm is raised if the Leakage Detection Daughter board indicates that leak was detected. Top Frequency Values (2)  for this mode, only the top (Top Frequency Count) values will be delivered to the LwM2M server via the Frequency Value ResourceAll Frequency Values(3)  for this mode, all frequency values for all frequency bands will be provided to the LwM2M server via the Frequency Value Resource
    Resource(2, &instance::DetectionMode, O_RES_RW) DetectionMode;
    
    // Optional resource
    // 3 - Top Frequency Count is a readable and writeable resource used represent the number of samples to provide if the Detection Mode is set to Mode 2 (Top Frequency Values). If not provided, this value should default to 3
    Resource(3, &instance::TopFrequencyCount, O_RES_RW) TopFrequencyCount;
    
    // Optional resource
    // 4 - Frequency Thresholds is a multiple value readable and writeable resource used to represent upper bound thresholds for each of the frequency bands configured on the daughter board. Being a multiple value resource, this resource only needs to contain the values that are required to override the default values provided by the daughter board firmware.  As an example if the frequency threshold for band 7 and band 52 needs to be overridden, then this resource should just contain those two values:-/TBD/0/4/7 = 123/TBD/0/4/52 = 345
    Resource(4, &instance::FrequencyThresholds, O_RES_RW) FrequencyThresholds;
    
    // Optional resource
    // 5 - Frequency Values is a multiple value readonly resource used represent the latest frequency values recorded by the daughter board. In Detection Mode 2 (Top Frequency Values) only the number of values configured in Top Frequency Count will be provided. As an example, if the Top Frequency Count is 3 and the top three frequency threshold deviations were on band 8, 44 and 101, this resource would present:-/TBD/0/5/8 = 434/TBD/0/5/44 = 39/TBD/0/5/101 = 349In Detection Mode 3, this resource would present all frequency readings from 1 through to the number of bands measured by the board.This resource can either be observed by the LwM2M server (and subsequently notified by the Client daily) or Read adhoc from the LwM2M server.
    Resource(5, &instance::FrequencyValues, O_RES_R) FrequencyValues;
    
    // 7 - Firmware Version is a readonly resource representing the current firmware version of the Daughter Board.
    Resource(7, &instance::FirmwareVersion, O_RES_R) FirmwareVersion;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10265::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10265::RESID c1) { return (uint16_t) c1 == c2; }
	