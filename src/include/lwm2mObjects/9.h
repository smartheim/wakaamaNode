#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id9 {
// Custom, overrideable types for Opaque and String resources

    #ifndef PkgName9
    class PkgNameType : public PreallocString<30> {};
    #endif
    
    #ifndef PkgVersion9
    class PkgVersionType : public PreallocString<30> {};
    #endif
    
    #ifndef Package9
    class PackageType : public Opaque<30> {};
    #endif
    
    #ifndef PackageURI9
    class PackageURIType : public PreallocString<30> {};
    #endif
    
    #ifndef UserName9
    class UserNameType : public PreallocString<30> {};
    #endif
    
    #ifndef Password9
    class PasswordType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 9 - LWM2M Software Management
 *  This LwM2M objects provides the resources needed to perform software management on
 *  the device. Each software component is managed via a dedicated Software Management
 *  Object instance.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Name of the software package
    PkgNameType PkgName;
    
    // 1 - Version of the software package
    PkgVersionType PkgVersion;
    
    // Optional resource
    // 2 - Software packageThe package can be in one single software component, or any delivery material used by the Device to determine the software component(s) and proceed to their installation.Can be archive file, executable, manifest. This resource to be used when it is single block of delivery.
    PackageType Package;
    
    // Optional resource
    // 3 - URI from where the device can download the software package by an alternative mechanism. As soon the device has received the Package URI it performs the download at the next practical opportunity.Can be direct link to a single software component or link to archive file, executable, or manifest, used by the Device to determine, then access to the software component(s). This resource to be used when it is single block of delivery.
    PackageURIType PackageURI;
    
    // 4 - Installs software from the package either stored in Package resource, or, downloaded from the Package URI. This Resource is only executable when the value of the State Resource is DELIVERED.
    Executable Install;

    // Optional resource
    // 5 - Link to a Checkpoint“ object which allows to specify conditions/dependencies for a software update. E.g. power connected, sufficient memory, target system.
    // Objlnk resources are not supported yet - Checkpoint;
    
    // 6 - Uninstalls the software package.This executable resource may have one argument.If used with no argument or argument is 0, the Package is removed i from the Device. If the argument is 1 (“ForUpdate”), the Client MUST prepare itself for receiving a Package used to upgrade the Software already in place. Update State is set back to INITIAL state.
    Executable Uninstall;

    // 7 - Indicates current state with respect to this software update. This value is set by the LwM2M Client.0: INITIALBefore downloading.(see 5.1.2.1)1: DOWNLOAD STARTEDThe downloading process has started and is on-going.(see 5.1.2.2)2: DOWNLOADEDThe package has been completely downloaded (see 5.1.2.3)3: DELIVEREDIn that state, the package has been correctly downloaded and is ready to be installed. (see 5.1.2.4)If executing the Install Resource failed, the state remains at DELIVERED.If executing the Install Resource was successful, the state changes from DELIVERED to INSTALLED.After executing the UnInstall Resource, the state changes to INITIAL.4: INSTALLEDIn that state the software is correctly installed and can be activated or deactivated according to the Activation State Machine.(see 5.1.2.5)
    int UpdateState;
    
    // Optional resource
    // 8 - If this value is true, the LwM2M Client MUST inform the registered LwM2M Servers of Objects and Object Instances parameter by sending an Update or Registration message after the software update operation at the next practical opportunity if supported Objects in the LwM2M Client have changed, in order for the LwM2M Servers to promptly manage newly installed Objects. If false, Objects and Object Instances parameter MUST be reported at the next periodic Update message.The default value is false.
    bool UpdateSupportedObjects;
    
    // 9 - Contains the result of downloading or installing/uninstalling the software0: Initial value. Prior to download any new package in the Device, Update Result MUST be reset to this initial value. One side effect of executing the Uninstall resource is to reset Update Result to this initial value “0”.1: Downloading. The package downloading process is on-going.2: Software successfully installed.3: Successfully Downloaded and package integrity verified(( 4-49, for expansion, of other scenarios))50: Not enough storage for the new software package.51: Out of memory during downloading process.52: Connection lost during downloading process.53: Package integrity check failure.54: Unsupported package type.56: Invalid URI57: Device defined update error58: Software installation failure59: Uninstallation Failure during forUpdate(arg=0)60-200 : (for expansion, selection to be in blocks depending on new introduction of features)This Resource MAY be reported by sending Observe operation.
    int UpdateResult;
    
    // 10 - This action activates the software previously successfully installed (the Package Installation State Machine is currently in the INSTALLED state)
    Executable Activate;

    // 11 - This action deactivates softwareif the Package Installation State Machine is currently in the INSTALLED state.
    Executable Deactivate;

    // 12 - Indicates the current activation state of this software:0: DISABLEDActivation State is DISABLED if the Software Activation State Machine is in the INACTIVE state or not alive.1: ENABLEDActivation State is ENABLED only if the Software Activation State Machine is in the ACTIVE state
    bool ActivationState;
    
    // Optional resource
    // 13 - Link to “Package Settings” object which allows to modify at any time software configuration settings. This is an application specific object. Note: OMA might provide a template for a Package Settings object in a future release of this specification.
    // Objlnk resources are not supported yet - PackageSettings;
    
    // Optional resource
    // 14 - User Name for access to SW Update Package in pull mode.Key based mechanism can alternatively use for talking to the component server instead of user name and password combination.
    UserNameType UserName;
    
    // Optional resource
    // 15 - Password for access to SW Update Package in pull mode.
    PasswordType Password;
    
};

enum class RESID {
    PkgName = 0,
    PkgVersion = 1,
    Package = 2,
    PackageURI = 3,
    Install = 4,
    Checkpoint = 5,
    Uninstall = 6,
    UpdateState = 7,
    UpdateSupportedObjects = 8,
    UpdateResult = 9,
    Activate = 10,
    Deactivate = 11,
    ActivationState = 12,
    PackageSettings = 13,
    UserName = 14,
    Password = 15,
    
};

/* \brief Class for object 9 - LWM2M Software Management
 *  This LwM2M objects provides the resources needed to perform software management on
 *  the device. Each software component is managed via a dedicated Software Management
 *  Object instance.
 */
class object : public Lwm2mObject<9, object, instance> {
public:

    // 0 - Name of the software package
    Resource(0, &instance::PkgName, O_RES_R) PkgName;
    
    // 1 - Version of the software package
    Resource(1, &instance::PkgVersion, O_RES_R) PkgVersion;
    
    // Optional resource
    // 2 - Software packageThe package can be in one single software component, or any delivery material used by the Device to determine the software component(s) and proceed to their installation.Can be archive file, executable, manifest. This resource to be used when it is single block of delivery.
    Resource(2, &instance::Package, O_RES_W) Package;
    
    // Optional resource
    // 3 - URI from where the device can download the software package by an alternative mechanism. As soon the device has received the Package URI it performs the download at the next practical opportunity.Can be direct link to a single software component or link to archive file, executable, or manifest, used by the Device to determine, then access to the software component(s). This resource to be used when it is single block of delivery.
    Resource(3, &instance::PackageURI, O_RES_W) PackageURI;
    
    // 4 - Installs software from the package either stored in Package resource, or, downloaded from the Package URI. This Resource is only executable when the value of the State Resource is DELIVERED.
    Resource(4, &instance::Install) Install;
    
    // Optional resource
    // 5 - Link to a Checkpoint“ object which allows to specify conditions/dependencies for a software update. E.g. power connected, sufficient memory, target system.
    // Objlnk resources are not supported yet - Checkpoint;
    
    // 6 - Uninstalls the software package.This executable resource may have one argument.If used with no argument or argument is 0, the Package is removed i from the Device. If the argument is 1 (“ForUpdate”), the Client MUST prepare itself for receiving a Package used to upgrade the Software already in place. Update State is set back to INITIAL state.
    Resource(6, &instance::Uninstall) Uninstall;
    
    // 7 - Indicates current state with respect to this software update. This value is set by the LwM2M Client.0: INITIALBefore downloading.(see 5.1.2.1)1: DOWNLOAD STARTEDThe downloading process has started and is on-going.(see 5.1.2.2)2: DOWNLOADEDThe package has been completely downloaded (see 5.1.2.3)3: DELIVEREDIn that state, the package has been correctly downloaded and is ready to be installed. (see 5.1.2.4)If executing the Install Resource failed, the state remains at DELIVERED.If executing the Install Resource was successful, the state changes from DELIVERED to INSTALLED.After executing the UnInstall Resource, the state changes to INITIAL.4: INSTALLEDIn that state the software is correctly installed and can be activated or deactivated according to the Activation State Machine.(see 5.1.2.5)
    Resource(7, &instance::UpdateState, O_RES_R) UpdateState;
    
    // Optional resource
    // 8 - If this value is true, the LwM2M Client MUST inform the registered LwM2M Servers of Objects and Object Instances parameter by sending an Update or Registration message after the software update operation at the next practical opportunity if supported Objects in the LwM2M Client have changed, in order for the LwM2M Servers to promptly manage newly installed Objects. If false, Objects and Object Instances parameter MUST be reported at the next periodic Update message.The default value is false.
    Resource(8, &instance::UpdateSupportedObjects, O_RES_RW) UpdateSupportedObjects;
    
    // 9 - Contains the result of downloading or installing/uninstalling the software0: Initial value. Prior to download any new package in the Device, Update Result MUST be reset to this initial value. One side effect of executing the Uninstall resource is to reset Update Result to this initial value “0”.1: Downloading. The package downloading process is on-going.2: Software successfully installed.3: Successfully Downloaded and package integrity verified(( 4-49, for expansion, of other scenarios))50: Not enough storage for the new software package.51: Out of memory during downloading process.52: Connection lost during downloading process.53: Package integrity check failure.54: Unsupported package type.56: Invalid URI57: Device defined update error58: Software installation failure59: Uninstallation Failure during forUpdate(arg=0)60-200 : (for expansion, selection to be in blocks depending on new introduction of features)This Resource MAY be reported by sending Observe operation.
    Resource(9, &instance::UpdateResult, O_RES_R) UpdateResult;
    
    // 10 - This action activates the software previously successfully installed (the Package Installation State Machine is currently in the INSTALLED state)
    Resource(10, &instance::Activate) Activate;
    
    // 11 - This action deactivates softwareif the Package Installation State Machine is currently in the INSTALLED state.
    Resource(11, &instance::Deactivate) Deactivate;
    
    // 12 - Indicates the current activation state of this software:0: DISABLEDActivation State is DISABLED if the Software Activation State Machine is in the INACTIVE state or not alive.1: ENABLEDActivation State is ENABLED only if the Software Activation State Machine is in the ACTIVE state
    Resource(12, &instance::ActivationState, O_RES_R) ActivationState;
    
    // Optional resource
    // 13 - Link to “Package Settings” object which allows to modify at any time software configuration settings. This is an application specific object. Note: OMA might provide a template for a Package Settings object in a future release of this specification.
    // Objlnk resources are not supported yet - PackageSettings;
    
    // Optional resource
    // 14 - User Name for access to SW Update Package in pull mode.Key based mechanism can alternatively use for talking to the component server instead of user name and password combination.
    Resource(14, &instance::UserName, O_RES_W) UserName;
    
    // Optional resource
    // 15 - Password for access to SW Update Package in pull mode.
    Resource(15, &instance::Password, O_RES_W) Password;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id9::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id9::RESID c1) { return (uint16_t) c1 == c2; }
	