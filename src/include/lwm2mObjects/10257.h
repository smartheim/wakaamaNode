#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10257 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Manufacturer10257
    class ManufacturerType : public PreallocString<30> {};
    #endif
    
    #ifndef ModelNumber10257
    class ModelNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef SerialNumber10257
    class SerialNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef Description10257
    class DescriptionType : public PreallocString<30> {};
    #endif
    
    #ifndef CurrentTime10257
    class CurrentTimeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10257 - Heat / Cooling meter
 *  This Object provides the information to represent a generic (district) heat or cooling
 *  meter
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
    // 2 - Serial number of the meter
    SerialNumberType SerialNumber;
    
    // Optional resource
    // 3 - Description of the meter
    DescriptionType Description;
    
    // Optional resource
    // 11 - Error code reported by the meter
    int Errorcode;
    
    // Optional resource
    // 5800 - The current active power
    float Instantaneousactivepower;
    
    // 5802 - The maximum active power measured by the sensor since it is ON
    float MaxMeasuredactivepower;
    
    // Optional resource
    // 5805 - The cumulative active power since the last cumulative energy reset or device start
    float Cumulativeactivepower;
    
    // Optional resource
    // 12 - Flow temperature
    float Flowtemperature;
    
    // Optional resource
    // 13 - The maximum flow temperature measured by the meter
    float MaxMeasuredflowtemperature;
    
    // Optional resource
    // 14 - Return temperature
    float Returntemperature;
    
    // Optional resource
    // 15 - The maximum return temperature measured by the meter 
    float MaxMeasuredreturntemperature;
    
    // Optional resource
    // 16 - Temperature difference
    float Temperaturedifference;
    
    // Optional resource
    // 17 - The flow rate
    float Flowrate;
    
    // Optional resource
    // 18 - The maximum flow measured by the meter 
    float MaxMeasuredflow;
    
    // Optional resource
    // 20 - The cumulative flow volume measured on the flow pipe
    float Flowvolume;
    
    // Optional resource
    // 21 - The cumulative flow volume measured on the return pipe
    float Returnvolume;
    
    // Optional resource
    // 5506 - Unix Time. A signed integer representing the number of seconds since Jan 1st, 1970 in the UTC time zone.
    CurrentTimeType CurrentTime; // Time
    
};

enum class RESID {
    Manufacturer = 0,
    ModelNumber = 1,
    SerialNumber = 2,
    Description = 3,
    Errorcode = 11,
    Instantaneousactivepower = 5800,
    MaxMeasuredactivepower = 5802,
    Cumulativeactivepower = 5805,
    Flowtemperature = 12,
    MaxMeasuredflowtemperature = 13,
    Returntemperature = 14,
    MaxMeasuredreturntemperature = 15,
    Temperaturedifference = 16,
    Flowrate = 17,
    MaxMeasuredflow = 18,
    Flowvolume = 20,
    Returnvolume = 21,
    CurrentTime = 5506,
    
};

/* \brief Class for object 10257 - Heat / Cooling meter
 *  This Object provides the information to represent a generic (district) heat or cooling
 *  meter
 */
class object : public Lwm2mObject<10257, object, instance> {
public:

    // Optional resource
    // 0 - Human readable manufacturer name
    Resource(0, &instance::Manufacturer, O_RES_R) Manufacturer;
    
    // Optional resource
    // 1 - A model identifier (manufacturer specified string)
    Resource(1, &instance::ModelNumber, O_RES_R) ModelNumber;
    
    // Optional resource
    // 2 - Serial number of the meter
    Resource(2, &instance::SerialNumber, O_RES_R) SerialNumber;
    
    // Optional resource
    // 3 - Description of the meter
    Resource(3, &instance::Description, O_RES_R) Description;
    
    // Optional resource
    // 11 - Error code reported by the meter
    Resource(11, &instance::Errorcode, O_RES_R) Errorcode;
    
    // Optional resource
    // 5800 - The current active power
    Resource(5800, &instance::Instantaneousactivepower, O_RES_R) Instantaneousactivepower;
    
    // 5802 - The maximum active power measured by the sensor since it is ON
    Resource(5802, &instance::MaxMeasuredactivepower, O_RES_R) MaxMeasuredactivepower;
    
    // Optional resource
    // 5805 - The cumulative active power since the last cumulative energy reset or device start
    Resource(5805, &instance::Cumulativeactivepower, O_RES_R) Cumulativeactivepower;
    
    // Optional resource
    // 12 - Flow temperature
    Resource(12, &instance::Flowtemperature, O_RES_R) Flowtemperature;
    
    // Optional resource
    // 13 - The maximum flow temperature measured by the meter
    Resource(13, &instance::MaxMeasuredflowtemperature, O_RES_R) MaxMeasuredflowtemperature;
    
    // Optional resource
    // 14 - Return temperature
    Resource(14, &instance::Returntemperature, O_RES_R) Returntemperature;
    
    // Optional resource
    // 15 - The maximum return temperature measured by the meter 
    Resource(15, &instance::MaxMeasuredreturntemperature, O_RES_R) MaxMeasuredreturntemperature;
    
    // Optional resource
    // 16 - Temperature difference
    Resource(16, &instance::Temperaturedifference, O_RES_R) Temperaturedifference;
    
    // Optional resource
    // 17 - The flow rate
    Resource(17, &instance::Flowrate, O_RES_R) Flowrate;
    
    // Optional resource
    // 18 - The maximum flow measured by the meter 
    Resource(18, &instance::MaxMeasuredflow, O_RES_R) MaxMeasuredflow;
    
    // Optional resource
    // 20 - The cumulative flow volume measured on the flow pipe
    Resource(20, &instance::Flowvolume, O_RES_R) Flowvolume;
    
    // Optional resource
    // 21 - The cumulative flow volume measured on the return pipe
    Resource(21, &instance::Returnvolume, O_RES_R) Returnvolume;
    
    // Optional resource
    // 5506 - Unix Time. A signed integer representing the number of seconds since Jan 1st, 1970 in the UTC time zone.
    Resource(5506, &instance::CurrentTime, O_RES_RW) CurrentTime;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10257::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10257::RESID c1) { return (uint16_t) c1 == c2; }
	