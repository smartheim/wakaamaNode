#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10 {
// Custom, overrideable types for Opaque and String resources

    #ifndef ActivatedProfileNames10
    class ActivatedProfileNamesType : public PreallocString<30> {};
    #endif
    
    #ifndef SMSCaddress10
    class SMSCaddressType : public PreallocString<30> {};
    #endif
    
    #ifndef Moduleactivationcode10
    class ModuleactivationcodeType : public PreallocString<30> {};
    #endif
    
    #ifndef eDRXparametersforIumode110
    class eDRXparametersforIumode1Type : public Opaque<30> {};
    #endif
    
    #ifndef eDRXparametersforWBS1mode110
    class eDRXparametersforWBS1mode1Type : public Opaque<30> {};
    #endif
    
    #ifndef eDRXparametersforNBS1mode110
    class eDRXparametersforNBS1mode1Type : public Opaque<30> {};
    #endif
    
    #ifndef eDRXparametersforAGbmode110
    class eDRXparametersforAGbmode1Type : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10 - Cellular connectivity
 *  This object specifies resources to enable a device to connect to a 3GPP or 3GPP2 bearer,
 *  including GPRS/EDGE, UMTS, LTE, NB-IoT, SMS. For cellular connectivity, this object
 *  focuses on Packet Switched (PS) connectivity and doesn’t aim to provide comprehensive
 *  Circuit Switched (CS) connectivity management.Notes:(1) This parameter is controlled
 *  by the 3GPP network. A LWM2M server may write a suggested value to this resource. As soon
 *  a LWM2M server changes the current value the device then suggests the new value to the
 *  network upon the next practical opportunity e.g. by inclusion of the requested value
 *  in an Attach or TAU request. In case the network confirms the suggested value then the
 *  device shall apply that value. In case the network provides a different value then the
 *  value provided by the network shall be applied by the device and the resource value shall
 *  be set to that value. The LWM2M server may use the observe function to be notified upon
 *  any changes of PSM or Active timer. By using the observe function the LWM2M server will
 *  get notified in case the value suggested by the LWM2M server is not accepted by the network,
 *  or, if the value is changed by the network for any reason (e.g. if the device moves into
 *  new tracking areas there is no guarantee that the above values remain the same and are
 *  not altered by the network).
 */
class instance : public Lwm2mObjectInstance {
public:

    // 11 - Links to instances of the “APN connection profile” object representing every APN connection profile that has an activated connection to a PDN.
    ActivatedProfileNamesType ActivatedProfileNames;
    
    // Optional resource
    // 0 - E.164 address of SMSC.   Applicable for 3GPP2 networks where SMSC is not available from a smart card, or for 3GPP/3GPP2 networks to provide the application with a customer specific SMSC.  The application decides how to use this parameter, e.g. precedence over UICC based SMSC address.
    SMSCaddressType SMSCaddress;
    
    // Optional resource
    // 1 - Time period for which the device shall disconnect from cellular radio (PS detach, CS detach if applicable).Can be used to handle network overload situations. The value is a positive integer (0 to 65535), duration can be from 1 minute to 65535 minutes (approximately 45 days).As soon the server writes a value which is >0 the device SHALL disconnect. When the period has elapsed the device MAY reconnect.
    int Disableradioperiod;
    
    // Optional resource
    // 2 - Configurable in case the application needs to issue a code (e.g. via AT command) to activate the module. e.g. “*98”.
    ModuleactivationcodeType Moduleactivationcode;
    
    // Optional resource
    // 3 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 4 - Power saving mode (PSM) timer as defined in [3GPP-TS_23.682].PSM Timer = Extended T3412.Max interval between periodic TAU if there is no other transmission from the device. During most of this time the device is considered as unreachable and can therefore go into a deep sleep mode while keeping the PDN connection(s) active.
    int PSMTimer1;
    
    // Optional resource
    // 5 - Active timer = T3324 as defined in [3GPP-TS_24.008].The time the UE has to remain reachable after transitioning to idle state in case there is pending data from the NW to send out. At the end of T3324 UE can go into a deep sleep mode while keeping the PDN connection(s) active.
    int ActiveTimer1;
    
    // Optional resource
    // 6 - Only for when using Signalling Radio Bearers (c.f. Data over NAS), it indicates the maximum the number of allowed uplink PDU transmissions per 6 minute interval aggregated across all PDN connections. See [3GPP-TS_23.401], octet 3 to 4 of the Serving PLMN rate control IE.
    int ServingPLMNRatecontrol;
    
    // Optional resource
    // 7 - Extended DRX parameters (Paging Time Window and eDRX value) for Iu mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    eDRXparametersforIumode1Type eDRXparametersforIumode1;
    
    // Optional resource
    // 8 - Extended DRX parameters (Paging Time Window and eDRX value) for WB-S1 mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    eDRXparametersforWBS1mode1Type eDRXparametersforWBS1mode1;
    
    // Optional resource
    // 9 - Extended DRX parameters (Paging Time Window and eDRX value) for NB-S1 mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    eDRXparametersforNBS1mode1Type eDRXparametersforNBS1mode1;
    
    // Optional resource
    // 10 - Extended DRX parameters (Paging Time Window and eDRX value) for A/Gb mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    eDRXparametersforAGbmode1Type eDRXparametersforAGbmode1;
    
};

enum class RESID {
    ActivatedProfileNames = 11,
    SMSCaddress = 0,
    Disableradioperiod = 1,
    Moduleactivationcode = 2,
    Vendorspecificextensions = 3,
    PSMTimer1 = 4,
    ActiveTimer1 = 5,
    ServingPLMNRatecontrol = 6,
    eDRXparametersforIumode1 = 7,
    eDRXparametersforWBS1mode1 = 8,
    eDRXparametersforNBS1mode1 = 9,
    eDRXparametersforAGbmode1 = 10,
    
};

/* \brief Class for object 10 - Cellular connectivity
 *  This object specifies resources to enable a device to connect to a 3GPP or 3GPP2 bearer,
 *  including GPRS/EDGE, UMTS, LTE, NB-IoT, SMS. For cellular connectivity, this object
 *  focuses on Packet Switched (PS) connectivity and doesn’t aim to provide comprehensive
 *  Circuit Switched (CS) connectivity management.Notes:(1) This parameter is controlled
 *  by the 3GPP network. A LWM2M server may write a suggested value to this resource. As soon
 *  a LWM2M server changes the current value the device then suggests the new value to the
 *  network upon the next practical opportunity e.g. by inclusion of the requested value
 *  in an Attach or TAU request. In case the network confirms the suggested value then the
 *  device shall apply that value. In case the network provides a different value then the
 *  value provided by the network shall be applied by the device and the resource value shall
 *  be set to that value. The LWM2M server may use the observe function to be notified upon
 *  any changes of PSM or Active timer. By using the observe function the LWM2M server will
 *  get notified in case the value suggested by the LWM2M server is not accepted by the network,
 *  or, if the value is changed by the network for any reason (e.g. if the device moves into
 *  new tracking areas there is no guarantee that the above values remain the same and are
 *  not altered by the network).
 */
class object : public Lwm2mObject<10, object, instance> {
public:

    // 11 - Links to instances of the “APN connection profile” object representing every APN connection profile that has an activated connection to a PDN.
    Resource(11, &instance::ActivatedProfileNames, O_RES_R) ActivatedProfileNames;
    
    // Optional resource
    // 0 - E.164 address of SMSC.   Applicable for 3GPP2 networks where SMSC is not available from a smart card, or for 3GPP/3GPP2 networks to provide the application with a customer specific SMSC.  The application decides how to use this parameter, e.g. precedence over UICC based SMSC address.
    Resource(0, &instance::SMSCaddress, O_RES_RW) SMSCaddress;
    
    // Optional resource
    // 1 - Time period for which the device shall disconnect from cellular radio (PS detach, CS detach if applicable).Can be used to handle network overload situations. The value is a positive integer (0 to 65535), duration can be from 1 minute to 65535 minutes (approximately 45 days).As soon the server writes a value which is >0 the device SHALL disconnect. When the period has elapsed the device MAY reconnect.
    Resource(1, &instance::Disableradioperiod, O_RES_RW) Disableradioperiod;
    
    // Optional resource
    // 2 - Configurable in case the application needs to issue a code (e.g. via AT command) to activate the module. e.g. “*98”.
    Resource(2, &instance::Moduleactivationcode, O_RES_RW) Moduleactivationcode;
    
    // Optional resource
    // 3 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
    // Optional resource
    // 4 - Power saving mode (PSM) timer as defined in [3GPP-TS_23.682].PSM Timer = Extended T3412.Max interval between periodic TAU if there is no other transmission from the device. During most of this time the device is considered as unreachable and can therefore go into a deep sleep mode while keeping the PDN connection(s) active.
    Resource(4, &instance::PSMTimer1, O_RES_RW) PSMTimer1;
    
    // Optional resource
    // 5 - Active timer = T3324 as defined in [3GPP-TS_24.008].The time the UE has to remain reachable after transitioning to idle state in case there is pending data from the NW to send out. At the end of T3324 UE can go into a deep sleep mode while keeping the PDN connection(s) active.
    Resource(5, &instance::ActiveTimer1, O_RES_RW) ActiveTimer1;
    
    // Optional resource
    // 6 - Only for when using Signalling Radio Bearers (c.f. Data over NAS), it indicates the maximum the number of allowed uplink PDU transmissions per 6 minute interval aggregated across all PDN connections. See [3GPP-TS_23.401], octet 3 to 4 of the Serving PLMN rate control IE.
    Resource(6, &instance::ServingPLMNRatecontrol, O_RES_R) ServingPLMNRatecontrol;
    
    // Optional resource
    // 7 - Extended DRX parameters (Paging Time Window and eDRX value) for Iu mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    Resource(7, &instance::eDRXparametersforIumode1, O_RES_RW) eDRXparametersforIumode1;
    
    // Optional resource
    // 8 - Extended DRX parameters (Paging Time Window and eDRX value) for WB-S1 mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    Resource(8, &instance::eDRXparametersforWBS1mode1, O_RES_RW) eDRXparametersforWBS1mode1;
    
    // Optional resource
    // 9 - Extended DRX parameters (Paging Time Window and eDRX value) for NB-S1 mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    Resource(9, &instance::eDRXparametersforNBS1mode1, O_RES_RW) eDRXparametersforNBS1mode1;
    
    // Optional resource
    // 10 - Extended DRX parameters (Paging Time Window and eDRX value) for A/Gb mode which the UE can request from the network. This resource is encoded as octet 3 in [3GPP-TS_24.008, clause 10.5.5.32].
    Resource(10, &instance::eDRXparametersforAGbmode1, O_RES_RW) eDRXparametersforAGbmode1;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10::RESID c1) { return (uint16_t) c1 == c2; }
	