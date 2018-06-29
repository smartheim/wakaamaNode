#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id12 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Interfacename12
    class InterfacenameType : public PreallocString<30> {};
    #endif
    
    #ifndef BSSID12
    class BSSIDType : public PreallocString<30> {};
    #endif
    
    #ifndef SSID12
    class SSIDType : public PreallocString<30> {};
    #endif
    
    #ifndef RegulatoryDomain12
    class RegulatoryDomainType : public PreallocString<30> {};
    #endif
    
    #ifndef WPAPreSharedKey12
    class WPAPreSharedKeyType : public PreallocString<30> {};
    #endif
    
    #ifndef WPAKeyPhrase12
    class WPAKeyPhraseType : public PreallocString<30> {};
    #endif
    
    #ifndef WEPKeyPhrase12
    class WEPKeyPhraseType : public PreallocString<30> {};
    #endif
    
    #ifndef WEPKey112
    class WEPKey1Type : public PreallocString<30> {};
    #endif
    
    #ifndef WEPKey212
    class WEPKey2Type : public PreallocString<30> {};
    #endif
    
    #ifndef WEPKey312
    class WEPKey3Type : public PreallocString<30> {};
    #endif
    
    #ifndef WEPKey412
    class WEPKey4Type : public PreallocString<30> {};
    #endif
    
    #ifndef RADIUSServer12
    class RADIUSServerType : public PreallocString<30> {};
    #endif
    
    #ifndef RADIUSSecret12
    class RADIUSSecretType : public PreallocString<30> {};
    #endif
    
    #ifndef MACAddressList12
    class MACAddressListType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 12 - WLAN connectivity
 *  This object specifies resources to enable a device to connect to a WLAN bearer.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Human-readable identifiereg. wlan0
    InterfacenameType Interfacename;
    
    // 1 - 0: Disabled1: EnabledEnable / Disable interfaceWhen disabled radio must also be disabled
    bool Enable;
    
    // Optional resource
    // 2 - 0: Disabled1: 2.4 GHz2: 5 GHz3: 0.9 GHz4: 3.7 GHz5: 45 GHz6: 60 GHz
    int RadioEnabled;
    
    // 3 - 0: Disabled1: UP (OK)2: Error
    int Status;
    
    // 4 - The MAC address of the interface, in hexadecimal form.
    BSSIDType BSSID;
    
    // 5 - The Service Set Identifier for this interface.
    SSIDType SSID;
    
    // Optional resource
    // 6 - 0: Do not broadcast SSID1: Broadcast SSID
    bool BroadcastSSID;
    
    // Optional resource
    // 7 - 0: Do not broadcast beacons1: Broadcast beacons
    bool BeaconEnabled;
    
    // 8 - 0: Access Point1: Client (Station)2: Bridge3: Repeater
    int Mode;
    
    // 9 - The current radio channel in use by this interface.0: Disabled1: Enabled
    int Channel;
    
    // Optional resource
    // 10 - 0: Disabled1: Enabled
    bool AutoChannel;
    
    // Optional resource
    // 11 - Array of supported radio channels.
    int SupportedChannels;
    
    // Optional resource
    // 12 - Array of channels which the access point has determined are ‘in use’.Including any channels in-use by access point itself.
    int ChannelsInUse;
    
    // Optional resource
    // 13 - 802.11d Regulatory Domain String. First two octets are ISO/IEC 3166-1 two-character country code. The third octet is either “ ” (all environments), “O” (outside) or “I” (inside).
    RegulatoryDomainType RegulatoryDomain;
    
    // 14 - 0: 802.11a1: 802.11b2: 802.11bg 3: 802.11g4: 802.11n5: 802.11bgn6: 802.11ac7: 802.11ah
    int Standard;
    
    // 15 - 0: None (Open)1: PSK2: EAP3: EAP+PSK4: EAPSIM
    int AuthenticationMode;
    
    // Optional resource
    // 16 - 0: AES (WPA2)1: TKIP (WPA)2: WEP (1)
    int EncryptionMode;
    
    // Optional resource
    // 17 - WPA/WPA2 Key expressed as a hex string.Write – Only.
    WPAPreSharedKeyType WPAPreSharedKey;
    
    // Optional resource
    // 18 - WPA/WPA2 Key Phrase.Write Only.
    WPAKeyPhraseType WPAKeyPhrase;
    
    // Optional resource
    // 19 - Description.0: None1: 40-bit2: 104-bit
    int WEPEncryptionType;
    
    // Optional resource
    // 20 - Index of the default WEP key.
    int WEPKeyIndex;
    
    // Optional resource
    // 21 - WPA/WPA2 Key Phrase.Write Only.
    WEPKeyPhraseType WEPKeyPhrase;
    
    // Optional resource
    // 22 - WEP Key 1 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    WEPKey1Type WEPKey1;
    
    // Optional resource
    // 23 - WEP Key 2 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    WEPKey2Type WEPKey2;
    
    // Optional resource
    // 24 - WEP Key 3 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    WEPKey3Type WEPKey3;
    
    // Optional resource
    // 25 - WEP Key 4 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    WEPKey4Type WEPKey4;
    
    // Optional resource
    // 26 - RADIUS Authentication Server Address
    RADIUSServerType RADIUSServer;
    
    // Optional resource
    // 27 - RADIUS Authentication Server Port Number
    int RADIUSServerPort;
    
    // Optional resource
    // 28 - RADIUS Shared Secret
    RADIUSSecretType RADIUSSecret;
    
    // Optional resource
    // 29 - 0: WMM NOT Supported1: WMM Wupported
    bool WMMSupported;
    
    // Optional resource
    // 30 - 0: Disabled1: Enabled
    bool WMMEnabled;
    
    // Optional resource
    // 31 - 0: Any Client MAC Address accepted1: Client MAC address must exist in MACAddressList
    bool MACControlEnabled;
    
    // Optional resource
    // 32 - Array of allowed client MAC addresses, in hexadecimal form.
    MACAddressListType MACAddressList;
    
    // Optional resource
    // 33 - Total number of bytes sent via this interface
    int TotalBytesSent;
    
    // Optional resource
    // 34 - Total number of bytes received via this interface
    int TotalBytesReceived;
    
    // Optional resource
    // 35 - Total packets sent via this interface
    int TotalPacketsSent;
    
    // Optional resource
    // 36 - Total packets received via this interface
    int TotalPacketsReceived;
    
    // Optional resource
    // 37 - Total number of packets which could not be transmitted because of errors.
    int TransmitErrors;
    
    // Optional resource
    // 38 - Total number of packets received with errors which prevented those packets from being delivered.
    int ReceiveErrors;
    
    // Optional resource
    // 39 - Count of Unicast Packets Sent
    int UnicastPacketsSent;
    
    // Optional resource
    // 40 - Count of Unicast Packets Received
    int UnicastPacketsReceived;
    
    // Optional resource
    // 41 - Count of Multicast Packets Sent
    int MulticastPacketsSend;
    
    // Optional resource
    // 42 - Count of Multicast Packets Received
    int MulticastPacketsReceived;
    
    // Optional resource
    // 43 - Count of Broadcast Packets Sent
    int BroadcastPacketsSent;
    
    // Optional resource
    // 44 - Count of Broadcast Packets Received
    int BroadcastPacketsReceived;
    
    // Optional resource
    // 45 - Count of valid outbound packets intentionally discarded without transmission, for example a packet may be discarded to manage buffer space.
    int DiscardPacketsSent;
    
    // Optional resource
    // 46 - Count of valid packets received and intentionally discarded without delivery to the system, for example a packet may be discarded to manage buffer space.
    int DiscardPacketsReceived;
    
    // Optional resource
    // 47 - Count of Unknown Packets Received
    int UnknownPacketsReceived;
    
    // Optional resource
    // 48 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
};

enum class RESID {
    Interfacename = 0,
    Enable = 1,
    RadioEnabled = 2,
    Status = 3,
    BSSID = 4,
    SSID = 5,
    BroadcastSSID = 6,
    BeaconEnabled = 7,
    Mode = 8,
    Channel = 9,
    AutoChannel = 10,
    SupportedChannels = 11,
    ChannelsInUse = 12,
    RegulatoryDomain = 13,
    Standard = 14,
    AuthenticationMode = 15,
    EncryptionMode = 16,
    WPAPreSharedKey = 17,
    WPAKeyPhrase = 18,
    WEPEncryptionType = 19,
    WEPKeyIndex = 20,
    WEPKeyPhrase = 21,
    WEPKey1 = 22,
    WEPKey2 = 23,
    WEPKey3 = 24,
    WEPKey4 = 25,
    RADIUSServer = 26,
    RADIUSServerPort = 27,
    RADIUSSecret = 28,
    WMMSupported = 29,
    WMMEnabled = 30,
    MACControlEnabled = 31,
    MACAddressList = 32,
    TotalBytesSent = 33,
    TotalBytesReceived = 34,
    TotalPacketsSent = 35,
    TotalPacketsReceived = 36,
    TransmitErrors = 37,
    ReceiveErrors = 38,
    UnicastPacketsSent = 39,
    UnicastPacketsReceived = 40,
    MulticastPacketsSend = 41,
    MulticastPacketsReceived = 42,
    BroadcastPacketsSent = 43,
    BroadcastPacketsReceived = 44,
    DiscardPacketsSent = 45,
    DiscardPacketsReceived = 46,
    UnknownPacketsReceived = 47,
    Vendorspecificextensions = 48,
    
};

/* \brief Class for object 12 - WLAN connectivity
 *  This object specifies resources to enable a device to connect to a WLAN bearer.
 */
class object : public Lwm2mObject<12, object, instance> {
public:

    // 0 - Human-readable identifiereg. wlan0
    Resource(0, &instance::Interfacename, O_RES_RW) Interfacename;
    
    // 1 - 0: Disabled1: EnabledEnable / Disable interfaceWhen disabled radio must also be disabled
    Resource(1, &instance::Enable, O_RES_RW) Enable;
    
    // Optional resource
    // 2 - 0: Disabled1: 2.4 GHz2: 5 GHz3: 0.9 GHz4: 3.7 GHz5: 45 GHz6: 60 GHz
    Resource(2, &instance::RadioEnabled, O_RES_RW) RadioEnabled;
    
    // 3 - 0: Disabled1: UP (OK)2: Error
    Resource(3, &instance::Status, O_RES_R) Status;
    
    // 4 - The MAC address of the interface, in hexadecimal form.
    Resource(4, &instance::BSSID, O_RES_R) BSSID;
    
    // 5 - The Service Set Identifier for this interface.
    Resource(5, &instance::SSID, O_RES_RW) SSID;
    
    // Optional resource
    // 6 - 0: Do not broadcast SSID1: Broadcast SSID
    Resource(6, &instance::BroadcastSSID, O_RES_RW) BroadcastSSID;
    
    // Optional resource
    // 7 - 0: Do not broadcast beacons1: Broadcast beacons
    Resource(7, &instance::BeaconEnabled, O_RES_RW) BeaconEnabled;
    
    // 8 - 0: Access Point1: Client (Station)2: Bridge3: Repeater
    Resource(8, &instance::Mode, O_RES_RW) Mode;
    
    // 9 - The current radio channel in use by this interface.0: Disabled1: Enabled
    Resource(9, &instance::Channel, O_RES_RW) Channel;
    
    // Optional resource
    // 10 - 0: Disabled1: Enabled
    Resource(10, &instance::AutoChannel, O_RES_RW) AutoChannel;
    
    // Optional resource
    // 11 - Array of supported radio channels.
    Resource(11, &instance::SupportedChannels, O_RES_RW) SupportedChannels;
    
    // Optional resource
    // 12 - Array of channels which the access point has determined are ‘in use’.Including any channels in-use by access point itself.
    Resource(12, &instance::ChannelsInUse, O_RES_RW) ChannelsInUse;
    
    // Optional resource
    // 13 - 802.11d Regulatory Domain String. First two octets are ISO/IEC 3166-1 two-character country code. The third octet is either “ ” (all environments), “O” (outside) or “I” (inside).
    Resource(13, &instance::RegulatoryDomain, O_RES_RW) RegulatoryDomain;
    
    // 14 - 0: 802.11a1: 802.11b2: 802.11bg 3: 802.11g4: 802.11n5: 802.11bgn6: 802.11ac7: 802.11ah
    Resource(14, &instance::Standard, O_RES_RW) Standard;
    
    // 15 - 0: None (Open)1: PSK2: EAP3: EAP+PSK4: EAPSIM
    Resource(15, &instance::AuthenticationMode, O_RES_RW) AuthenticationMode;
    
    // Optional resource
    // 16 - 0: AES (WPA2)1: TKIP (WPA)2: WEP (1)
    Resource(16, &instance::EncryptionMode, O_RES_RW) EncryptionMode;
    
    // Optional resource
    // 17 - WPA/WPA2 Key expressed as a hex string.Write – Only.
    Resource(17, &instance::WPAPreSharedKey, O_RES_W) WPAPreSharedKey;
    
    // Optional resource
    // 18 - WPA/WPA2 Key Phrase.Write Only.
    Resource(18, &instance::WPAKeyPhrase, O_RES_W) WPAKeyPhrase;
    
    // Optional resource
    // 19 - Description.0: None1: 40-bit2: 104-bit
    Resource(19, &instance::WEPEncryptionType, O_RES_RW) WEPEncryptionType;
    
    // Optional resource
    // 20 - Index of the default WEP key.
    Resource(20, &instance::WEPKeyIndex, O_RES_RW) WEPKeyIndex;
    
    // Optional resource
    // 21 - WPA/WPA2 Key Phrase.Write Only.
    Resource(21, &instance::WEPKeyPhrase, O_RES_W) WEPKeyPhrase;
    
    // Optional resource
    // 22 - WEP Key 1 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    Resource(22, &instance::WEPKey1, O_RES_W) WEPKey1;
    
    // Optional resource
    // 23 - WEP Key 2 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    Resource(23, &instance::WEPKey2, O_RES_W) WEPKey2;
    
    // Optional resource
    // 24 - WEP Key 3 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    Resource(24, &instance::WEPKey3, O_RES_W) WEPKey3;
    
    // Optional resource
    // 25 - WEP Key 4 expressed as a hexadecimal string.10 Bytes for a 40 Bit key26 Bytes for a 104 Bit key
    Resource(25, &instance::WEPKey4, O_RES_W) WEPKey4;
    
    // Optional resource
    // 26 - RADIUS Authentication Server Address
    Resource(26, &instance::RADIUSServer, O_RES_RW) RADIUSServer;
    
    // Optional resource
    // 27 - RADIUS Authentication Server Port Number
    Resource(27, &instance::RADIUSServerPort, O_RES_RW) RADIUSServerPort;
    
    // Optional resource
    // 28 - RADIUS Shared Secret
    Resource(28, &instance::RADIUSSecret, O_RES_W) RADIUSSecret;
    
    // Optional resource
    // 29 - 0: WMM NOT Supported1: WMM Wupported
    Resource(29, &instance::WMMSupported, O_RES_R) WMMSupported;
    
    // Optional resource
    // 30 - 0: Disabled1: Enabled
    Resource(30, &instance::WMMEnabled, O_RES_RW) WMMEnabled;
    
    // Optional resource
    // 31 - 0: Any Client MAC Address accepted1: Client MAC address must exist in MACAddressList
    Resource(31, &instance::MACControlEnabled, O_RES_RW) MACControlEnabled;
    
    // Optional resource
    // 32 - Array of allowed client MAC addresses, in hexadecimal form.
    Resource(32, &instance::MACAddressList, O_RES_RW) MACAddressList;
    
    // Optional resource
    // 33 - Total number of bytes sent via this interface
    Resource(33, &instance::TotalBytesSent, O_RES_R) TotalBytesSent;
    
    // Optional resource
    // 34 - Total number of bytes received via this interface
    Resource(34, &instance::TotalBytesReceived, O_RES_R) TotalBytesReceived;
    
    // Optional resource
    // 35 - Total packets sent via this interface
    Resource(35, &instance::TotalPacketsSent, O_RES_R) TotalPacketsSent;
    
    // Optional resource
    // 36 - Total packets received via this interface
    Resource(36, &instance::TotalPacketsReceived, O_RES_R) TotalPacketsReceived;
    
    // Optional resource
    // 37 - Total number of packets which could not be transmitted because of errors.
    Resource(37, &instance::TransmitErrors, O_RES_R) TransmitErrors;
    
    // Optional resource
    // 38 - Total number of packets received with errors which prevented those packets from being delivered.
    Resource(38, &instance::ReceiveErrors, O_RES_R) ReceiveErrors;
    
    // Optional resource
    // 39 - Count of Unicast Packets Sent
    Resource(39, &instance::UnicastPacketsSent, O_RES_R) UnicastPacketsSent;
    
    // Optional resource
    // 40 - Count of Unicast Packets Received
    Resource(40, &instance::UnicastPacketsReceived, O_RES_R) UnicastPacketsReceived;
    
    // Optional resource
    // 41 - Count of Multicast Packets Sent
    Resource(41, &instance::MulticastPacketsSend, O_RES_R) MulticastPacketsSend;
    
    // Optional resource
    // 42 - Count of Multicast Packets Received
    Resource(42, &instance::MulticastPacketsReceived, O_RES_R) MulticastPacketsReceived;
    
    // Optional resource
    // 43 - Count of Broadcast Packets Sent
    Resource(43, &instance::BroadcastPacketsSent, O_RES_R) BroadcastPacketsSent;
    
    // Optional resource
    // 44 - Count of Broadcast Packets Received
    Resource(44, &instance::BroadcastPacketsReceived, O_RES_R) BroadcastPacketsReceived;
    
    // Optional resource
    // 45 - Count of valid outbound packets intentionally discarded without transmission, for example a packet may be discarded to manage buffer space.
    Resource(45, &instance::DiscardPacketsSent, O_RES_R) DiscardPacketsSent;
    
    // Optional resource
    // 46 - Count of valid packets received and intentionally discarded without delivery to the system, for example a packet may be discarded to manage buffer space.
    Resource(46, &instance::DiscardPacketsReceived, O_RES_R) DiscardPacketsReceived;
    
    // Optional resource
    // 47 - Count of Unknown Packets Received
    Resource(47, &instance::UnknownPacketsReceived, O_RES_R) UnknownPacketsReceived;
    
    // Optional resource
    // 48 - Links to a vendor specific object.
    // Objlnk resources are not supported yet - Vendorspecificextensions;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id12::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id12::RESID c1) { return (uint16_t) c1 == c2; }
	