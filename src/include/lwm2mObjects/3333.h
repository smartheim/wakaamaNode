#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3333 {
// Custom, overrideable types for Opaque and String resources

    #ifndef CurrentTime3333
    class CurrentTimeType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3333
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3333 - Time
 *  This IPSO object is used to report the current time in seconds since January 1, 1970 UTC.
 *  There is also a fractional time counter that has a range of less than one second.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5506 - Unix Time. A signed integer representing the number of seconds since Jan 1st, 1970 in the UTC time zone.
    CurrentTimeType CurrentTime; // Time
    
    // Optional resource
    // 5507 - For shorter times of a fraction of a second (i.e. 0.23).
    float FractionalTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    CurrentTime = 5506,
    FractionalTime = 5507,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3333 - Time
 *  This IPSO object is used to report the current time in seconds since January 1, 1970 UTC.
 *  There is also a fractional time counter that has a range of less than one second.
 */
class object : public Lwm2mObject<3333, object, instance> {
public:

    // 5506 - Unix Time. A signed integer representing the number of seconds since Jan 1st, 1970 in the UTC time zone.
    Resource(5506, &instance::CurrentTime, O_RES_RW) CurrentTime;
    
    // Optional resource
    // 5507 - For shorter times of a fraction of a second (i.e. 0.23).
    Resource(5507, &instance::FractionalTime, O_RES_RW) FractionalTime;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3333::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3333::RESID c1) { return (uint16_t) c1 == c2; }
	