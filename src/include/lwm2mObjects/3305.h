#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3305 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ResetCumulativeenergy3305
    class ResetCumulativeenergyType : public Opaque<30> {};
    #endif
    
    #ifndef ResetMinandMaxMeasuredValues3305
    class ResetMinandMaxMeasuredValuesType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 3305 - Power Measurement
 *  This IPSO object should be used over a power measurement sensor to report a remote power
 *  measurement. It also provides resources for minimum/maximum measured values and
 *  the minimum/maximum range for both active and reactive power. Il also provides resources
 *  for cumulative energy, calibration, and the power factor.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5800 - The current active power
    float Instantaneousactivepower;
    
    // Optional resource
    // 5801 - The minimum active power measured by the sensor since it is ON
    float MinMeasuredactivepower;
    
    // Optional resource
    // 5802 - The maximum active power measured by the sensor since it is ON
    float MaxMeasuredactivepower;
    
    // Optional resource
    // 5803 - The minimum active power that can be measured by the sensor
    float MinRangeactivepower;
    
    // Optional resource
    // 5804 - The maximum active power that can be measured by the sensor
    float MaxRangeactivepower;
    
    // Optional resource
    // 5805 - The cumulative active power since the last cumulative energy reset or device start
    float Cumulativeactivepower;
    
    // Optional resource
    // 5806 - Request an active power calibration by writing the value of a calibrated load.
    float ActivePowerCalibration;
    
    // Optional resource
    // 5810 - The current reactive power
    float Instantaneousreactivepower;
    
    // Optional resource
    // 5811 - The minimum reactive power measured by the sensor since it is ON
    float MinMeasuredreactivepower;
    
    // Optional resource
    // 5812 - The maximum reactive power measured by the sensor since it is ON
    float MaxMeasuredreactivepower;
    
    // Optional resource
    // 5813 - The minimum active power that can be measured by the sensor
    float MinRangereactivepower;
    
    // Optional resource
    // 5814 - The maximum reactive power that can be measured by the sensor
    float MaxRangereactivepower;
    
    // Optional resource
    // 5815 - The cumulative reactive power since the last cumulative energy reset or device start
    float Cumulativereactivepower;
    
    // Optional resource
    // 5816 - Request a reactive power calibration by writing the value of a calibrated load.
    float ReactivePowerCalibration;
    
    // Optional resource
    // 5820 - If applicable, the power factor of the current consumption.
    float PowerFactor;
    
    // Optional resource
    // 5821 - Read or Write the current calibration coefficient
    float CurrentCalibration;
    
    // Optional resource
    // 5822 - Reset both cumulative active/reactive power
    Executable ResetCumulativeenergy;

    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Executable ResetMinandMaxMeasuredValues;

};

enum class RESID {
    Instantaneousactivepower = 5800,
    MinMeasuredactivepower = 5801,
    MaxMeasuredactivepower = 5802,
    MinRangeactivepower = 5803,
    MaxRangeactivepower = 5804,
    Cumulativeactivepower = 5805,
    ActivePowerCalibration = 5806,
    Instantaneousreactivepower = 5810,
    MinMeasuredreactivepower = 5811,
    MaxMeasuredreactivepower = 5812,
    MinRangereactivepower = 5813,
    MaxRangereactivepower = 5814,
    Cumulativereactivepower = 5815,
    ReactivePowerCalibration = 5816,
    PowerFactor = 5820,
    CurrentCalibration = 5821,
    ResetCumulativeenergy = 5822,
    ResetMinandMaxMeasuredValues = 5605,
    
};

/* \brief Class for object 3305 - Power Measurement
 *  This IPSO object should be used over a power measurement sensor to report a remote power
 *  measurement. It also provides resources for minimum/maximum measured values and
 *  the minimum/maximum range for both active and reactive power. Il also provides resources
 *  for cumulative energy, calibration, and the power factor.
 */
class object : public Lwm2mObject<3305, object, instance> {
public:

    // 5800 - The current active power
    Resource(5800, &instance::Instantaneousactivepower, O_RES_R) Instantaneousactivepower;
    
    // Optional resource
    // 5801 - The minimum active power measured by the sensor since it is ON
    Resource(5801, &instance::MinMeasuredactivepower, O_RES_R) MinMeasuredactivepower;
    
    // Optional resource
    // 5802 - The maximum active power measured by the sensor since it is ON
    Resource(5802, &instance::MaxMeasuredactivepower, O_RES_R) MaxMeasuredactivepower;
    
    // Optional resource
    // 5803 - The minimum active power that can be measured by the sensor
    Resource(5803, &instance::MinRangeactivepower, O_RES_R) MinRangeactivepower;
    
    // Optional resource
    // 5804 - The maximum active power that can be measured by the sensor
    Resource(5804, &instance::MaxRangeactivepower, O_RES_R) MaxRangeactivepower;
    
    // Optional resource
    // 5805 - The cumulative active power since the last cumulative energy reset or device start
    Resource(5805, &instance::Cumulativeactivepower, O_RES_R) Cumulativeactivepower;
    
    // Optional resource
    // 5806 - Request an active power calibration by writing the value of a calibrated load.
    Resource(5806, &instance::ActivePowerCalibration, O_RES_W) ActivePowerCalibration;
    
    // Optional resource
    // 5810 - The current reactive power
    Resource(5810, &instance::Instantaneousreactivepower, O_RES_R) Instantaneousreactivepower;
    
    // Optional resource
    // 5811 - The minimum reactive power measured by the sensor since it is ON
    Resource(5811, &instance::MinMeasuredreactivepower, O_RES_R) MinMeasuredreactivepower;
    
    // Optional resource
    // 5812 - The maximum reactive power measured by the sensor since it is ON
    Resource(5812, &instance::MaxMeasuredreactivepower, O_RES_R) MaxMeasuredreactivepower;
    
    // Optional resource
    // 5813 - The minimum active power that can be measured by the sensor
    Resource(5813, &instance::MinRangereactivepower, O_RES_R) MinRangereactivepower;
    
    // Optional resource
    // 5814 - The maximum reactive power that can be measured by the sensor
    Resource(5814, &instance::MaxRangereactivepower, O_RES_R) MaxRangereactivepower;
    
    // Optional resource
    // 5815 - The cumulative reactive power since the last cumulative energy reset or device start
    Resource(5815, &instance::Cumulativereactivepower, O_RES_R) Cumulativereactivepower;
    
    // Optional resource
    // 5816 - Request a reactive power calibration by writing the value of a calibrated load.
    Resource(5816, &instance::ReactivePowerCalibration, O_RES_W) ReactivePowerCalibration;
    
    // Optional resource
    // 5820 - If applicable, the power factor of the current consumption.
    Resource(5820, &instance::PowerFactor, O_RES_R) PowerFactor;
    
    // Optional resource
    // 5821 - Read or Write the current calibration coefficient
    Resource(5821, &instance::CurrentCalibration, O_RES_RW) CurrentCalibration;
    
    // Optional resource
    // 5822 - Reset both cumulative active/reactive power
    Resource(5822, &instance::ResetCumulativeenergy) ResetCumulativeenergy;
    
    // Optional resource
    // 5605 - Reset the Min and Max Measured Values to Current Value
    Resource(5605, &instance::ResetMinandMaxMeasuredValues) ResetMinandMaxMeasuredValues;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3305::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3305::RESID c1) { return (uint16_t) c1 == c2; }
	