#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3375 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3375 - PagingDRX
 *  Paging DRX information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6032 - EARFCN - frequency
    int dlEarfcn;
    
    // 6034 - PCI
    int pci;
    
    // 2 - Paging Cycle
    int pagingCycle;
    
    // 3 - DRX NB
    int DrxNb;
    
    // 4 - IMSI mod 1024
    int ueID;
    
    // 5 - drxSysFrameNumOffset is used to obtain the starting system frame number for DRX cycle
    int drxSysFrameNumOffset;
    
    // 6 - drxSubFrameNumOffset is used to obtain the starting sub frame number for DRX cycle
    int drxSubFrameNumOffset;
    
};

enum class RESID {
    dlEarfcn = 6032,
    pci = 6034,
    pagingCycle = 2,
    DrxNb = 3,
    ueID = 4,
    drxSysFrameNumOffset = 5,
    drxSubFrameNumOffset = 6,
    
};

/* \brief Class for object 3375 - PagingDRX
 *  Paging DRX information
 */
class object : public Lwm2mObject<3375, object, instance> {
public:

    // 6032 - EARFCN - frequency
    Resource(6032, &instance::dlEarfcn, O_RES_R) dlEarfcn;
    
    // 6034 - PCI
    Resource(6034, &instance::pci, O_RES_R) pci;
    
    // 2 - Paging Cycle
    Resource(2, &instance::pagingCycle, O_RES_R) pagingCycle;
    
    // 3 - DRX NB
    Resource(3, &instance::DrxNb, O_RES_R) DrxNb;
    
    // 4 - IMSI mod 1024
    Resource(4, &instance::ueID, O_RES_R) ueID;
    
    // 5 - drxSysFrameNumOffset is used to obtain the starting system frame number for DRX cycle
    Resource(5, &instance::drxSysFrameNumOffset, O_RES_R) drxSysFrameNumOffset;
    
    // 6 - drxSubFrameNumOffset is used to obtain the starting sub frame number for DRX cycle
    Resource(6, &instance::drxSubFrameNumOffset, O_RES_R) drxSubFrameNumOffset;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3375::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3375::RESID c1) { return (uint16_t) c1 == c2; }
	