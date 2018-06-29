#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10252 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Manifest10252
    class ManifestType : public Opaque<30> {};
    #endif
    
    #ifndef PayloadResult10252
    class PayloadResultType : public Opaque<30> {};
    #endif
    
    #ifndef AssetHash10252
    class AssetHashType : public Opaque<30> {};
    #endif
    
    #ifndef CampaignId10252
    class CampaignIdType : public PreallocString<30> {};
    #endif
    
    #ifndef ManualTrigger10252
    class ManualTriggerType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10252 - Manifest
 *  This object provides a range of information related to updating packages on a device
 */
class instance : public Lwm2mObjectInstance {
public:

    // 1 - Content of a new manifest
    ManifestType Manifest;
    
    // 2 - Current state of manifest processing0.	Uninitialised1.	Idle2.	Processing manifest3.	Awaiting download approval4.	Downloading 5.	Downloaded6.	Awaiting application approval7.	Updating8.	Rebooting
    int State;
    
    // 3 - Final result of the device processing a manifest.0.	Uninitialised1.	Success2.	Manifest timeout. The Manifest URI has timed-out.3.	Manifest not found. The Manifest URI not found.4.	Manifest failed integrity check. The manifest integrity check failed. 5.	Manifest rejected. The Manifest attributes do not apply to this device.6.	Manifest certificate not found7.	Manifest signature failed. The Manifest signature is not recognised by this device.8.	Dependent manifest not found9.	Not enough storage for the new asset10.	Out of memory during download process11.	Connection lost during download process12.	Asset failed integrity check13.	Unsupported asset type14.	Invalid asset URI15.	Timed out downloading asset16.	Unsupported delta format17.	Unsupported encryption format18.	Asset update successfully completed19.	Asset updated successfully after recovery
    int ManifestResult;
    
    // 4 - Contains payload-specific errors or output.
    PayloadResultType PayloadResult;
    
    // 5 - Hash of the installed asset.
    AssetHashType AssetHash;
    
    // 6 - Version of the current manifest.
    int Manifestversion;
    
    // 7 - Progress update of the asset installation process (in bytes).
    int AssetInstallationProgress;
    
    // 8 - Id of campaign affecting this device. There currently isn’t any logic on the server or the client to handle this. 
    CampaignIdType CampaignId;
    
    // 9 - Manually apply the asset update. This will only have effect if the manifest requires this. The state resource must also be in the downloaded state for the execute command to be actioned.
    Executable ManualTrigger;

};

enum class RESID {
    Manifest = 1,
    State = 2,
    ManifestResult = 3,
    PayloadResult = 4,
    AssetHash = 5,
    Manifestversion = 6,
    AssetInstallationProgress = 7,
    CampaignId = 8,
    ManualTrigger = 9,
    
};

/* \brief Class for object 10252 - Manifest
 *  This object provides a range of information related to updating packages on a device
 */
class object : public Lwm2mObject<10252, object, instance> {
public:

    // 1 - Content of a new manifest
    Resource(1, &instance::Manifest, O_RES_W) Manifest;
    
    // 2 - Current state of manifest processing0.	Uninitialised1.	Idle2.	Processing manifest3.	Awaiting download approval4.	Downloading 5.	Downloaded6.	Awaiting application approval7.	Updating8.	Rebooting
    Resource(2, &instance::State, O_RES_R) State;
    
    // 3 - Final result of the device processing a manifest.0.	Uninitialised1.	Success2.	Manifest timeout. The Manifest URI has timed-out.3.	Manifest not found. The Manifest URI not found.4.	Manifest failed integrity check. The manifest integrity check failed. 5.	Manifest rejected. The Manifest attributes do not apply to this device.6.	Manifest certificate not found7.	Manifest signature failed. The Manifest signature is not recognised by this device.8.	Dependent manifest not found9.	Not enough storage for the new asset10.	Out of memory during download process11.	Connection lost during download process12.	Asset failed integrity check13.	Unsupported asset type14.	Invalid asset URI15.	Timed out downloading asset16.	Unsupported delta format17.	Unsupported encryption format18.	Asset update successfully completed19.	Asset updated successfully after recovery
    Resource(3, &instance::ManifestResult, O_RES_R) ManifestResult;
    
    // 4 - Contains payload-specific errors or output.
    Resource(4, &instance::PayloadResult, O_RES_R) PayloadResult;
    
    // 5 - Hash of the installed asset.
    Resource(5, &instance::AssetHash, O_RES_R) AssetHash;
    
    // 6 - Version of the current manifest.
    Resource(6, &instance::Manifestversion, O_RES_R) Manifestversion;
    
    // 7 - Progress update of the asset installation process (in bytes).
    Resource(7, &instance::AssetInstallationProgress, O_RES_R) AssetInstallationProgress;
    
    // 8 - Id of campaign affecting this device. There currently isn’t any logic on the server or the client to handle this. 
    Resource(8, &instance::CampaignId, O_RES_RW) CampaignId;
    
    // 9 - Manually apply the asset update. This will only have effect if the manifest requires this. The state resource must also be in the downloaded state for the execute command to be actioned.
    Resource(9, &instance::ManualTrigger) ManualTrigger;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10252::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10252::RESID c1) { return (uint16_t) c1 == c2; }
	