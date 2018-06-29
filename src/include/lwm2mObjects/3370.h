#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3370 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3370 - ServingCellMeasurement
 *  Serving Cell Measurement
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6037 - System Frame Number
    int sysFrameNumber;
    
    // 6038 - Sub Frame Number
    int subFrameNumber;
    
    // 6034 - PCI (0..504)
    int pci;
    
    // 6035 - RSRP Value in dBm (-180..-30)
    int rsrp;
    
    // 6036 - RSRQ Value in dB (-30..10)
    int rsrq;
    
    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
};

enum class RESID {
    sysFrameNumber = 6037,
    subFrameNumber = 6038,
    pci = 6034,
    rsrp = 6035,
    rsrq = 6036,
    dlEarfcn = 6032,
    
};

/* \brief Class for object 3370 - ServingCellMeasurement
 *  Serving Cell Measurement
 */
class object : public Lwm2mObject<3370, object, instance> {
public:

    // 6037 - System Frame Number
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
    // 6038 - Sub Frame Number
    Resource(6038, &instance::subFrameNumber, O_RES_R) subFrameNumber;
    
    // 6034 - PCI (0..504)
    Resource(6034, &instance::pci, O_RES_R) pci;
    
    // 6035 - RSRP Value in dBm (-180..-30)
    Resource(6035, &instance::rsrp, O_RES_R) rsrp;
    
    // 6036 - RSRQ Value in dB (-30..10)
    Resource(6036, &instance::rsrq, O_RES_R) rsrq;
    
    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3370::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3370::RESID c1) { return (uint16_t) c1 == c2; }
	