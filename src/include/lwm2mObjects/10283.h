#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10283 {
// Custom, overrideable types for Opaque and String resources

    #ifndef LatestDeliveredEventTime10283
    class LatestDeliveredEventTimeType : public PreallocString<30> {};
    #endif
    
    #ifndef LatestRecordedEventTime10283
    class LatestRecordedEventTimeType : public PreallocString<30> {};
    #endif
    
    #ifndef LatestPayload10283
    class LatestPayloadType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10283 - Device Reboot Event
 *  This binary status should indicate that the meter MCU can no longer communicate with
 *  a daughter board
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6011 - Event Type is a readable and writable resource used to represent how this event will behave. Event Type should be one of the following values:-0. Disabled1. Alarm Current State2. Alarm State Change Log3. Event LogWhen the Event Type is set to Disabled (0), this event will not be recorded by the device. No Latest Eventlog payload should be delivered for events that are Disabled.When the Event Type is set to Alarm Current State (1), this Event is treated as an alarm state manager and the Latest Eventlog Payload will only contain the current state of this alarm.When the Event Type is set to Alarm State Change Log (2), the Event is treated as an alarm that reports whenever the Alarm is either set or cleared. The Latest Eventlog Payload will contain all alarm transitions since the previous delivery in this mode.When the Event Type is set to Event Log (3), this object instance is treated as a raw event log. It is used to manage and deliver events. The Latest Eventlog Payload will contain all events since the previous delivery in this mode.See the Event Log Payload for examples of each of these modes.
    int EventType;
    
    // 6012 - Realtime is a readable and writable resource used to indicate if an event should report immediately (1) at the point of occurrence, or delivered periodically as part of the Latest Eventlog Payload.
    bool AlarmRealtime;
    
    // Optional resource
    // 6013 - Alarm State is a read-only resource used to indicate the current alarm state for this Event configuration. This is only applicable if the Event Type is Alarm Current State (1) or Alarm State Change (2).  
    bool AlarmState;
    
    // Optional resource
    // 6014 - Set Threshold is a readable and writable resource used to represent the threshold for when an alarm is triggered. This resource is used in conjunction with the Set Operator resource. 
    float AlarmSetThreshold;
    
    // Optional resource
    // 6015 - Set Operator is a readable and writable resource used in conjunction with the Set Threshold to represent when an alarm is triggered. This resource should be set to one of the following values:-0. Greater Than or Equal to1. Less Than or Equal to By setting the Set Operator to Greater Than (0), when the measured value for this event exceeds the Set Threshold resource, the event is considered to be in an Alarm State of 1By setting the Set Operator to Less Than (1), when the measured value for this event falls below the Set Threshold resource, the event is considered to be in an Alarm State of 1
    int AlarmSetOperator;
    
    // Optional resource
    // 6016 - Clear Threshold is a readable and writable resource used to represent the threshold for when an alarm is cleared. This resource is used in conjunction with the Clear Operator resource.  
    float AlarmClearThreshold;
    
    // Optional resource
    // 6017 - Clear Operator is a readable and writable resource used in conjunction with the Clear Threshold to represent when an alarm is Cleared. This resource should be set to one of the following values:-0. Greater Than or Equal to1. Less Than or Equal toBy setting the Clear Operator to Greater Than (0), when the measured value for this event exceeds the Clear Threshold resource, the event is considered to be in an Alarm State of 0By setting the Clear Operator to Less Than (1), when the measured value for this event falls below the Clear Threshold resource, the event is considered to be in an Alarm State of 0
    int AlarmClearOperator;
    
    // Optional resource
    // 6018 - Maximum Event Count is a readable and writable resource used provide a ceiling on the number of events that can be raised within the time period defined in Maximum Event Period resource. If no Maximum Event Count is set, the number of events recorded is unconstrained. The intent of this resource is to control the number of events reported, particularly in the case of a faulty sensor.
    int AlarmMaximumEventCount;
    
    // Optional resource
    // 6019 - Maximum Event Period is a readable and writable resource used in conjunction with the Maximum Event Count resource to control the number of events that can be raised in a given period. Maximum Event Period is an integer value representing the number of seconds for which the Maximum Event Count is measured. If no Maximum Event Period is set, the number of events recorded is unconstrained. The intent of this resource is to control the number of events reported, particularly in the case of a faulty sensor.
    int AlarmMaximumEventPeriod;
    
    // Optional resource
    // 6020 - Latest Delivered Event Time is a readable and writable resource to represent the last recorded time that an event was delivered for this event code to the LwM2M server. The setting of this resource is implementation specific but should be updated based on, either a Read request of the Latest Eventlog Payload from the LwM2M server or via a confirmed delivery of Notify operation of the Latest Eventlog Payload resource. This resource is writable to allow the server to adjust the Last Delivered Event Time value if the server and client is out of sync.
    LatestDeliveredEventTimeType LatestDeliveredEventTime; // Time
    
    // 6021 - Latest Recorded Event Time is a readonly resource used to represent the last recorded event time for this object instance on the device
    LatestRecordedEventTimeType LatestRecordedEventTime; // Time
    
    // Optional resource
    // 6022 - Clear Alarm is an executable resource used to allow the LwM2M server to clear alarms when they need to be manually acknowledged.
    Executable AlarmClear;

    // Optional resource
    // 6023 - Auto Clear Alarm is a readable and writable resource used to indicate if an alarm is automatically cleared once the delivery of the event data payload is complete 
    bool AlarmAutoClear;
    
    // 6024 - Event Code is a read-only resource used as an identifier to represent this class of event. The allocation of event codes is implementation specific but ideally be unique across the implementation. Event Codes use vendor specific LogClass value 100...255
    int EventCode;
    
    // 6025 - The Latest Eventlog Payload resource is a read-only serialised Opaque (Binary) representation of all the Event Data between the Last Delivered Event Time and the Latest Recorded Event Time. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should be updated. When no new data exists, an empty Opaque value should be provided.The payload data can be provided in an implementation specific serialisation, but by default for fixed length values should use the OMA-LwM2M CBOR format encoded with one of these schemes:-Event Type = Alarm Current State (1)In this mode, only the current alarm state should be reported1. 8-bit integer, value 2 representing OMA-LwM2M CBOR format.2. Event Code [16-bit integer]3. Event Type [8-bit Integer] - Alarm Current State (1)4. Alarm Timestamp [32-bit unsigned integer] representing the number of seconds since Jan 1st, 1970 in the UTC time zone.5. Alarm State [8-bit Integer]
    LatestPayloadType LatestPayload;
    
};

enum class RESID {
    EventType = 6011,
    AlarmRealtime = 6012,
    AlarmState = 6013,
    AlarmSetThreshold = 6014,
    AlarmSetOperator = 6015,
    AlarmClearThreshold = 6016,
    AlarmClearOperator = 6017,
    AlarmMaximumEventCount = 6018,
    AlarmMaximumEventPeriod = 6019,
    LatestDeliveredEventTime = 6020,
    LatestRecordedEventTime = 6021,
    AlarmClear = 6022,
    AlarmAutoClear = 6023,
    EventCode = 6024,
    LatestPayload = 6025,
    
};

/* \brief Class for object 10283 - Device Reboot Event
 *  This binary status should indicate that the meter MCU can no longer communicate with
 *  a daughter board
 */
class object : public Lwm2mObject<10283, object, instance> {
public:

    // 6011 - Event Type is a readable and writable resource used to represent how this event will behave. Event Type should be one of the following values:-0. Disabled1. Alarm Current State2. Alarm State Change Log3. Event LogWhen the Event Type is set to Disabled (0), this event will not be recorded by the device. No Latest Eventlog payload should be delivered for events that are Disabled.When the Event Type is set to Alarm Current State (1), this Event is treated as an alarm state manager and the Latest Eventlog Payload will only contain the current state of this alarm.When the Event Type is set to Alarm State Change Log (2), the Event is treated as an alarm that reports whenever the Alarm is either set or cleared. The Latest Eventlog Payload will contain all alarm transitions since the previous delivery in this mode.When the Event Type is set to Event Log (3), this object instance is treated as a raw event log. It is used to manage and deliver events. The Latest Eventlog Payload will contain all events since the previous delivery in this mode.See the Event Log Payload for examples of each of these modes.
    Resource(6011, &instance::EventType, O_RES_RW) EventType;
    
    // 6012 - Realtime is a readable and writable resource used to indicate if an event should report immediately (1) at the point of occurrence, or delivered periodically as part of the Latest Eventlog Payload.
    Resource(6012, &instance::AlarmRealtime, O_RES_RW) AlarmRealtime;
    
    // Optional resource
    // 6013 - Alarm State is a read-only resource used to indicate the current alarm state for this Event configuration. This is only applicable if the Event Type is Alarm Current State (1) or Alarm State Change (2).  
    Resource(6013, &instance::AlarmState, O_RES_R) AlarmState;
    
    // Optional resource
    // 6014 - Set Threshold is a readable and writable resource used to represent the threshold for when an alarm is triggered. This resource is used in conjunction with the Set Operator resource. 
    Resource(6014, &instance::AlarmSetThreshold, O_RES_RW) AlarmSetThreshold;
    
    // Optional resource
    // 6015 - Set Operator is a readable and writable resource used in conjunction with the Set Threshold to represent when an alarm is triggered. This resource should be set to one of the following values:-0. Greater Than or Equal to1. Less Than or Equal to By setting the Set Operator to Greater Than (0), when the measured value for this event exceeds the Set Threshold resource, the event is considered to be in an Alarm State of 1By setting the Set Operator to Less Than (1), when the measured value for this event falls below the Set Threshold resource, the event is considered to be in an Alarm State of 1
    Resource(6015, &instance::AlarmSetOperator, O_RES_RW) AlarmSetOperator;
    
    // Optional resource
    // 6016 - Clear Threshold is a readable and writable resource used to represent the threshold for when an alarm is cleared. This resource is used in conjunction with the Clear Operator resource.  
    Resource(6016, &instance::AlarmClearThreshold, O_RES_RW) AlarmClearThreshold;
    
    // Optional resource
    // 6017 - Clear Operator is a readable and writable resource used in conjunction with the Clear Threshold to represent when an alarm is Cleared. This resource should be set to one of the following values:-0. Greater Than or Equal to1. Less Than or Equal toBy setting the Clear Operator to Greater Than (0), when the measured value for this event exceeds the Clear Threshold resource, the event is considered to be in an Alarm State of 0By setting the Clear Operator to Less Than (1), when the measured value for this event falls below the Clear Threshold resource, the event is considered to be in an Alarm State of 0
    Resource(6017, &instance::AlarmClearOperator, O_RES_RW) AlarmClearOperator;
    
    // Optional resource
    // 6018 - Maximum Event Count is a readable and writable resource used provide a ceiling on the number of events that can be raised within the time period defined in Maximum Event Period resource. If no Maximum Event Count is set, the number of events recorded is unconstrained. The intent of this resource is to control the number of events reported, particularly in the case of a faulty sensor.
    Resource(6018, &instance::AlarmMaximumEventCount, O_RES_RW) AlarmMaximumEventCount;
    
    // Optional resource
    // 6019 - Maximum Event Period is a readable and writable resource used in conjunction with the Maximum Event Count resource to control the number of events that can be raised in a given period. Maximum Event Period is an integer value representing the number of seconds for which the Maximum Event Count is measured. If no Maximum Event Period is set, the number of events recorded is unconstrained. The intent of this resource is to control the number of events reported, particularly in the case of a faulty sensor.
    Resource(6019, &instance::AlarmMaximumEventPeriod, O_RES_RW) AlarmMaximumEventPeriod;
    
    // Optional resource
    // 6020 - Latest Delivered Event Time is a readable and writable resource to represent the last recorded time that an event was delivered for this event code to the LwM2M server. The setting of this resource is implementation specific but should be updated based on, either a Read request of the Latest Eventlog Payload from the LwM2M server or via a confirmed delivery of Notify operation of the Latest Eventlog Payload resource. This resource is writable to allow the server to adjust the Last Delivered Event Time value if the server and client is out of sync.
    Resource(6020, &instance::LatestDeliveredEventTime, O_RES_RW) LatestDeliveredEventTime;
    
    // 6021 - Latest Recorded Event Time is a readonly resource used to represent the last recorded event time for this object instance on the device
    Resource(6021, &instance::LatestRecordedEventTime, O_RES_R) LatestRecordedEventTime;
    
    // Optional resource
    // 6022 - Clear Alarm is an executable resource used to allow the LwM2M server to clear alarms when they need to be manually acknowledged.
    Resource(6022, &instance::AlarmClear) AlarmClear;
    
    // Optional resource
    // 6023 - Auto Clear Alarm is a readable and writable resource used to indicate if an alarm is automatically cleared once the delivery of the event data payload is complete 
    Resource(6023, &instance::AlarmAutoClear, O_RES_RW) AlarmAutoClear;
    
    // 6024 - Event Code is a read-only resource used as an identifier to represent this class of event. The allocation of event codes is implementation specific but ideally be unique across the implementation. Event Codes use vendor specific LogClass value 100...255
    Resource(6024, &instance::EventCode, O_RES_R) EventCode;
    
    // 6025 - The Latest Eventlog Payload resource is a read-only serialised Opaque (Binary) representation of all the Event Data between the Last Delivered Event Time and the Latest Recorded Event Time. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should be updated. When no new data exists, an empty Opaque value should be provided.The payload data can be provided in an implementation specific serialisation, but by default for fixed length values should use the OMA-LwM2M CBOR format encoded with one of these schemes:-Event Type = Alarm Current State (1)In this mode, only the current alarm state should be reported1. 8-bit integer, value 2 representing OMA-LwM2M CBOR format.2. Event Code [16-bit integer]3. Event Type [8-bit Integer] - Alarm Current State (1)4. Alarm Timestamp [32-bit unsigned integer] representing the number of seconds since Jan 1st, 1970 in the UTC time zone.5. Alarm State [8-bit Integer]
    Resource(6025, &instance::LatestPayload, O_RES_R) LatestPayload;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10283::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10283::RESID c1) { return (uint16_t) c1 == c2; }
	