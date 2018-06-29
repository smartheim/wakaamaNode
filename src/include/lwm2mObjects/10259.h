#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10259 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Name10259
    class NameType : public PreallocString<30> {};
    #endif
    
    #ifndef ReadAll10259
    class ReadAllType : public PreallocString<30> {};
    #endif
    
    #ifndef Read10259
    class ReadType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10259 - System Log
 *  This object provides read access to log buffers as well as limited configuration of
 *  logging services.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Short name describing the log source represented by this particular instance.For syslog-compatible log sources this value should be "syslog". If multiple syslog-compatible log sources exist on a device then each should be given a distinct name that is then prefixed with "syslog-".
    NameType Name;
    
    // 1 - Read the entire current contents of the log buffer.Result is delivered as a display-formatted UTF-8 string, with each message entry on a new line.
    ReadAllType ReadAll;
    
    // Optional resource
    // 2 - Similar to Read All, but only reads log entries that have arrived since the last time this log buffer was read.If the LwM2M client is connected to multiple servers then the last read position should be tracked separately for each server.If this is the first attempt to read the log for a given connection then this resource behaves the same as Read All.
    ReadType Read;
    
    // Optional resource
    // 3 - Enable or disable log capture for this source.If this resource is not provided by an implementation, then the existence of a System Log instance is taken as implicit confirmation that the log source it represents is currently enabled.
    bool Enabled;
    
    // Optional resource
    // 4 - For log sources that support message priorities, this resource configures the minimum priority to capture.For syslog-compatible log sources the following enumeration must be used: 1 = Emergency, 2 = Alert, 3 = Critical, 4 = Error, 5 = Warning, 6 = Notice, 7 = Info, 8 = Debug.For other log sources this is left up to the implementer, with the requirement that consecutive values are used, starting at 1 and sorted so that message verbosity increases as the number ascends.
    int CaptureLevel;
    
};

enum class RESID {
    Name = 0,
    ReadAll = 1,
    Read = 2,
    Enabled = 3,
    CaptureLevel = 4,
    
};

/* \brief Class for object 10259 - System Log
 *  This object provides read access to log buffers as well as limited configuration of
 *  logging services.
 */
class object : public Lwm2mObject<10259, object, instance> {
public:

    // 0 - Short name describing the log source represented by this particular instance.For syslog-compatible log sources this value should be "syslog". If multiple syslog-compatible log sources exist on a device then each should be given a distinct name that is then prefixed with "syslog-".
    Resource(0, &instance::Name, O_RES_R) Name;
    
    // 1 - Read the entire current contents of the log buffer.Result is delivered as a display-formatted UTF-8 string, with each message entry on a new line.
    Resource(1, &instance::ReadAll, O_RES_R) ReadAll;
    
    // Optional resource
    // 2 - Similar to Read All, but only reads log entries that have arrived since the last time this log buffer was read.If the LwM2M client is connected to multiple servers then the last read position should be tracked separately for each server.If this is the first attempt to read the log for a given connection then this resource behaves the same as Read All.
    Resource(2, &instance::Read, O_RES_R) Read;
    
    // Optional resource
    // 3 - Enable or disable log capture for this source.If this resource is not provided by an implementation, then the existence of a System Log instance is taken as implicit confirmation that the log source it represents is currently enabled.
    Resource(3, &instance::Enabled, O_RES_RW) Enabled;
    
    // Optional resource
    // 4 - For log sources that support message priorities, this resource configures the minimum priority to capture.For syslog-compatible log sources the following enumeration must be used: 1 = Emergency, 2 = Alert, 3 = Critical, 4 = Error, 5 = Warning, 6 = Notice, 7 = Info, 8 = Debug.For other log sources this is left up to the implementer, with the requirement that consecutive values are used, starting at 1 and sorted so that message verbosity increases as the number ascends.
    Resource(4, &instance::CaptureLevel, O_RES_RW) CaptureLevel;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10259::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10259::RESID c1) { return (uint16_t) c1 == c2; }
	