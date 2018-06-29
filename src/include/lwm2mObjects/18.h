#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id18 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 18 - Non-Access Stratum (NAS) configuration 
 *  This object provides Non-Access Stratum (NAS) configuration and is derived from 3GPP
 *  TS 24.368.
 */
class instance : public Lwm2mObjectInstance {
public:

    // Optional resource
    // 0 - Indicates a NAS signalling priority which is used to determine the setting of the low priority indicator to be included in NAS messages as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0=reserved1=NAS signalling low priority2-255=reserved
    int NASSignallingPriority;
    
    // Optional resource
    // 1 - Indicates whether attach with IMSI is performed when moving to a non-equivalent PLMN as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that normal behaviour is applied.1	Indicates that attach with IMSI is performed when moving to a non-equivalent PLMN.
    bool AttachWithIMSI;
    
    // Optional resource
    // 2 - Gives a minimum value in minutes for the timer T controlling the periodic search for higher prioritized PLMNs as specified in 3GPP TS 23.122 [3].
    int MinimumPeriodicSearchTimer;
    
    // Optional resource
    // 3 - Indicates whether the "NMO I, Network Mode of Operation I" indication as specified in 3GPP TS 24.008 [4] is applied by the UE.0	Indicates that the "NMO I, Network Mode of Operation I" indication is not used.1	Indicates that the "NMO I, Network Mode of Operation I" indication is used, if available.
    bool NMOIBehaviour;
    
    // Optional resource
    // 4 - Indicates whether the timer T3245 and the related functionality as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5] is used by the UE.0	Indicates that the timer T3245 is not used.1	Indicates that the timer T3245 is used.
    bool TimerT3245Behaviour;
    
    // Optional resource
    // 5 - Indicates whether the extended access barring is applicable for the UE as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the extended access barring is not applied for the UE.1	Indicates that the extended access barring is applied for the UE.
    bool ExtendedAccessBarring;
    
    // Optional resource
    // 6 - Indicates whether the UE can override the NAS_SignallingPriority leaf node configured to NAS signalling low priority.The setting of the low priority indicator included in NAS messages when this resource exists is specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the UE cannot override the NAS signalling low priority indicator1	Indicates that the UE can override the NAS signalling low priority indicatorThe default value 0 applies if this leaf is not provisioned.If provisioned, this resource is set to the same value as that provisioned for the Override_ExtendedAccessBarring leaf, e.g., if the UE is configured to override the NAS signalling low access priority indicator, then UE is also configured to override extended access class barring (see 3GPP TS 23.401 [5A]).
    bool OverrideNASSignallingLowPriority;
    
    // Optional resource
    // 7 - Indicates whether the UE can override ExtendedAccessBarring resource configured to extended access barring.The handling of extended access barring for the UE when this resource exists is specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the UE cannot override extended access barring1	Indicates that the UE can override extended access barringThe default value 0 applies if this resource is not provisioned.If provisioned, this resource is set to the same value as that provisioned for the Override_NAS_SignallingLowPriority leaf, e.g., if the UE is configured to override the NAS signalling low access priority indicator, then UE is also configured to override extended access class barring (see 3GPP TS 23.401 [5A]).
    bool OverrideExtendedAccessBarring;
    
    // Optional resource
    // 8 - Indicates whether the UE performs the first search for a higher priority PLMN after at least 2 minutes and at most T minutes upon entering a VPLMN as specified in 3GPP TS 23.122 [3].0	Indicates that the Fast First Higher Priority PLMN Search is disabled, see 3GPP TS 23.122 [3]1	Indicates that the Fast First Higher Priority PLMN Search is enabled, see 3GPP TS 23.122 [3]The default value 0 applies if this resource is not provisioned.
    bool FastFirstHigherPriorityPLMNSearch;
    
    // Optional resource
    // 9 - Indicates whether the UE is allowed to disable the E-UTRA capability when it receives the Extended EMM cause IE with value "E-UTRAN not allowed" as described in 3GPP TS 24.301 [5].0	Indicates that "E-UTRA Disabling for EMM cause #15" is disabled, see 3GPP TS 24.301 [5]1	Indicates that "E-UTRA Disabling for EMM cause #15" is enabled, see 3GPP TS 24.301 [5]The default value 0 applies if this resource is not provisioned.
    bool EUTRADisablingAllowedForEMMCause15;
    
    // Optional resource
    // 10 - Indicates a configured UE retry wait time value applicable when in HPLMN or EHPLMN (see 3GPP TS 23.122 [3]) for controlling the UE session management retry behaviour when prior session management request was rejected by the network with cause value #8, #27, #32, #33 as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]. The default value of 12 minutes applies if this resource is not provisioned.This resource shall be coded in the same format as the value part of GPRS Timer 3 IE as specified in Table 10.5.163a/3GPP TS 24.008 [4] converted into a decimal value.
    int SMRetryWaitTime;
    
    // Optional resource
    // 11 - Indicates the UE's retry behaviour when in HPLMN or EHPLMN (see 3GPP TS 23.122 [3]) after inter-system change between S1 mode and A/Gb or Iu mode as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]. 0	Indicates that the UE is allowed to retry the corresponding ESM procedure in S1 mode if an SM procedure was rejected in A/Gb or Iu mode, and to retry the corresponding SM procedure in A/Gb or Iu mode if an ESM procedure was rejected in S1 mode, see 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]1	Indicates that the UE is not allowed to retry an SM procedure or the corresponding ESM procedure in any of the modes: A/Gb, Iu and S1 mode, see 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]The default value 0 applies if this resource is not provisioned.
    bool SMRetryAtRATChange;
    
    // Optional resource
    // 12 - For the UE in NB-S1 mode, this resource indicates whether the UE is allowed to use the RRC establishment cause mo-ExceptionData, as specified in 3GPP TS 24.301 [5].0	Indicates that the UE is not allowed to use the RRC establishment cause mo-ExceptionData.1	Indicates that the UE is allowed to use the RRC establishment cause mo-ExceptionData.If this resource is not provisioned, the value of 0 is used.
    bool ExceptionDataReportingAllowed;
    
};

enum class RESID {
    NASSignallingPriority = 0,
    AttachWithIMSI = 1,
    MinimumPeriodicSearchTimer = 2,
    NMOIBehaviour = 3,
    TimerT3245Behaviour = 4,
    ExtendedAccessBarring = 5,
    OverrideNASSignallingLowPriority = 6,
    OverrideExtendedAccessBarring = 7,
    FastFirstHigherPriorityPLMNSearch = 8,
    EUTRADisablingAllowedForEMMCause15 = 9,
    SMRetryWaitTime = 10,
    SMRetryAtRATChange = 11,
    ExceptionDataReportingAllowed = 12,
    
};

/* \brief Class for object 18 - Non-Access Stratum (NAS) configuration 
 *  This object provides Non-Access Stratum (NAS) configuration and is derived from 3GPP
 *  TS 24.368.
 */
class object : public Lwm2mObject<18, object, instance> {
public:

    // Optional resource
    // 0 - Indicates a NAS signalling priority which is used to determine the setting of the low priority indicator to be included in NAS messages as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0=reserved1=NAS signalling low priority2-255=reserved
    Resource(0, &instance::NASSignallingPriority, O_RES_RW) NASSignallingPriority;
    
    // Optional resource
    // 1 - Indicates whether attach with IMSI is performed when moving to a non-equivalent PLMN as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that normal behaviour is applied.1	Indicates that attach with IMSI is performed when moving to a non-equivalent PLMN.
    Resource(1, &instance::AttachWithIMSI, O_RES_RW) AttachWithIMSI;
    
    // Optional resource
    // 2 - Gives a minimum value in minutes for the timer T controlling the periodic search for higher prioritized PLMNs as specified in 3GPP TS 23.122 [3].
    Resource(2, &instance::MinimumPeriodicSearchTimer, O_RES_RW) MinimumPeriodicSearchTimer;
    
    // Optional resource
    // 3 - Indicates whether the "NMO I, Network Mode of Operation I" indication as specified in 3GPP TS 24.008 [4] is applied by the UE.0	Indicates that the "NMO I, Network Mode of Operation I" indication is not used.1	Indicates that the "NMO I, Network Mode of Operation I" indication is used, if available.
    Resource(3, &instance::NMOIBehaviour, O_RES_RW) NMOIBehaviour;
    
    // Optional resource
    // 4 - Indicates whether the timer T3245 and the related functionality as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5] is used by the UE.0	Indicates that the timer T3245 is not used.1	Indicates that the timer T3245 is used.
    Resource(4, &instance::TimerT3245Behaviour, O_RES_RW) TimerT3245Behaviour;
    
    // Optional resource
    // 5 - Indicates whether the extended access barring is applicable for the UE as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the extended access barring is not applied for the UE.1	Indicates that the extended access barring is applied for the UE.
    Resource(5, &instance::ExtendedAccessBarring, O_RES_RW) ExtendedAccessBarring;
    
    // Optional resource
    // 6 - Indicates whether the UE can override the NAS_SignallingPriority leaf node configured to NAS signalling low priority.The setting of the low priority indicator included in NAS messages when this resource exists is specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the UE cannot override the NAS signalling low priority indicator1	Indicates that the UE can override the NAS signalling low priority indicatorThe default value 0 applies if this leaf is not provisioned.If provisioned, this resource is set to the same value as that provisioned for the Override_ExtendedAccessBarring leaf, e.g., if the UE is configured to override the NAS signalling low access priority indicator, then UE is also configured to override extended access class barring (see 3GPP TS 23.401 [5A]).
    Resource(6, &instance::OverrideNASSignallingLowPriority, O_RES_RW) OverrideNASSignallingLowPriority;
    
    // Optional resource
    // 7 - Indicates whether the UE can override ExtendedAccessBarring resource configured to extended access barring.The handling of extended access barring for the UE when this resource exists is specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5].0	Indicates that the UE cannot override extended access barring1	Indicates that the UE can override extended access barringThe default value 0 applies if this resource is not provisioned.If provisioned, this resource is set to the same value as that provisioned for the Override_NAS_SignallingLowPriority leaf, e.g., if the UE is configured to override the NAS signalling low access priority indicator, then UE is also configured to override extended access class barring (see 3GPP TS 23.401 [5A]).
    Resource(7, &instance::OverrideExtendedAccessBarring, O_RES_RW) OverrideExtendedAccessBarring;
    
    // Optional resource
    // 8 - Indicates whether the UE performs the first search for a higher priority PLMN after at least 2 minutes and at most T minutes upon entering a VPLMN as specified in 3GPP TS 23.122 [3].0	Indicates that the Fast First Higher Priority PLMN Search is disabled, see 3GPP TS 23.122 [3]1	Indicates that the Fast First Higher Priority PLMN Search is enabled, see 3GPP TS 23.122 [3]The default value 0 applies if this resource is not provisioned.
    Resource(8, &instance::FastFirstHigherPriorityPLMNSearch, O_RES_RW) FastFirstHigherPriorityPLMNSearch;
    
    // Optional resource
    // 9 - Indicates whether the UE is allowed to disable the E-UTRA capability when it receives the Extended EMM cause IE with value "E-UTRAN not allowed" as described in 3GPP TS 24.301 [5].0	Indicates that "E-UTRA Disabling for EMM cause #15" is disabled, see 3GPP TS 24.301 [5]1	Indicates that "E-UTRA Disabling for EMM cause #15" is enabled, see 3GPP TS 24.301 [5]The default value 0 applies if this resource is not provisioned.
    Resource(9, &instance::EUTRADisablingAllowedForEMMCause15, O_RES_RW) EUTRADisablingAllowedForEMMCause15;
    
    // Optional resource
    // 10 - Indicates a configured UE retry wait time value applicable when in HPLMN or EHPLMN (see 3GPP TS 23.122 [3]) for controlling the UE session management retry behaviour when prior session management request was rejected by the network with cause value #8, #27, #32, #33 as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]. The default value of 12 minutes applies if this resource is not provisioned.This resource shall be coded in the same format as the value part of GPRS Timer 3 IE as specified in Table 10.5.163a/3GPP TS 24.008 [4] converted into a decimal value.
    Resource(10, &instance::SMRetryWaitTime, O_RES_RW) SMRetryWaitTime;
    
    // Optional resource
    // 11 - Indicates the UE's retry behaviour when in HPLMN or EHPLMN (see 3GPP TS 23.122 [3]) after inter-system change between S1 mode and A/Gb or Iu mode as specified in 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]. 0	Indicates that the UE is allowed to retry the corresponding ESM procedure in S1 mode if an SM procedure was rejected in A/Gb or Iu mode, and to retry the corresponding SM procedure in A/Gb or Iu mode if an ESM procedure was rejected in S1 mode, see 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]1	Indicates that the UE is not allowed to retry an SM procedure or the corresponding ESM procedure in any of the modes: A/Gb, Iu and S1 mode, see 3GPP TS 24.008 [4] and 3GPP TS 24.301 [5]The default value 0 applies if this resource is not provisioned.
    Resource(11, &instance::SMRetryAtRATChange, O_RES_RW) SMRetryAtRATChange;
    
    // Optional resource
    // 12 - For the UE in NB-S1 mode, this resource indicates whether the UE is allowed to use the RRC establishment cause mo-ExceptionData, as specified in 3GPP TS 24.301 [5].0	Indicates that the UE is not allowed to use the RRC establishment cause mo-ExceptionData.1	Indicates that the UE is allowed to use the RRC establishment cause mo-ExceptionData.If this resource is not provisioned, the value of 0 is used.
    Resource(12, &instance::ExceptionDataReportingAllowed, O_RES_RW) ExceptionDataReportingAllowed;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id18::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id18::RESID c1) { return (uint16_t) c1 == c2; }
	