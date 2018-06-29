#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id13 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Celllocklist13
    class CelllocklistType : public PreallocString<30> {};
    #endif
    
    #ifndef Operatorlist13
    class OperatorlistType : public PreallocString<30> {};
    #endif
    
    #ifndef ListofavailablePLMNs13
    class ListofavailablePLMNsType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 13 - Bearer selection
 *  This object specifies resources to enable a device to choose a PLMN/network on which
 *  to attach/register and what type of bearer to then connect. This object allows via remote
 *  bearer and network configuration to overwrite automatic network and bearer selection
 *  e.g. as supported by the UICC. An equivalent example for overwriting automatic selection
 *  is a user doing manual network and bearer selection on a smart phone.Notes:(1) Remote
 *  management of this communications bearer via LWM2M is currently not supported.(2)
 *  See [3GPP-TS_23.401, section 4.3.5.10] for the Preferred Network Behaviour indication
 *  used by the UE to inform the network about its capabilities and preferences.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Used in network selection and, if applicable, in subsequent mobility management procedures:0: auto connect1: 3GPP PS preferred2: 3GPP PS GSM (GPRS) preferred (including EC-GSM-IoT)3: 3GPP PS UMTS preferred4: 3GPP PS LTE preferred5: 1xEV-DO preferred (1)6: 3GPP CS preferred (1)7: WLAN preferred8: Ethernet preferred (1)9: DSL preferred (1)10: Bluetooth preferred (1)11: WIMAX preferred (1)12: 3GPP PS LTE with CIoT EPS optimisations, User Plane preferred (2)13: 3GPP PS LTE with CIoT EPS optimisations, Control Plane preferred (2)14: 3GPP PS NB-IoT Control Plane optimisations preferred (2)15: 3GPP PS NB-IoT User Plane optimisations preferred (2) 16-100: Reserved for future useThe Preferred Communications Bearer resource specifies the preferred communications bearer that the LWM2M Client is requested to use for connecting to the LWM2M Server. If multiple preferred communications bearers are specified, the priority order is reflected by the resource instance order. E.g. the bearer which appears first in the list of resource instances is to have higher priority over the rest of available bearers. The LWM2M Client SHOULD use the preferred bearers with higher priority first if they are available. If none of indicated preferred bearers is available, the LWM2M Client SHOULD wait until one of them becomes available. 
    int PreferredCommunicationsBearer;
    
    // Optional resource
    // 1 - Provides guide to the application when performing manual network selection.
    int AcceptableRSSIGSM;
    
    // Optional resource
    // 2 - Provides guide to the application when performing manual network selection.
    int AcceptableRSCPUMTS;
    
    // Optional resource
    // 3 - Provides guide to the application when performing manual network selection.
    int AcceptableRSRPLTE;
    
    // Optional resource
    // 4 - Provides guide to the application when performing manual network selection.
    int AcceptableRSSI1xEVDO;
    
    // Optional resource
    // 5 - Comma separated list of allowed Global Cell Identities.
    CelllocklistType Celllocklist;
    
    // Optional resource
    // 6 - Comma separated list of MCC+MNC of operators, in priority order.Resource “operator list mode” indicates how to process this list.
    OperatorlistType Operatorlist;
    
    // Optional resource
    // 7 - Indicates whether resource “operator list” represents the allowed operator list (white list), or, the preferred operator list.0=preferred1=allowed
    bool Operatorlistmode;
    
    // Optional resource
    // 8 - Allows server to see results of network scan (e.g. result of AT+COPS=?)
    ListofavailablePLMNsType ListofavailablePLMNs;
    
    // Optional resource
    // 9 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 10 - Provides guide to the application when performing manual network selection.
    int AcceptableRSRPNBIoT;
    
    // Optional resource
    // 11 - Interval between periodic searches for higher priority PLMNs of the same country when camped on a visited PLMN, i.e. roaming scenario; based on SIM configuration, EFHPPLMN [3GPP-TS_31.102, section 4.2.6]
    int HigherPriorityPLMNSearchTimer;
    
    // Optional resource
    // 12 - 0=attach with PDN connection1=attach without PDN connection
    bool AttachwithoutPDNconnection;
    
};

enum class RESID {
    PreferredCommunicationsBearer = 0,
    AcceptableRSSIGSM = 1,
    AcceptableRSCPUMTS = 2,
    AcceptableRSRPLTE = 3,
    AcceptableRSSI1xEVDO = 4,
    Celllocklist = 5,
    Operatorlist = 6,
    Operatorlistmode = 7,
    ListofavailablePLMNs = 8,
    Vendorspecificextensions = 9,
    AcceptableRSRPNBIoT = 10,
    HigherPriorityPLMNSearchTimer = 11,
    AttachwithoutPDNconnection = 12,
    
};

/* \brief Class for object 13 - Bearer selection
 *  This object specifies resources to enable a device to choose a PLMN/network on which
 *  to attach/register and what type of bearer to then connect. This object allows via remote
 *  bearer and network configuration to overwrite automatic network and bearer selection
 *  e.g. as supported by the UICC. An equivalent example for overwriting automatic selection
 *  is a user doing manual network and bearer selection on a smart phone.Notes:(1) Remote
 *  management of this communications bearer via LWM2M is currently not supported.(2)
 *  See [3GPP-TS_23.401, section 4.3.5.10] for the Preferred Network Behaviour indication
 *  used by the UE to inform the network about its capabilities and preferences.
 */
class object : public Lwm2mObject<13, object, instance> {
public:

    // Optional resource
    // 0 - Used in network selection and, if applicable, in subsequent mobility management procedures:0: auto connect1: 3GPP PS preferred2: 3GPP PS GSM (GPRS) preferred (including EC-GSM-IoT)3: 3GPP PS UMTS preferred4: 3GPP PS LTE preferred5: 1xEV-DO preferred (1)6: 3GPP CS preferred (1)7: WLAN preferred8: Ethernet preferred (1)9: DSL preferred (1)10: Bluetooth preferred (1)11: WIMAX preferred (1)12: 3GPP PS LTE with CIoT EPS optimisations, User Plane preferred (2)13: 3GPP PS LTE with CIoT EPS optimisations, Control Plane preferred (2)14: 3GPP PS NB-IoT Control Plane optimisations preferred (2)15: 3GPP PS NB-IoT User Plane optimisations preferred (2) 16-100: Reserved for future useThe Preferred Communications Bearer resource specifies the preferred communications bearer that the LWM2M Client is requested to use for connecting to the LWM2M Server. If multiple preferred communications bearers are specified, the priority order is reflected by the resource instance order. E.g. the bearer which appears first in the list of resource instances is to have higher priority over the rest of available bearers. The LWM2M Client SHOULD use the preferred bearers with higher priority first if they are available. If none of indicated preferred bearers is available, the LWM2M Client SHOULD wait until one of them becomes available. 
    Resource(0, &instance::PreferredCommunicationsBearer, O_RES_RW) PreferredCommunicationsBearer;
    
    // Optional resource
    // 1 - Provides guide to the application when performing manual network selection.
    Resource(1, &instance::AcceptableRSSIGSM, O_RES_RW) AcceptableRSSIGSM;
    
    // Optional resource
    // 2 - Provides guide to the application when performing manual network selection.
    Resource(2, &instance::AcceptableRSCPUMTS, O_RES_RW) AcceptableRSCPUMTS;
    
    // Optional resource
    // 3 - Provides guide to the application when performing manual network selection.
    Resource(3, &instance::AcceptableRSRPLTE, O_RES_RW) AcceptableRSRPLTE;
    
    // Optional resource
    // 4 - Provides guide to the application when performing manual network selection.
    Resource(4, &instance::AcceptableRSSI1xEVDO, O_RES_RW) AcceptableRSSI1xEVDO;
    
    // Optional resource
    // 5 - Comma separated list of allowed Global Cell Identities.
    Resource(5, &instance::Celllocklist, O_RES_RW) Celllocklist;
    
    // Optional resource
    // 6 - Comma separated list of MCC+MNC of operators, in priority order.Resource “operator list mode” indicates how to process this list.
    Resource(6, &instance::Operatorlist, O_RES_RW) Operatorlist;
    
    // Optional resource
    // 7 - Indicates whether resource “operator list” represents the allowed operator list (white list), or, the preferred operator list.0=preferred1=allowed
    Resource(7, &instance::Operatorlistmode, O_RES_RW) Operatorlistmode;
    
    // Optional resource
    // 8 - Allows server to see results of network scan (e.g. result of AT+COPS=?)
    Resource(8, &instance::ListofavailablePLMNs, O_RES_R) ListofavailablePLMNs;
    
    // Optional resource
    // 9 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 10 - Provides guide to the application when performing manual network selection.
    Resource(10, &instance::AcceptableRSRPNBIoT, O_RES_RW) AcceptableRSRPNBIoT;
    
    // Optional resource
    // 11 - Interval between periodic searches for higher priority PLMNs of the same country when camped on a visited PLMN, i.e. roaming scenario; based on SIM configuration, EFHPPLMN [3GPP-TS_31.102, section 4.2.6]
    Resource(11, &instance::HigherPriorityPLMNSearchTimer, O_RES_RW) HigherPriorityPLMNSearchTimer;
    
    // Optional resource
    // 12 - 0=attach with PDN connection1=attach without PDN connection
    Resource(12, &instance::AttachwithoutPDNconnection, O_RES_RW) AttachwithoutPDNconnection;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id13::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id13::RESID c1) { return (uint16_t) c1 == c2; }
	