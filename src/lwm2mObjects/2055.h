#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id2055 {
/* \brief Class for object 2055 - CmdhNwAccessRule
 *  This Object defines limits in usage of specific underlying networks for forwarding
 *  information to other CSEs during processing of CMDH-related requests in a CSE.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Contains identifiers of Underlying networks
    PreallocString<30> TargetNetwork;
    
    // 1 - Contains a value in ms such that before accessing the underlying network (typically to forward an incoming request), the CSE will wait for an additional amount of time randomly chosen between 0 and this value
    int SpreadingWaitTime;
    
    // 2 - Minimum amount of data that needs to be aggregated before any of the Underlying Networks matching with the targetNetwork Resource of the current Instance of the  CmdhNwAccessRule Object can be used for forwarding information to other CSEs.
    int MinReqVolume;
    
    // 3 - Reference to an Instance of BackOffParameterSet Object defining parameters that define how usage of any of the Underlying Networks matching with the targetNetwork Resource  of that Object Instance, shall be handled when attempts to use such networks have failed.
    // Objlnk resources are not supported yet - BackOffParameters;
    
    // 4 - List of additional conditions that need to be fulfilled before any of the Underlying Networks matching with the TargetNetwork Resource of this CmdhNwAccessRule Object Instance can be used for forwarding information to other CSEs. 
    PreallocString<30> OtherConditions;
    
    // 5 - Contains time schedules in form of extended crontab syntax defined in oneM2M Protocol TS-0004 
    PreallocString<30> AllowedSchedule;
    
    enum class RESID {
        TargetNetwork = 0,
        SpreadingWaitTime = 1,
        MinReqVolume = 2,
        BackOffParameters = 3,
        OtherConditions = 4,
        AllowedSchedule = 5,
        
    };
};

/* \brief Class for object 2055 - CmdhNwAccessRule
 *  This Object defines limits in usage of specific underlying networks for forwarding
 *  information to other CSEs during processing of CMDH-related requests in a CSE.
 */
class object : public Lwm2mObject<2055, object, instance> {
public:

    // 0 - Contains identifiers of Underlying networks
    Resource(0, &instance::TargetNetwork, O_RES_RW) TargetNetwork;
    
    // 1 - Contains a value in ms such that before accessing the underlying network (typically to forward an incoming request), the CSE will wait for an additional amount of time randomly chosen between 0 and this value
    Resource(1, &instance::SpreadingWaitTime, O_RES_RW) SpreadingWaitTime;
    
    // 2 - Minimum amount of data that needs to be aggregated before any of the Underlying Networks matching with the targetNetwork Resource of the current Instance of the  CmdhNwAccessRule Object can be used for forwarding information to other CSEs.
    Resource(2, &instance::MinReqVolume, O_RES_RW) MinReqVolume;
    
    // 3 - Reference to an Instance of BackOffParameterSet Object defining parameters that define how usage of any of the Underlying Networks matching with the targetNetwork Resource  of that Object Instance, shall be handled when attempts to use such networks have failed.
    // Objlnk resources are not supported yet - BackOffParameters;
    
    // 4 - List of additional conditions that need to be fulfilled before any of the Underlying Networks matching with the TargetNetwork Resource of this CmdhNwAccessRule Object Instance can be used for forwarding information to other CSEs. 
    Resource(4, &instance::OtherConditions, O_RES_RW) OtherConditions;
    
    // 5 - Contains time schedules in form of extended crontab syntax defined in oneM2M Protocol TS-0004 
    Resource(5, &instance::AllowedSchedule, O_RES_RW) AllowedSchedule;
    
};

} // end of id namespace
inline bool operator== (id2055::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id2055::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	