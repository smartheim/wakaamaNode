#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10244 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10244 - VehicleControlUnit
 *  This Object provides the information to represent a generic VCU(vehicle control unit).
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The UI state of the vehicle. 0: idle 1: driving 2: charging 3: limp-home 4-15: reserved for future use
    int VehicleUIState;
    
    // 1 - Current speed of the vehicle.
    int VehicleSpeed;
    
    // 2 - Current shift status of the vehicle. 0: Neutral 1: Forward 2: Reverse
    int VehicleShiftStatus;
    
    // 3 - Current position of the accelerator pedal.
    int VehicleAPPosition;
    
    // Optional resource
    // 4 - Current power of drive output/regenerative braking.
    float VehiclePower;
    
    // Optional resource
    // 5 - Accumulated drive energy of the vehicle.
    float VehicleDriveEnergy;
    
    // Optional resource
    // 6 - Energy consumption efficiency of the vehicle.
    float VehicleEnergyConsumptionEfficiency;
    
    // Optional resource
    // 7 - Estimated mileage of current battery capacity.
    int VehicleEstimatedMileage;
    
    // 8 - Whether the charge cable is connected or not. 0: unconnected 1: connected
    bool VehicleChargeCableStatus;
    
    // 9 - Charging status of the vehicle. 1: non-charge mode 2: charging 3: charge completed 4: charging abort abnormally 
    int VehicleChargeStatus;
    
    // 10 - Charging voltage
    float VehicleChargeVoltage;
    
    // 11 - Charging current
    float VehicleChargeCurrent;
    
    // 12 - Remaining charging time
    int VehicleChargeRemainingTime;
    
    // 13 - Voltage of the battery pack
    float BatteryPackVoltage;
    
    // 14 - Current of the battery pack
    float BatteryPackCurrent;
    
    // 15 - Remaining capacity of the battery pack
    int BatteryPackRemainingCapacity;
    
    // 16 - SOC(state of charge) of the battery pack
    int BatteryPackSOC;
    
    // 17 - SOH(state of health) of the battery pack
    int BatteryPackSOH;
    
    // 18 - Minimum voltage of the battery module (with parallel connection of cells)
    int BatteryCellMinVolt;
    
    // 19 - Maximum voltage of the battery module (with parallel connection of cells)
    int BatteryCellMaxVolt;
    
    // 20 - Minimum temperature of the battery module
    int BatteryModuleMinTemp;
    
    // 21 - Maximum temperature of the battery module
    int BatteryModuleMaxTemp;
    
    // 22 - Whether the battery is connected or not. 0: unconnected 1: connected
    bool BatteryConnectionStatus;
    
    // 24 - Voltage of the MCU(motor control unit)
    int MCUVoltage;
    
    // 25 - Temperature of MCU(motor control unit)
    int MCUTemperature;
    
    // 26 - Rotational speed of the motor
    int MotorSpeed;
    
    // 27 - Temperature of the motor
    int MotorTemperature;
    
    // Optional resource
    // 28 - Whether the motor is OT or not. 0: normal 1: OT warning
    bool MotorOTWarning;
    
    // Optional resource
    // 29 - Whether the MCU is OT or not. 0: normal 1: OT warning
    bool MCUOTWarning;
    
    // Optional resource
    // 30 - Whether the battery pack is OT or not. 0: normal 1: OT warning
    bool BatteryPackOTWarning;
    
    // Optional resource
    // 31 - Status of MCU. 0: normal 1: level 1 minor fault 2: level 2 critical fault
    bool MCUfault;
    
    // Optional resource
    // 32 - Status of the battery pack. 0: normal 1: level D25 minor fault 2: level 2 critical fault
    bool MotorError;
    
};

enum class RESID {
    VehicleUIState = 0,
    VehicleSpeed = 1,
    VehicleShiftStatus = 2,
    VehicleAPPosition = 3,
    VehiclePower = 4,
    VehicleDriveEnergy = 5,
    VehicleEnergyConsumptionEfficiency = 6,
    VehicleEstimatedMileage = 7,
    VehicleChargeCableStatus = 8,
    VehicleChargeStatus = 9,
    VehicleChargeVoltage = 10,
    VehicleChargeCurrent = 11,
    VehicleChargeRemainingTime = 12,
    BatteryPackVoltage = 13,
    BatteryPackCurrent = 14,
    BatteryPackRemainingCapacity = 15,
    BatteryPackSOC = 16,
    BatteryPackSOH = 17,
    BatteryCellMinVolt = 18,
    BatteryCellMaxVolt = 19,
    BatteryModuleMinTemp = 20,
    BatteryModuleMaxTemp = 21,
    BatteryConnectionStatus = 22,
    MCUVoltage = 24,
    MCUTemperature = 25,
    MotorSpeed = 26,
    MotorTemperature = 27,
    MotorOTWarning = 28,
    MCUOTWarning = 29,
    BatteryPackOTWarning = 30,
    MCUfault = 31,
    MotorError = 32,
    
};

/* \brief Class for object 10244 - VehicleControlUnit
 *  This Object provides the information to represent a generic VCU(vehicle control unit).
 */
class object : public Lwm2mObject<10244, object, instance> {
public:

    // 0 - The UI state of the vehicle. 0: idle 1: driving 2: charging 3: limp-home 4-15: reserved for future use
    Resource(0, &instance::VehicleUIState, O_RES_R) VehicleUIState;
    
    // 1 - Current speed of the vehicle.
    Resource(1, &instance::VehicleSpeed, O_RES_R) VehicleSpeed;
    
    // 2 - Current shift status of the vehicle. 0: Neutral 1: Forward 2: Reverse
    Resource(2, &instance::VehicleShiftStatus, O_RES_R) VehicleShiftStatus;
    
    // 3 - Current position of the accelerator pedal.
    Resource(3, &instance::VehicleAPPosition, O_RES_R) VehicleAPPosition;
    
    // Optional resource
    // 4 - Current power of drive output/regenerative braking.
    Resource(4, &instance::VehiclePower, O_RES_R) VehiclePower;
    
    // Optional resource
    // 5 - Accumulated drive energy of the vehicle.
    Resource(5, &instance::VehicleDriveEnergy, O_RES_R) VehicleDriveEnergy;
    
    // Optional resource
    // 6 - Energy consumption efficiency of the vehicle.
    Resource(6, &instance::VehicleEnergyConsumptionEfficiency, O_RES_R) VehicleEnergyConsumptionEfficiency;
    
    // Optional resource
    // 7 - Estimated mileage of current battery capacity.
    Resource(7, &instance::VehicleEstimatedMileage, O_RES_R) VehicleEstimatedMileage;
    
    // 8 - Whether the charge cable is connected or not. 0: unconnected 1: connected
    Resource(8, &instance::VehicleChargeCableStatus, O_RES_R) VehicleChargeCableStatus;
    
    // 9 - Charging status of the vehicle. 1: non-charge mode 2: charging 3: charge completed 4: charging abort abnormally 
    Resource(9, &instance::VehicleChargeStatus, O_RES_R) VehicleChargeStatus;
    
    // 10 - Charging voltage
    Resource(10, &instance::VehicleChargeVoltage, O_RES_R) VehicleChargeVoltage;
    
    // 11 - Charging current
    Resource(11, &instance::VehicleChargeCurrent, O_RES_R) VehicleChargeCurrent;
    
    // 12 - Remaining charging time
    Resource(12, &instance::VehicleChargeRemainingTime, O_RES_R) VehicleChargeRemainingTime;
    
    // 13 - Voltage of the battery pack
    Resource(13, &instance::BatteryPackVoltage, O_RES_R) BatteryPackVoltage;
    
    // 14 - Current of the battery pack
    Resource(14, &instance::BatteryPackCurrent, O_RES_R) BatteryPackCurrent;
    
    // 15 - Remaining capacity of the battery pack
    Resource(15, &instance::BatteryPackRemainingCapacity, O_RES_R) BatteryPackRemainingCapacity;
    
    // 16 - SOC(state of charge) of the battery pack
    Resource(16, &instance::BatteryPackSOC, O_RES_R) BatteryPackSOC;
    
    // 17 - SOH(state of health) of the battery pack
    Resource(17, &instance::BatteryPackSOH, O_RES_R) BatteryPackSOH;
    
    // 18 - Minimum voltage of the battery module (with parallel connection of cells)
    Resource(18, &instance::BatteryCellMinVolt, O_RES_R) BatteryCellMinVolt;
    
    // 19 - Maximum voltage of the battery module (with parallel connection of cells)
    Resource(19, &instance::BatteryCellMaxVolt, O_RES_R) BatteryCellMaxVolt;
    
    // 20 - Minimum temperature of the battery module
    Resource(20, &instance::BatteryModuleMinTemp, O_RES_R) BatteryModuleMinTemp;
    
    // 21 - Maximum temperature of the battery module
    Resource(21, &instance::BatteryModuleMaxTemp, O_RES_R) BatteryModuleMaxTemp;
    
    // 22 - Whether the battery is connected or not. 0: unconnected 1: connected
    Resource(22, &instance::BatteryConnectionStatus, O_RES_R) BatteryConnectionStatus;
    
    // 24 - Voltage of the MCU(motor control unit)
    Resource(24, &instance::MCUVoltage, O_RES_R) MCUVoltage;
    
    // 25 - Temperature of MCU(motor control unit)
    Resource(25, &instance::MCUTemperature, O_RES_R) MCUTemperature;
    
    // 26 - Rotational speed of the motor
    Resource(26, &instance::MotorSpeed, O_RES_R) MotorSpeed;
    
    // 27 - Temperature of the motor
    Resource(27, &instance::MotorTemperature, O_RES_R) MotorTemperature;
    
    // Optional resource
    // 28 - Whether the motor is OT or not. 0: normal 1: OT warning
    Resource(28, &instance::MotorOTWarning, O_RES_R) MotorOTWarning;
    
    // Optional resource
    // 29 - Whether the MCU is OT or not. 0: normal 1: OT warning
    Resource(29, &instance::MCUOTWarning, O_RES_R) MCUOTWarning;
    
    // Optional resource
    // 30 - Whether the battery pack is OT or not. 0: normal 1: OT warning
    Resource(30, &instance::BatteryPackOTWarning, O_RES_R) BatteryPackOTWarning;
    
    // Optional resource
    // 31 - Status of MCU. 0: normal 1: level 1 minor fault 2: level 2 critical fault
    Resource(31, &instance::MCUfault, O_RES_R) MCUfault;
    
    // Optional resource
    // 32 - Status of the battery pack. 0: normal 1: level D25 minor fault 2: level 2 critical fault
    Resource(32, &instance::MotorError, O_RES_R) MotorError;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10244::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10244::RESID c1) { return (uint16_t) c1 == c2; }
	