#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id6 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Velocity6
    class VelocityType : public Opaque<30> {};
    #endif
    
    #ifndef Timestamp6
    class TimestampType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 6 - Location
 *  This LwM2M Objects provide a range of device related information which can be queried
 *  by the LwM2M Server, and a device reboot and factory reset function.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The decimal notation of latitude, e.g., -43.5723 [World Geodetic System 1984].
    float Latitude;
    
    // 1 - The decimal notation of longitude, e.g., 153.21760 [World Geodetic System 1984].
    float Longitude;
    
    // Optional resource
    // 2 - The decimal notation of altitude in meters above sea level.
    float Altitude;
    
    // Optional resource
    // 3 - The value in the Radius Resource indicates the size in meters of a circular area around a point of geometry.
    float Radius;
    
    // Optional resource
    // 4 - The velocity in the LwM2M Client is defined in [3GPP-TS_23.032].
    VelocityType Velocity;
    
    // 5 - The timestamp of when the location measurement was performed.
    TimestampType Timestamp; // Time
    
    // Optional resource
    // 6 - Speed is the time rate of change in position of a LwM2M Client without regard for direction: the scalar component of velocity.
    float Speed;
    
};

enum class RESID {
    Latitude = 0,
    Longitude = 1,
    Altitude = 2,
    Radius = 3,
    Velocity = 4,
    Timestamp = 5,
    Speed = 6,
    
};

/* \brief Class for object 6 - Location
 *  This LwM2M Objects provide a range of device related information which can be queried
 *  by the LwM2M Server, and a device reboot and factory reset function.
 */
class object : public Lwm2mObject<6, object, instance> {
public:

    // 0 - The decimal notation of latitude, e.g., -43.5723 [World Geodetic System 1984].
    Resource(0, &instance::Latitude, O_RES_R) Latitude;
    
    // 1 - The decimal notation of longitude, e.g., 153.21760 [World Geodetic System 1984].
    Resource(1, &instance::Longitude, O_RES_R) Longitude;
    
    // Optional resource
    // 2 - The decimal notation of altitude in meters above sea level.
    Resource(2, &instance::Altitude, O_RES_R) Altitude;
    
    // Optional resource
    // 3 - The value in the Radius Resource indicates the size in meters of a circular area around a point of geometry.
    Resource(3, &instance::Radius, O_RES_R) Radius;
    
    // Optional resource
    // 4 - The velocity in the LwM2M Client is defined in [3GPP-TS_23.032].
    Resource(4, &instance::Velocity, O_RES_R) Velocity;
    
    // 5 - The timestamp of when the location measurement was performed.
    Resource(5, &instance::Timestamp, O_RES_R) Timestamp;
    
    // Optional resource
    // 6 - Speed is the time rate of change in position of a LwM2M Client without regard for direction: the scalar component of velocity.
    Resource(6, &instance::Speed, O_RES_R) Speed;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id6::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id6::RESID c1) { return (uint16_t) c1 == c2; }
	