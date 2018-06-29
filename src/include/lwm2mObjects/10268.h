#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10268 {
// Custom, overrideable types for Opaque and String resources

    #ifndef IntervalUTCOffset10268
    class IntervalUTCOffsetType : public PreallocString<30> {};
    #endif
    
    #ifndef IntervalCollectionStartTime10268
    class IntervalCollectionStartTimeType : public PreallocString<30> {};
    #endif
    
    #ifndef OldestRecordedInterval10268
    class OldestRecordedIntervalType : public PreallocString<30> {};
    #endif
    
    #ifndef LastDeliveredInterval10268
    class LastDeliveredIntervalType : public PreallocString<30> {};
    #endif
    
    #ifndef LatestRecordedInterval10268
    class LatestRecordedIntervalType : public PreallocString<30> {};
    #endif
    
    #ifndef IntervalHistoricalReadPayload10268
    class IntervalHistoricalReadPayloadType : public Opaque<30> {};
    #endif
    
    #ifndef LatestPayload10268
    class LatestPayloadType : public Opaque<30> {};
    #endif
    

/* \brief Class for object 10268 - Temperature Readings
 *  Periodic temperature measurements
 */
class instance : public Lwm2mObjectInstance {
public:

    // 6000 - The Interval Period resource is an Integer value representing the width in seconds of the intervals being managed by this interval data object. This resource is read only and can only be changed by resource 11 (Change Interval Configuration). It is recommended that the Interval Period be set to a devisor of 24 hours (86400 seconds) to provide a consistent interval period. Examples of Interval Period include:-30 = Every 30 seconds600 = Every 10 minutes1800 = Every 30 minutes3600 = Hourly7200 = Every 2 hours14400 = Every 4 hours43200 = Every 12 hours86400 = Every Day172600 = Every Second Day
    int IntervalPeriod;
    
    // Optional resource
    // 6001 - The Interval Start Offset resource is a read only resource representing the number of seconds past midnight for which the first interval is recorded. If this resource is empty, it is assumed that the intervals are midnight aligned. This can be used to adjust interval boundaries. As an example, an Interval Period of 3600 seconds and an Interval Start time of 300 represents hourly interval data, starting at 00:05.
    int IntervalStartOffset;
    
    // Optional resource
    // 6002 - The Interval UTC Offset resource is a read only resource representing the time zone offset for this Interval Data instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided. UTC+X [ISO 8601].
    IntervalUTCOffsetType IntervalUTCOffset;
    
    // 6003 - The Collection Start Time resource is a read only resource representing the time when the first interval was recorded on the device. Interval times represent the end of the interval, not the beginning. As an example, the first four hourly interval past midnight will have a timestamp of 04:00 (adjusting for UTC offset). 
    IntervalCollectionStartTimeType IntervalCollectionStartTime; // Time
    
    // 6004 - The Oldest Recorded Interval resource is a read-only resource representing the oldest available interval on the device. Interval times represent the end of the interval, not the beginning.
    OldestRecordedIntervalType OldestRecordedInterval; // Time
    
    // Optional resource
    // 6005 - The Last Delivered Interval is a readable and writable resource used to represent the last interval delivered to the LwM2M server. Interval times represent the end of the interval, not the beginning. The setting of this resource is implementation specific but should be updated based on, either a Read request of the Latest Payload from the LwM2M server or via a confirmed delivery of Notify operation of the Latest Payload resource. This resource is writable to allow the server to adjust the Last Delivered Interval value if the server and client is out of sync.
    LastDeliveredIntervalType LastDeliveredInterval; // Time
    
    // 6006 - The Latest Recorded Interval is a readable resource representing the currently highest recorded interval on the device. Interval times represent the end of the interval, not the beginning.
    LatestRecordedIntervalType LatestRecordedInterval; // Time
    
    // 6007 - The Delivery Midnight Aligned is a readable and writable resource used to indicate if data is delivered only to the previous midnight (1) or if part-day data can be delivered (0). Calculating Midnight should consider the Interval UTC Offset resource, or if empty, the Device [/3/0/14] object instance resource.
    bool IntervalDeliveryMidnightAligned;
    
    // Optional resource
    // 6008 - Historical Interval Read is an executable resource designed to retrieve ad-hoc interval read data. The resource takes two arguments:-Argument 0: First Interval time to Retrieve represented as number of seconds since Jan 1st, 1970 in the UTC time zone.Argument 1: Last interval time to Retrieve represented as number of seconds since Jan 1st, 1970 in the UTC time zone.The dates should be inclusive based on the end time of the interval. The data retrieved from this resource will be readable (or observable) from the Historical Read Payload Resource.As an example, the Argument List to retrieve data from Midnight 2nd March (UTC+10) to Midnight 6rd March (UTC+10) for a specific instance of the interval data object, would be constructed as follows:-0='1488463200',1='1488808800'
    Executable IntervalHistoricalRead;

    // Optional resource
    // 6009 - The Historical Read Payload resource is the representation of the data requested by the Historical Interval Read executable resource. The format of this Opaque value should be identical to the Latest Payload resource. If no Historical Interval Read has been executed, this resource should return and empty Opaque value. This resource can either be Read from the Server or set up as an observation and Notified to the server as soon as the historical data is available. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Historical Read Payload should be set to an empty Opaque value.
    IntervalHistoricalReadPayloadType IntervalHistoricalReadPayload;
    
    // Optional resource
    // 6010 - Change Interval Configuration is an executable resource designed to allow the Interval Period, Interval Start Offset and Interval UTC Offset to be reconfigured. The resource takes three arguments:-Argument 0: [Mandatory] Interval Period represented as an integer as defined in the Interval Period Resource.Argument 1: [Optional] Interval start offset represented as an integer as defined in the Interval Start Offset Resource. If not provided, leave the value as per the current configurationArgument 2: [Optional] Interval UTC offset represented as a String as defined in the Interval UTC Offset Resource. If not provided, leave the value as per the current configuration.Depending on the specifics of the implementation of this object, reconfiguring the Interval data object may result in the removal of all historical data for this Interval Data Object Instance. Please consult with your device vendor as to the implications of reconfiguring an Interval Data Object Instance.As an example, the Argument List to change an interval data object instance from its existing values to one hour intervals, midnight aligned in UTC+10 time zone:-0='3600',1='0',1='UTC+10'
    Executable IntervalChangeConfiguration;

    // Optional resource
    // 6026 - Start is an executable resource that enables the recording of interval data. The first interval recorded will have a timestamp based on the Interval Start Offset resource. This executable resource takes no arguments. Refer to re-usable resource LogStart for further details.
    Executable Start;

    // Optional resource
    // 6027 - Stop (LogStop) is an executable resource that disables the recording of interval data for this object instance. This executable resource takes no arguments. Refer to re-usable resource LogStop for further details.
    Executable Stop;

    // Optional resource
    // 6028 - Recording Enabled is a read-only resource providing an indication of if interval data is currently being recorded for this object instance. Refer to re-usable resource LogStatus for further details.
    int Status;
    
    // 6029 - The Latest Payload resource is a read-only serialised Opaque (Binary) representation of all the Interval Data between the Last Delivered Interval and the Latest Recorded Interval, accounting for the Delivery Midnight Aligned resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should be updated. When no new data exists, an empty Opaque value should be provided.The payload data can be provided in an implementation specific serialisation, but by default for fixed length values should use the OMA-LwM2M CBOR format encoded as follows:1. 8-bit integer, value 2 representing OMA-LwM2M CBOR format.2. Interval Data Instance ID/ Class [16-bit integer]3. Timestamp of first Interval [32-bit integer] representing the number of seconds since Jan 1st, 1970 in the UTC time zone.4. Interval Period in seconds [32-bit integer]5. Number of intervals in Payload [16-bit integer]6. Number of Values Per Interval [8-bit integer]7. Size of Value 1 in bits [8-bit integer]8. Size of Value 2 in bits [8-bit integer]...9. Size of Value N in bits [8-bit integer]10. Interval 1 Value 1 [x bits]11. Interval 1 Value 2 [x bits]...12. Interval 1 Value N [x bits]...13. Interval N Value N [x bits]If for some implementation specific reason, there are missing intervals in the sequence, the payload may consist of multiple blocks of the above serialised data (appended into a single binary opaque value), each block representing a continuous series of interval data.
    LatestPayloadType LatestPayload;
    
};

enum class RESID {
    IntervalPeriod = 6000,
    IntervalStartOffset = 6001,
    IntervalUTCOffset = 6002,
    IntervalCollectionStartTime = 6003,
    OldestRecordedInterval = 6004,
    LastDeliveredInterval = 6005,
    LatestRecordedInterval = 6006,
    IntervalDeliveryMidnightAligned = 6007,
    IntervalHistoricalRead = 6008,
    IntervalHistoricalReadPayload = 6009,
    IntervalChangeConfiguration = 6010,
    Start = 6026,
    Stop = 6027,
    Status = 6028,
    LatestPayload = 6029,
    
};

/* \brief Class for object 10268 - Temperature Readings
 *  Periodic temperature measurements
 */
class object : public Lwm2mObject<10268, object, instance> {
public:

    // 6000 - The Interval Period resource is an Integer value representing the width in seconds of the intervals being managed by this interval data object. This resource is read only and can only be changed by resource 11 (Change Interval Configuration). It is recommended that the Interval Period be set to a devisor of 24 hours (86400 seconds) to provide a consistent interval period. Examples of Interval Period include:-30 = Every 30 seconds600 = Every 10 minutes1800 = Every 30 minutes3600 = Hourly7200 = Every 2 hours14400 = Every 4 hours43200 = Every 12 hours86400 = Every Day172600 = Every Second Day
    Resource(6000, &instance::IntervalPeriod, O_RES_R) IntervalPeriod;
    
    // Optional resource
    // 6001 - The Interval Start Offset resource is a read only resource representing the number of seconds past midnight for which the first interval is recorded. If this resource is empty, it is assumed that the intervals are midnight aligned. This can be used to adjust interval boundaries. As an example, an Interval Period of 3600 seconds and an Interval Start time of 300 represents hourly interval data, starting at 00:05.
    Resource(6001, &instance::IntervalStartOffset, O_RES_R) IntervalStartOffset;
    
    // Optional resource
    // 6002 - The Interval UTC Offset resource is a read only resource representing the time zone offset for this Interval Data instance. If this resource is empty, the application should use the UTC offset provided in the Device [/3/0/14] object instance resource or UTC if not provided. UTC+X [ISO 8601].
    Resource(6002, &instance::IntervalUTCOffset, O_RES_R) IntervalUTCOffset;
    
    // 6003 - The Collection Start Time resource is a read only resource representing the time when the first interval was recorded on the device. Interval times represent the end of the interval, not the beginning. As an example, the first four hourly interval past midnight will have a timestamp of 04:00 (adjusting for UTC offset). 
    Resource(6003, &instance::IntervalCollectionStartTime, O_RES_R) IntervalCollectionStartTime;
    
    // 6004 - The Oldest Recorded Interval resource is a read-only resource representing the oldest available interval on the device. Interval times represent the end of the interval, not the beginning.
    Resource(6004, &instance::OldestRecordedInterval, O_RES_R) OldestRecordedInterval;
    
    // Optional resource
    // 6005 - The Last Delivered Interval is a readable and writable resource used to represent the last interval delivered to the LwM2M server. Interval times represent the end of the interval, not the beginning. The setting of this resource is implementation specific but should be updated based on, either a Read request of the Latest Payload from the LwM2M server or via a confirmed delivery of Notify operation of the Latest Payload resource. This resource is writable to allow the server to adjust the Last Delivered Interval value if the server and client is out of sync.
    Resource(6005, &instance::LastDeliveredInterval, O_RES_RW) LastDeliveredInterval;
    
    // 6006 - The Latest Recorded Interval is a readable resource representing the currently highest recorded interval on the device. Interval times represent the end of the interval, not the beginning.
    Resource(6006, &instance::LatestRecordedInterval, O_RES_R) LatestRecordedInterval;
    
    // 6007 - The Delivery Midnight Aligned is a readable and writable resource used to indicate if data is delivered only to the previous midnight (1) or if part-day data can be delivered (0). Calculating Midnight should consider the Interval UTC Offset resource, or if empty, the Device [/3/0/14] object instance resource.
    Resource(6007, &instance::IntervalDeliveryMidnightAligned, O_RES_RW) IntervalDeliveryMidnightAligned;
    
    // Optional resource
    // 6008 - Historical Interval Read is an executable resource designed to retrieve ad-hoc interval read data. The resource takes two arguments:-Argument 0: First Interval time to Retrieve represented as number of seconds since Jan 1st, 1970 in the UTC time zone.Argument 1: Last interval time to Retrieve represented as number of seconds since Jan 1st, 1970 in the UTC time zone.The dates should be inclusive based on the end time of the interval. The data retrieved from this resource will be readable (or observable) from the Historical Read Payload Resource.As an example, the Argument List to retrieve data from Midnight 2nd March (UTC+10) to Midnight 6rd March (UTC+10) for a specific instance of the interval data object, would be constructed as follows:-0='1488463200',1='1488808800'
    Resource(6008, &instance::IntervalHistoricalRead) IntervalHistoricalRead;
    
    // Optional resource
    // 6009 - The Historical Read Payload resource is the representation of the data requested by the Historical Interval Read executable resource. The format of this Opaque value should be identical to the Latest Payload resource. If no Historical Interval Read has been executed, this resource should return and empty Opaque value. This resource can either be Read from the Server or set up as an observation and Notified to the server as soon as the historical data is available. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Historical Read Payload should be set to an empty Opaque value.
    Resource(6009, &instance::IntervalHistoricalReadPayload, O_RES_R) IntervalHistoricalReadPayload;
    
    // Optional resource
    // 6010 - Change Interval Configuration is an executable resource designed to allow the Interval Period, Interval Start Offset and Interval UTC Offset to be reconfigured. The resource takes three arguments:-Argument 0: [Mandatory] Interval Period represented as an integer as defined in the Interval Period Resource.Argument 1: [Optional] Interval start offset represented as an integer as defined in the Interval Start Offset Resource. If not provided, leave the value as per the current configurationArgument 2: [Optional] Interval UTC offset represented as a String as defined in the Interval UTC Offset Resource. If not provided, leave the value as per the current configuration.Depending on the specifics of the implementation of this object, reconfiguring the Interval data object may result in the removal of all historical data for this Interval Data Object Instance. Please consult with your device vendor as to the implications of reconfiguring an Interval Data Object Instance.As an example, the Argument List to change an interval data object instance from its existing values to one hour intervals, midnight aligned in UTC+10 time zone:-0='3600',1='0',1='UTC+10'
    Resource(6010, &instance::IntervalChangeConfiguration) IntervalChangeConfiguration;
    
    // Optional resource
    // 6026 - Start is an executable resource that enables the recording of interval data. The first interval recorded will have a timestamp based on the Interval Start Offset resource. This executable resource takes no arguments. Refer to re-usable resource LogStart for further details.
    Resource(6026, &instance::Start) Start;
    
    // Optional resource
    // 6027 - Stop (LogStop) is an executable resource that disables the recording of interval data for this object instance. This executable resource takes no arguments. Refer to re-usable resource LogStop for further details.
    Resource(6027, &instance::Stop) Stop;
    
    // Optional resource
    // 6028 - Recording Enabled is a read-only resource providing an indication of if interval data is currently being recorded for this object instance. Refer to re-usable resource LogStatus for further details.
    Resource(6028, &instance::Status, O_RES_R) Status;
    
    // 6029 - The Latest Payload resource is a read-only serialised Opaque (Binary) representation of all the Interval Data between the Last Delivered Interval and the Latest Recorded Interval, accounting for the Delivery Midnight Aligned resource. When this payload is delivered to the LwM2M server, via either a read request or a confirmed observation on this Object, Object Instance or Resource, the Latest Delivered Interval should be updated. When no new data exists, an empty Opaque value should be provided.The payload data can be provided in an implementation specific serialisation, but by default for fixed length values should use the OMA-LwM2M CBOR format encoded as follows:1. 8-bit integer, value 2 representing OMA-LwM2M CBOR format.2. Interval Data Instance ID/ Class [16-bit integer]3. Timestamp of first Interval [32-bit integer] representing the number of seconds since Jan 1st, 1970 in the UTC time zone.4. Interval Period in seconds [32-bit integer]5. Number of intervals in Payload [16-bit integer]6. Number of Values Per Interval [8-bit integer]7. Size of Value 1 in bits [8-bit integer]8. Size of Value 2 in bits [8-bit integer]...9. Size of Value N in bits [8-bit integer]10. Interval 1 Value 1 [x bits]11. Interval 1 Value 2 [x bits]...12. Interval 1 Value N [x bits]...13. Interval N Value N [x bits]If for some implementation specific reason, there are missing intervals in the sequence, the payload may consist of multiple blocks of the above serialised data (appended into a single binary opaque value), each block representing a continuous series of interval data.
    Resource(6029, &instance::LatestPayload, O_RES_R) LatestPayload;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10268::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10268::RESID c1) { return (uint16_t) c1 == c2; }
	