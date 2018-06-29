#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3336 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Latitude3336
    class LatitudeType : public PreallocString<30> {};
    #endif
    
    #ifndef Longitude3336
    class LongitudeType : public PreallocString<30> {};
    #endif
    
    #ifndef Uncertainty3336
    class UncertaintyType : public PreallocString<30> {};
    #endif
    
    #ifndef Velocity3336
    class VelocityType : public Opaque<30> {};
    #endif
    
    #ifndef Timestamp3336
    class TimestampType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3336
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3336 - Location
 *  This IPSO object represents GPS coordinates. This object is compatible with the LWM2M
 *  management object for location, but uses reusable resources.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5514 - The decimal notation of latitude, e.g. -43.5723 (World Geodetic System 1984).
    LatitudeType Latitude;
    
    // 5515 - The decimal notation of longitude, e.g. 153.21760 (World Geodetic System 1984).
    LongitudeType Longitude;
    
    // Optional resource
    // 5516 - The accuracy of the position in meters.
    UncertaintyType Uncertainty;
    
    // Optional resource
    // 5705 - Measured Direction.
    float CompassDirection;
    
    // Optional resource
    // 5517 - The velocity of the device as defined in 3GPP 23.032 GAD specification. This set of values may not be available if the device is static.
    VelocityType Velocity;
    
    // Optional resource
    // 5518 - The timestamp of when the location measurement was performed.
    TimestampType Timestamp; // Time
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Latitude = 5514,
    Longitude = 5515,
    Uncertainty = 5516,
    CompassDirection = 5705,
    Velocity = 5517,
    Timestamp = 5518,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3336 - Location
 *  This IPSO object represents GPS coordinates. This object is compatible with the LWM2M
 *  management object for location, but uses reusable resources.
 */
class object : public Lwm2mObject<3336, object, instance> {
public:

    // 5514 - The decimal notation of latitude, e.g. -43.5723 (World Geodetic System 1984).
    Resource(5514, &instance::Latitude, O_RES_R) Latitude;
    
    // 5515 - The decimal notation of longitude, e.g. 153.21760 (World Geodetic System 1984).
    Resource(5515, &instance::Longitude, O_RES_R) Longitude;
    
    // Optional resource
    // 5516 - The accuracy of the position in meters.
    Resource(5516, &instance::Uncertainty, O_RES_R) Uncertainty;
    
    // Optional resource
    // 5705 - Measured Direction.
    Resource(5705, &instance::CompassDirection, O_RES_R) CompassDirection;
    
    // Optional resource
    // 5517 - The velocity of the device as defined in 3GPP 23.032 GAD specification. This set of values may not be available if the device is static.
    Resource(5517, &instance::Velocity, O_RES_R) Velocity;
    
    // Optional resource
    // 5518 - The timestamp of when the location measurement was performed.
    Resource(5518, &instance::Timestamp, O_RES_R) Timestamp;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3336::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3336::RESID c1) { return (uint16_t) c1 == c2; }
	