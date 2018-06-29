#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10242 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Manufacturer10242
    class ManufacturerType : public PreallocString<30> {};
    #endif
    
    #ifndef ModelNumber10242
    class ModelNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef SerialNumber10242
    class SerialNumberType : public PreallocString<30> {};
    #endif
    
    #ifndef Description10242
    class DescriptionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10242 - 3-Phase Power Meter
 *  This Object provides the information to represent a generic 3-Phase Power Meter.
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
    
    // 4 -                 Voltage phase 1 (phase to neutral)            
    float TensionR;
    
    // 5 -                 Current phase 1            
    float CurrentR;
    
    // Optional resource
    // 6 -                 Active Power phase 1            
    float ActivePowerR;
    
    // Optional resource
    // 7 -                 Reactive Power phase 1            
    float ReactivePowerR;
    
    // Optional resource
    // 8 -                 Inductive Reactive Power phase 1            
    float InductiveReactivePowerR;
    
    // Optional resource
    // 9 -                 Capacitive Reactive Power phase 1            
    float CapacitiveReactivePowerR;
    
    // Optional resource
    // 10 -                 Apparent Power phase 1            
    float ApparentPowerR;
    
    // Optional resource
    // 11 -                 Power Factor phase 1            
    float PowerFactorR;
    
    // Optional resource
    // 12 -                 Total Harmonic Distortion phase 1 (Tension)            
    float THDVR;
    
    // Optional resource
    // 13 -                 Total Harmonig Distortion phase 1 (Current)            
    float THDAR;
    
    // 14 -                 Voltage phase 2 (phase to neutral)            
    float TensionS;
    
    // 15 -                 Current phase 2            
    float CurrentS;
    
    // Optional resource
    // 16 -                 Active Power phase 2            
    float ActivePowerS;
    
    // Optional resource
    // 17 -                 Reactive Power phase 2            
    float ReactivePowerS;
    
    // Optional resource
    // 18 -                 Inductive Reactive Power phase 2            
    float InductiveReactivePowerS;
    
    // Optional resource
    // 19 -                 Capacitive Reactive Power phase 2            
    float CapacitiveReactivePowerS;
    
    // Optional resource
    // 20 -                 Apparent Power phase 2            
    float ApparentPowerS;
    
    // Optional resource
    // 21 -                 Power Factor phase 2            
    float PowerFactorS;
    
    // Optional resource
    // 22 -                 Total Harmonic Distortion phase 2 (Tension)            
    float THDVS;
    
    // Optional resource
    // 23 -                 Total Harmonic Distortion phase 2 (Current)            
    float THDAS;
    
    // 24 -                 Voltage phase 3 (phase to neutral)            
    float TensionT;
    
    // 25 -                 Current phase 3            
    float CurrentT;
    
    // Optional resource
    // 26 -                 Active Power phase 3            
    float ActivePowerT;
    
    // Optional resource
    // 27 -                 Reactive Power phase 3            
    float ReactivePowerT;
    
    // Optional resource
    // 28 -                 Inductive Reactive Power phase 3            
    float InductiveReactivePowerT;
    
    // Optional resource
    // 29 -                 Capacitive Reactive Power phase 3            
    float CapacitiveReactivePowerT;
    
    // Optional resource
    // 30 -                 Apparent Power phase 3            
    float ApparentPowerT;
    
    // Optional resource
    // 31 -                 Power Factor phase 3            
    float PowerFactorT;
    
    // Optional resource
    // 32 -                 Total Harmonic Distortion phase 3 (Tension)            
    float THDVT;
    
    // Optional resource
    // 33 -                 Total Harmonic Distortion phase 3 (Current)            
    float THDAT;
    
    // Optional resource
    // 34 -                 3-Phase Active Power            
    float ThreePhaseActivePower;
    
    // Optional resource
    // 35 -                 3-Phase Reactive Power            
    float ThreePhaseReactivePower;
    
    // Optional resource
    // 36 -                 3-Phase Inductive Reactive Power            
    float ThreePhaseInductiveReactivePower;
    
    // Optional resource
    // 37 -                 3-Phase Capacitive Reactive Power            
    float ThreePhaseCapacitiveReactivePower;
    
    // Optional resource
    // 38 -                 3-Phase Apparent Power            
    float ThreePhaseApparentPower;
    
    // Optional resource
    // 39 -                 3-Phase Power Factor            
    float ThreePhasePowerFactor;
    
    // Optional resource
    // 40 -                 3-Phase phi cosine            
    float ThreePhasephicosine;
    
    // Optional resource
    // 41 -                 Active Energy            
    float ActiveEnergy;
    
    // Optional resource
    // 42 -                 Reactive Energy            
    float ReactiveEnergy;
    
    // Optional resource
    // 43 -                 Inductive Reactive Energy            
    float InductiveReactiveEnergy;
    
    // Optional resource
    // 44 -                 Capacitive Reactive Energy            
    float CapacitiveReactiveEnergy;
    
    // Optional resource
    // 45 -                 Apparent Energy            
    float ApparentEnergy;
    
    // Optional resource
    // 46 -                 Voltage phase 1 to phase 2            
    float TensionRS;
    
    // Optional resource
    // 47 -                 Voltage phase 2 to phase 3            
    float TensionST;
    
    // Optional resource
    // 48 -                 Voltage phase 3 to phase 1            
    float TensionTR;
    
    // Optional resource
    // 49 -                 Frequency            
    float Frequency;
    
    // Optional resource
    // 50 -                 Neutral Current            
    float NeutralCurrent;
    
};

enum class RESID {
    Manufacturer = 0,
    ModelNumber = 1,
    SerialNumber = 2,
    Description = 3,
    TensionR = 4,
    CurrentR = 5,
    ActivePowerR = 6,
    ReactivePowerR = 7,
    InductiveReactivePowerR = 8,
    CapacitiveReactivePowerR = 9,
    ApparentPowerR = 10,
    PowerFactorR = 11,
    THDVR = 12,
    THDAR = 13,
    TensionS = 14,
    CurrentS = 15,
    ActivePowerS = 16,
    ReactivePowerS = 17,
    InductiveReactivePowerS = 18,
    CapacitiveReactivePowerS = 19,
    ApparentPowerS = 20,
    PowerFactorS = 21,
    THDVS = 22,
    THDAS = 23,
    TensionT = 24,
    CurrentT = 25,
    ActivePowerT = 26,
    ReactivePowerT = 27,
    InductiveReactivePowerT = 28,
    CapacitiveReactivePowerT = 29,
    ApparentPowerT = 30,
    PowerFactorT = 31,
    THDVT = 32,
    THDAT = 33,
    ThreePhaseActivePower = 34,
    ThreePhaseReactivePower = 35,
    ThreePhaseInductiveReactivePower = 36,
    ThreePhaseCapacitiveReactivePower = 37,
    ThreePhaseApparentPower = 38,
    ThreePhasePowerFactor = 39,
    ThreePhasephicosine = 40,
    ActiveEnergy = 41,
    ReactiveEnergy = 42,
    InductiveReactiveEnergy = 43,
    CapacitiveReactiveEnergy = 44,
    ApparentEnergy = 45,
    TensionRS = 46,
    TensionST = 47,
    TensionTR = 48,
    Frequency = 49,
    NeutralCurrent = 50,
    
};

/* \brief Class for object 10242 - 3-Phase Power Meter
 *  This Object provides the information to represent a generic 3-Phase Power Meter.
 */
class object : public Lwm2mObject<10242, object, instance> {
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
    
    // 4 -                 Voltage phase 1 (phase to neutral)            
    Resource(4, &instance::TensionR, O_RES_R) TensionR;
    
    // 5 -                 Current phase 1            
    Resource(5, &instance::CurrentR, O_RES_R) CurrentR;
    
    // Optional resource
    // 6 -                 Active Power phase 1            
    Resource(6, &instance::ActivePowerR, O_RES_R) ActivePowerR;
    
    // Optional resource
    // 7 -                 Reactive Power phase 1            
    Resource(7, &instance::ReactivePowerR, O_RES_R) ReactivePowerR;
    
    // Optional resource
    // 8 -                 Inductive Reactive Power phase 1            
    Resource(8, &instance::InductiveReactivePowerR, O_RES_R) InductiveReactivePowerR;
    
    // Optional resource
    // 9 -                 Capacitive Reactive Power phase 1            
    Resource(9, &instance::CapacitiveReactivePowerR, O_RES_R) CapacitiveReactivePowerR;
    
    // Optional resource
    // 10 -                 Apparent Power phase 1            
    Resource(10, &instance::ApparentPowerR, O_RES_R) ApparentPowerR;
    
    // Optional resource
    // 11 -                 Power Factor phase 1            
    Resource(11, &instance::PowerFactorR, O_RES_R) PowerFactorR;
    
    // Optional resource
    // 12 -                 Total Harmonic Distortion phase 1 (Tension)            
    Resource(12, &instance::THDVR, O_RES_R) THDVR;
    
    // Optional resource
    // 13 -                 Total Harmonig Distortion phase 1 (Current)            
    Resource(13, &instance::THDAR, O_RES_R) THDAR;
    
    // 14 -                 Voltage phase 2 (phase to neutral)            
    Resource(14, &instance::TensionS, O_RES_R) TensionS;
    
    // 15 -                 Current phase 2            
    Resource(15, &instance::CurrentS, O_RES_R) CurrentS;
    
    // Optional resource
    // 16 -                 Active Power phase 2            
    Resource(16, &instance::ActivePowerS, O_RES_R) ActivePowerS;
    
    // Optional resource
    // 17 -                 Reactive Power phase 2            
    Resource(17, &instance::ReactivePowerS, O_RES_R) ReactivePowerS;
    
    // Optional resource
    // 18 -                 Inductive Reactive Power phase 2            
    Resource(18, &instance::InductiveReactivePowerS, O_RES_R) InductiveReactivePowerS;
    
    // Optional resource
    // 19 -                 Capacitive Reactive Power phase 2            
    Resource(19, &instance::CapacitiveReactivePowerS, O_RES_R) CapacitiveReactivePowerS;
    
    // Optional resource
    // 20 -                 Apparent Power phase 2            
    Resource(20, &instance::ApparentPowerS, O_RES_R) ApparentPowerS;
    
    // Optional resource
    // 21 -                 Power Factor phase 2            
    Resource(21, &instance::PowerFactorS, O_RES_R) PowerFactorS;
    
    // Optional resource
    // 22 -                 Total Harmonic Distortion phase 2 (Tension)            
    Resource(22, &instance::THDVS, O_RES_R) THDVS;
    
    // Optional resource
    // 23 -                 Total Harmonic Distortion phase 2 (Current)            
    Resource(23, &instance::THDAS, O_RES_R) THDAS;
    
    // 24 -                 Voltage phase 3 (phase to neutral)            
    Resource(24, &instance::TensionT, O_RES_R) TensionT;
    
    // 25 -                 Current phase 3            
    Resource(25, &instance::CurrentT, O_RES_R) CurrentT;
    
    // Optional resource
    // 26 -                 Active Power phase 3            
    Resource(26, &instance::ActivePowerT, O_RES_R) ActivePowerT;
    
    // Optional resource
    // 27 -                 Reactive Power phase 3            
    Resource(27, &instance::ReactivePowerT, O_RES_R) ReactivePowerT;
    
    // Optional resource
    // 28 -                 Inductive Reactive Power phase 3            
    Resource(28, &instance::InductiveReactivePowerT, O_RES_R) InductiveReactivePowerT;
    
    // Optional resource
    // 29 -                 Capacitive Reactive Power phase 3            
    Resource(29, &instance::CapacitiveReactivePowerT, O_RES_R) CapacitiveReactivePowerT;
    
    // Optional resource
    // 30 -                 Apparent Power phase 3            
    Resource(30, &instance::ApparentPowerT, O_RES_R) ApparentPowerT;
    
    // Optional resource
    // 31 -                 Power Factor phase 3            
    Resource(31, &instance::PowerFactorT, O_RES_R) PowerFactorT;
    
    // Optional resource
    // 32 -                 Total Harmonic Distortion phase 3 (Tension)            
    Resource(32, &instance::THDVT, O_RES_R) THDVT;
    
    // Optional resource
    // 33 -                 Total Harmonic Distortion phase 3 (Current)            
    Resource(33, &instance::THDAT, O_RES_R) THDAT;
    
    // Optional resource
    // 34 -                 3-Phase Active Power            
    Resource(34, &instance::ThreePhaseActivePower, O_RES_R) ThreePhaseActivePower;
    
    // Optional resource
    // 35 -                 3-Phase Reactive Power            
    Resource(35, &instance::ThreePhaseReactivePower, O_RES_R) ThreePhaseReactivePower;
    
    // Optional resource
    // 36 -                 3-Phase Inductive Reactive Power            
    Resource(36, &instance::ThreePhaseInductiveReactivePower, O_RES_R) ThreePhaseInductiveReactivePower;
    
    // Optional resource
    // 37 -                 3-Phase Capacitive Reactive Power            
    Resource(37, &instance::ThreePhaseCapacitiveReactivePower, O_RES_R) ThreePhaseCapacitiveReactivePower;
    
    // Optional resource
    // 38 -                 3-Phase Apparent Power            
    Resource(38, &instance::ThreePhaseApparentPower, O_RES_R) ThreePhaseApparentPower;
    
    // Optional resource
    // 39 -                 3-Phase Power Factor            
    Resource(39, &instance::ThreePhasePowerFactor, O_RES_R) ThreePhasePowerFactor;
    
    // Optional resource
    // 40 -                 3-Phase phi cosine            
    Resource(40, &instance::ThreePhasephicosine, O_RES_R) ThreePhasephicosine;
    
    // Optional resource
    // 41 -                 Active Energy            
    Resource(41, &instance::ActiveEnergy, O_RES_R) ActiveEnergy;
    
    // Optional resource
    // 42 -                 Reactive Energy            
    Resource(42, &instance::ReactiveEnergy, O_RES_R) ReactiveEnergy;
    
    // Optional resource
    // 43 -                 Inductive Reactive Energy            
    Resource(43, &instance::InductiveReactiveEnergy, O_RES_R) InductiveReactiveEnergy;
    
    // Optional resource
    // 44 -                 Capacitive Reactive Energy            
    Resource(44, &instance::CapacitiveReactiveEnergy, O_RES_R) CapacitiveReactiveEnergy;
    
    // Optional resource
    // 45 -                 Apparent Energy            
    Resource(45, &instance::ApparentEnergy, O_RES_R) ApparentEnergy;
    
    // Optional resource
    // 46 -                 Voltage phase 1 to phase 2            
    Resource(46, &instance::TensionRS, O_RES_R) TensionRS;
    
    // Optional resource
    // 47 -                 Voltage phase 2 to phase 3            
    Resource(47, &instance::TensionST, O_RES_R) TensionST;
    
    // Optional resource
    // 48 -                 Voltage phase 3 to phase 1            
    Resource(48, &instance::TensionTR, O_RES_R) TensionTR;
    
    // Optional resource
    // 49 -                 Frequency            
    Resource(49, &instance::Frequency, O_RES_R) Frequency;
    
    // Optional resource
    // 50 -                 Neutral Current            
    Resource(50, &instance::NeutralCurrent, O_RES_R) NeutralCurrent;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10242::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10242::RESID c1) { return (uint16_t) c1 == c2; }
	