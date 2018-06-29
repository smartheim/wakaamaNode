#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3361 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3361 - emmStateValue
 *  EMM context information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - 1 = EmmNull2 = EmmDeregistered3 = EmmRegisteredInitiated4 = EmmRegistered5 = EmmTrackingAreaUpdatingInitiated6 = EmmServiceRequestInitiated7 = EmmDeregisteredInitiated
    int EmmState;
    
    // 1 -  -- If EMM state is EmmDeregistered(2), EMM sub-state    -- EmmDeregisteredNoImsi(1)    -- EmmDeregisteredPlmnSearch(2)    -- EmmDeregisteredAttachNeeded(3)    -- EmmDeregisteredNoCellAvailable(4)    -- EmmDeregisteredAttemptingToAttach(5)    -- EmmDeregisteredNormalService(6)    -- EmmDeregisteredLimitedService(7)    -- If EMM state is EmmRegistered(4), EMM sub-state    -- EmmRegisteredNormalService(1)    -- EmmRegisteredUpdateNeeded(2)    -- EmmRegisteredAttemptingToUpdate(3)    -- EmmRegisteredNoCellAvailable(4)    -- EmmRegisteredPlmnSearch(5)    -- EmmRegisteredLimitedService(6)    -- EmmRegisteredImsiDetachInitiated(7)    -- EmmRegisteredAttemptingToUpdateMm(8)    -- Others use invalid EMM Substate value (0)
    int emmSubstate;
    
};

enum class RESID {
    EmmState = 0,
    emmSubstate = 1,
    
};

/* \brief Class for object 3361 - emmStateValue
 *  EMM context information
 */
class object : public Lwm2mObject<3361, object, instance> {
public:

    // 0 - 1 = EmmNull2 = EmmDeregistered3 = EmmRegisteredInitiated4 = EmmRegistered5 = EmmTrackingAreaUpdatingInitiated6 = EmmServiceRequestInitiated7 = EmmDeregisteredInitiated
    Resource(0, &instance::EmmState, O_RES_R) EmmState;
    
    // 1 -  -- If EMM state is EmmDeregistered(2), EMM sub-state    -- EmmDeregisteredNoImsi(1)    -- EmmDeregisteredPlmnSearch(2)    -- EmmDeregisteredAttachNeeded(3)    -- EmmDeregisteredNoCellAvailable(4)    -- EmmDeregisteredAttemptingToAttach(5)    -- EmmDeregisteredNormalService(6)    -- EmmDeregisteredLimitedService(7)    -- If EMM state is EmmRegistered(4), EMM sub-state    -- EmmRegisteredNormalService(1)    -- EmmRegisteredUpdateNeeded(2)    -- EmmRegisteredAttemptingToUpdate(3)    -- EmmRegisteredNoCellAvailable(4)    -- EmmRegisteredPlmnSearch(5)    -- EmmRegisteredLimitedService(6)    -- EmmRegisteredImsiDetachInitiated(7)    -- EmmRegisteredAttemptingToUpdateMm(8)    -- Others use invalid EMM Substate value (0)
    Resource(1, &instance::emmSubstate, O_RES_R) emmSubstate;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3361::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3361::RESID c1) { return (uint16_t) c1 == c2; }
	