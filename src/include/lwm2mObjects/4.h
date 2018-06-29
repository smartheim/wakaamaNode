#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id4 {
// Custom, overrideable types for Opaque and String resources

    #ifndef IPAddresses4
    class IPAddressesType : public PreallocString<30> {};
    #endif
    
    #ifndef RouterIPAddresses4
    class RouterIPAddressesType : public PreallocString<30> {};
    #endif
    
    #ifndef APN4
    class APNType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 4 - Connectivity Monitoring
 *  This LwM2M Object enables monitoring of parameters related to network connectivity.In
 *  this general connectivity Object, the Resources are limited to the most general cases
 *  common to most network bearers. It is recommended to read the description, which refers
 *  to relevant standard development organizations (e.g., 3GPP, IEEE).The goal of the
 *  Connectivity Monitoring Object is to carry information reflecting the more up to date
 *  values of the current connection for monitoring purposes. Resources such as Link Quality,
 *  Radio Signal Strength, Cell ID are retrieved during connected mode at least for cellular
 *  networks.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Indicates the network bearer used for the current LwM2M communication session from the below network bearer list.0~20 are Cellular Bearers0: GSM cellular network1: TD-SCDMA cellular network2: WCDMA cellular network3: CDMA2000 cellular network4: WiMAX cellular network5: LTE-TDD cellular network6: LTE-FDD cellular network7: NB-IoT8~20: Reserved for other type cellular network21~40 are Wireless Bearers21: WLAN network22: Bluetooth network23: IEEE 802.15.4 network24~40: Reserved for other type local wireless network41~50 are Wireline Bearers41: Ethernet42: DSL43: PLC44~50: reserved for others type wireline networks.
    int NetworkBearer;
    
    // 1 - Indicates list of current available network bearer. Each Resource Instance has a value from the network bearer list.
    int AvailableNetworkBearer;
    
    // 2 - This node contains the average value of thereceived signal strength indication used in thecurrent network bearer (as indicated byResource 0 of this Object). For the following network bearers the signal strength parameters indicated below are represented by this resource:GSM:    RSSIUMTS:  RSCPLTE:      RSRPNB-IoT: NRSRPFor more detailson Network Measurement Report, refer to theappropriate Cellular or Wireless Networkstandards. (e.g., for LTE Cellular Networkrefer to ETSI TS 36.133 specification).
    int RadioSignalStrength;
    
    // Optional resource
    // 3 - This contains received link quality  e.g. LQI for IEEE 802.15.4 (range 0..255), RxQual Downlink for GSM (range 0…7, refer to [3GPP 44.018] for more details on Network Measurement Report encoding), RSRQ for LTE, (refer to [3GPP 36.214]), NRSRQ for NB-IoT (refer to [3GPP 36.214]).
    int LinkQuality;
    
    // 4 - The IP addresses assigned to the connectivity interface. (e.g., IPv4, IPv6, etc.)
    IPAddressesType IPAddresses;
    
    // Optional resource
    // 5 - The IP address of the next-hop IP router, on each of the interfaces specified in resource 4 (IP Addresses).Note: This IP Address doesn’t indicate the Server IP address.
    RouterIPAddressesType RouterIPAddresses;
    
    // Optional resource
    // 6 - The average utilization of the link to the next-hop IP router in %.
    int LinkUtilization;
    
    // Optional resource
    // 7 - Access Point Name in case Network Bearer Resource is a Cellular Network.
    APNType APN;
    
    // Optional resource
    // 8 - Serving Cell ID in case Network Bearer Resource is a Cellular Network.As specified in TS [3GPP 23.003] and in [3GPP. 24.008]. Range (0…65535) in GSM/EDGEUTRAN Cell ID has a length of 28 bits.Cell Identity in WCDMA/TD-SCDMA. Range: (0..268435455).LTE Cell ID has a length of 28 bits.Parameter definitions in [3GPP 25.331].
    int CellID;
    
    // Optional resource
    // 9 - Serving Mobile Network Code. In case Network Bearer Resource has 0(cellular network). Range (0…999).As specified in TS [3GPP 23.003].
    int SMNC;
    
    // Optional resource
    // 10 - Serving Mobile Country Code. In case Network Bearer Resource has 0 (cellular network). Range (0…999).As specified in TS [3GPP 23.003].
    int SMCC;
    
};

enum class RESID {
    NetworkBearer = 0,
    AvailableNetworkBearer = 1,
    RadioSignalStrength = 2,
    LinkQuality = 3,
    IPAddresses = 4,
    RouterIPAddresses = 5,
    LinkUtilization = 6,
    APN = 7,
    CellID = 8,
    SMNC = 9,
    SMCC = 10,
    
};

/* \brief Class for object 4 - Connectivity Monitoring
 *  This LwM2M Object enables monitoring of parameters related to network connectivity.In
 *  this general connectivity Object, the Resources are limited to the most general cases
 *  common to most network bearers. It is recommended to read the description, which refers
 *  to relevant standard development organizations (e.g., 3GPP, IEEE).The goal of the
 *  Connectivity Monitoring Object is to carry information reflecting the more up to date
 *  values of the current connection for monitoring purposes. Resources such as Link Quality,
 *  Radio Signal Strength, Cell ID are retrieved during connected mode at least for cellular
 *  networks.
 */
class object : public Lwm2mObject<4, object, instance> {
public:

    // 0 - Indicates the network bearer used for the current LwM2M communication session from the below network bearer list.0~20 are Cellular Bearers0: GSM cellular network1: TD-SCDMA cellular network2: WCDMA cellular network3: CDMA2000 cellular network4: WiMAX cellular network5: LTE-TDD cellular network6: LTE-FDD cellular network7: NB-IoT8~20: Reserved for other type cellular network21~40 are Wireless Bearers21: WLAN network22: Bluetooth network23: IEEE 802.15.4 network24~40: Reserved for other type local wireless network41~50 are Wireline Bearers41: Ethernet42: DSL43: PLC44~50: reserved for others type wireline networks.
    Resource(0, &instance::NetworkBearer, O_RES_R) NetworkBearer;
    
    // 1 - Indicates list of current available network bearer. Each Resource Instance has a value from the network bearer list.
    Resource(1, &instance::AvailableNetworkBearer, O_RES_R) AvailableNetworkBearer;
    
    // 2 - This node contains the average value of thereceived signal strength indication used in thecurrent network bearer (as indicated byResource 0 of this Object). For the following network bearers the signal strength parameters indicated below are represented by this resource:GSM:    RSSIUMTS:  RSCPLTE:      RSRPNB-IoT: NRSRPFor more detailson Network Measurement Report, refer to theappropriate Cellular or Wireless Networkstandards. (e.g., for LTE Cellular Networkrefer to ETSI TS 36.133 specification).
    Resource(2, &instance::RadioSignalStrength, O_RES_R) RadioSignalStrength;
    
    // Optional resource
    // 3 - This contains received link quality  e.g. LQI for IEEE 802.15.4 (range 0..255), RxQual Downlink for GSM (range 0…7, refer to [3GPP 44.018] for more details on Network Measurement Report encoding), RSRQ for LTE, (refer to [3GPP 36.214]), NRSRQ for NB-IoT (refer to [3GPP 36.214]).
    Resource(3, &instance::LinkQuality, O_RES_R) LinkQuality;
    
    // 4 - The IP addresses assigned to the connectivity interface. (e.g., IPv4, IPv6, etc.)
    Resource(4, &instance::IPAddresses, O_RES_R) IPAddresses;
    
    // Optional resource
    // 5 - The IP address of the next-hop IP router, on each of the interfaces specified in resource 4 (IP Addresses).Note: This IP Address doesn’t indicate the Server IP address.
    Resource(5, &instance::RouterIPAddresses, O_RES_R) RouterIPAddresses;
    
    // Optional resource
    // 6 - The average utilization of the link to the next-hop IP router in %.
    Resource(6, &instance::LinkUtilization, O_RES_R) LinkUtilization;
    
    // Optional resource
    // 7 - Access Point Name in case Network Bearer Resource is a Cellular Network.
    Resource(7, &instance::APN, O_RES_R) APN;
    
    // Optional resource
    // 8 - Serving Cell ID in case Network Bearer Resource is a Cellular Network.As specified in TS [3GPP 23.003] and in [3GPP. 24.008]. Range (0…65535) in GSM/EDGEUTRAN Cell ID has a length of 28 bits.Cell Identity in WCDMA/TD-SCDMA. Range: (0..268435455).LTE Cell ID has a length of 28 bits.Parameter definitions in [3GPP 25.331].
    Resource(8, &instance::CellID, O_RES_R) CellID;
    
    // Optional resource
    // 9 - Serving Mobile Network Code. In case Network Bearer Resource has 0(cellular network). Range (0…999).As specified in TS [3GPP 23.003].
    Resource(9, &instance::SMNC, O_RES_R) SMNC;
    
    // Optional resource
    // 10 - Serving Mobile Country Code. In case Network Bearer Resource has 0 (cellular network). Range (0…999).As specified in TS [3GPP 23.003].
    Resource(10, &instance::SMCC, O_RES_R) SMCC;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id4::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id4::RESID c1) { return (uint16_t) c1 == c2; }
	