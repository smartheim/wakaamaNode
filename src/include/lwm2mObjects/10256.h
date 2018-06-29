#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10256 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 10256 - ECID-Signal Measurement Information
 *  This LWM2M Object provides ECID signal measurements of a device.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - This field specifies the physical cell identity of the measured cell.
    int physCellId;
    
    // Optional resource
    // 1 - This field specifies cell global ID of the measured cell. The target device shall provide this field if it was able to determine the ECGI of the measured cell at the time of measurement.
    int ECGI;
    
    // 2 - This field specifies the ARFCN of the measured E-UTRA carrier frequency.
    int arfcnEUTRA;
    
    // 3 - This field specifies the reference signal received power (RSRP) measurement.
    int rsrpResult;
    
    // Optional resource
    // 4 - This field specifies the reference signal received quality (RSRQ) measurement.
    int rsrqResult;
    
    // Optional resource
    // 5 - This field specifies the UE Rx–Tx time difference measurement.
    int ueRxTxTimeDiff;
    
};

enum class RESID {
    physCellId = 0,
    ECGI = 1,
    arfcnEUTRA = 2,
    rsrpResult = 3,
    rsrqResult = 4,
    ueRxTxTimeDiff = 5,
    
};

/* \brief Class for object 10256 - ECID-Signal Measurement Information
 *  This LWM2M Object provides ECID signal measurements of a device.
 */
class object : public Lwm2mObject<10256, object, instance> {
public:

    // 0 - This field specifies the physical cell identity of the measured cell.
    Resource(0, &instance::physCellId, O_RES_R) physCellId;
    
    // Optional resource
    // 1 - This field specifies cell global ID of the measured cell. The target device shall provide this field if it was able to determine the ECGI of the measured cell at the time of measurement.
    Resource(1, &instance::ECGI, O_RES_R) ECGI;
    
    // 2 - This field specifies the ARFCN of the measured E-UTRA carrier frequency.
    Resource(2, &instance::arfcnEUTRA, O_RES_R) arfcnEUTRA;
    
    // 3 - This field specifies the reference signal received power (RSRP) measurement.
    Resource(3, &instance::rsrpResult, O_RES_R) rsrpResult;
    
    // Optional resource
    // 4 - This field specifies the reference signal received quality (RSRQ) measurement.
    Resource(4, &instance::rsrqResult, O_RES_R) rsrqResult;
    
    // Optional resource
    // 5 - This field specifies the UE Rx–Tx time difference measurement.
    Resource(5, &instance::ueRxTxTimeDiff, O_RES_R) ueRxTxTimeDiff;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10256::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10256::RESID c1) { return (uint16_t) c1 == c2; }
	