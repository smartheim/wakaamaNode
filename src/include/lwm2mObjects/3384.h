#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3384 {
// Custom, overrideable types for Opaque and String resources


/* \brief Class for object 3384 - sipSubscriptionEvent
 *  SIP Subscription status
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - -obtained header of the SUBSCRIBE1 = Registration2 = Presence3 = Conference4 = Dialog5 = Call-info
    int eventType;
    
    // 1 - -1 = Event subscription message not available0 = Success (when 200 OK received is followed by NOTIFY, and applies to all Event Types)1 = Failure (when any error other than 401 is received; else when 408 timeout occurs)
    int subscriptionResult;
    
};

enum class RESID {
    eventType = 0,
    subscriptionResult = 1,
    
};

/* \brief Class for object 3384 - sipSubscriptionEvent
 *  SIP Subscription status
 */
class object : public Lwm2mObject<3384, object, instance> {
public:

    // 0 - -obtained header of the SUBSCRIBE1 = Registration2 = Presence3 = Conference4 = Dialog5 = Call-info
    Resource(0, &instance::eventType, O_RES_R) eventType;
    
    // 1 - -1 = Event subscription message not available0 = Success (when 200 OK received is followed by NOTIFY, and applies to all Event Types)1 = Failure (when any error other than 401 is received; else when 408 timeout occurs)
    Resource(1, &instance::subscriptionResult, O_RES_R) subscriptionResult;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3384::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3384::RESID c1) { return (uint16_t) c1 == c2; }
	