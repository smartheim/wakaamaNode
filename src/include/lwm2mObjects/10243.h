#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10243 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Manufacturer10243
    class ManufacturerType : public PreallocString<30> {};
    #endif
    
    #ifndef ModelNumber10243
    class ModelNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef SerialNumber10243
    class SerialNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef Description10243
    class DescriptionType : public PreallocString<30> {};
    #endif
    
    #ifndef Tension10243
    class TensionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10243 - Single-Phase Power Meter
 *  This Object provides the information to represent a generic Single-Phase Power Meter.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 -                 Human readable manufacturer name            
    ManufacturerType Manufacturer;
    
    // Optional resource
    // 1 -                 A model identifier (manufacturer specified string)            
    ModelNumberType ModelNumber;
    
    // Optional resource
    // 2 -                 Serial number of the meter            
    SerialNumberType SerialNumber;
    
    // Optional resource
    // 3 -                 Description of the meter            
    DescriptionType Description;
    
    // 4 -                 Voltage            
    TensionType Tension;
    
    // 5 -                 Current            
    float Current;
    
    // Optional resource
    // 6 -                 Active Power            
    float ActivePower;
    
    // Optional resource
    // 7 -                 Reactive Power            
    float ReactivePower;
    
    // Optional resource
    // 8 -                 Inductive Reactive Power            
    float InductiveReactivePower;
    
    // Optional resource
    // 9 -                 Capacitive Reactive Power            
    float CapacitiveReactivePower;
    
    // Optional resource
    // 10 -                 Apparent Power            
    float ApparentPower;
    
    // Optional resource
    // 11 -                 Power Factor            
    float PowerFactor;
    
    // Optional resource
    // 12 -                 Total Harmonic Distortion (Tension)            
    float THDV;
    
    // Optional resource
    // 13 -                 Total Harmonic Distortion (Current)            
    float THDA;
    
    // Optional resource
    // 14 -                 Active Energy            
    float ActiveEnergy;
    
    // Optional resource
    // 15 -                 Reactive Energy            
    float ReactiveEnergy;
    
    // Optional resource
    // 16 -                 Apparent Energy            
    float ApparentEnergy;
    
    // Optional resource
    // 17 -                 Frequency            
    float Frequency;
    
};

enum class RESID {
    Manufacturer = 0,
    ModelNumber = 1,
    SerialNumber = 2,
    Description = 3,
    Tension = 4,
    Current = 5,
    ActivePower = 6,
    ReactivePower = 7,
    InductiveReactivePower = 8,
    CapacitiveReactivePower = 9,
    ApparentPower = 10,
    PowerFactor = 11,
    THDV = 12,
    THDA = 13,
    ActiveEnergy = 14,
    ReactiveEnergy = 15,
    ApparentEnergy = 16,
    Frequency = 17,
    
};

/* \brief Class for object 10243 - Single-Phase Power Meter
 *  This Object provides the information to represent a generic Single-Phase Power Meter.
 */
class object : public Lwm2mObject<10243, object, instance> {
public:

    // Optional resource
    // 0 -                 Human readable manufacturer name            
    Resource(0, &instance::Manufacturer, O_RES_R) Manufacturer;
    
    // Optional resource
    // 1 -                 A model identifier (manufacturer specified string)            
    Resource(1, &instance::ModelNumber, O_RES_R) ModelNumber;
    
    // Optional resource
    // 2 -                 Serial number of the meter            
    Resource(2, &instance::SerialNumber, O_RES_R) SerialNumber;
    
    // Optional resource
    // 3 -                 Description of the meter            
    Resource(3, &instance::Description, O_RES_R) Description;
    
    // 4 -                 Voltage            
    Resource(4, &instance::Tension, O_RES_R) Tension;
    
    // 5 -                 Current            
    Resource(5, &instance::Current, O_RES_R) Current;
    
    // Optional resource
    // 6 -                 Active Power            
    Resource(6, &instance::ActivePower, O_RES_R) ActivePower;
    
    // Optional resource
    // 7 -                 Reactive Power            
    Resource(7, &instance::ReactivePower, O_RES_R) ReactivePower;
    
    // Optional resource
    // 8 -                 Inductive Reactive Power            
    Resource(8, &instance::InductiveReactivePower, O_RES_R) InductiveReactivePower;
    
    // Optional resource
    // 9 -                 Capacitive Reactive Power            
    Resource(9, &instance::CapacitiveReactivePower, O_RES_R) CapacitiveReactivePower;
    
    // Optional resource
    // 10 -                 Apparent Power            
    Resource(10, &instance::ApparentPower, O_RES_R) ApparentPower;
    
    // Optional resource
    // 11 -                 Power Factor            
    Resource(11, &instance::PowerFactor, O_RES_R) PowerFactor;
    
    // Optional resource
    // 12 -                 Total Harmonic Distortion (Tension)            
    Resource(12, &instance::THDV, O_RES_R) THDV;
    
    // Optional resource
    // 13 -                 Total Harmonic Distortion (Current)            
    Resource(13, &instance::THDA, O_RES_R) THDA;
    
    // Optional resource
    // 14 -                 Active Energy            
    Resource(14, &instance::ActiveEnergy, O_RES_R) ActiveEnergy;
    
    // Optional resource
    // 15 -                 Reactive Energy            
    Resource(15, &instance::ReactiveEnergy, O_RES_R) ReactiveEnergy;
    
    // Optional resource
    // 16 -                 Apparent Energy            
    Resource(16, &instance::ApparentEnergy, O_RES_R) ApparentEnergy;
    
    // Optional resource
    // 17 -                 Frequency            
    Resource(17, &instance::Frequency, O_RES_R) Frequency;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10243::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10243::RESID c1) { return (uint16_t) c1 == c2; }
	