#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id10251 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Command10251
    class CommandType : public PreallocString<30> {};
    #endif
    
    #ifndef Response10251
    class ResponseType : public PreallocString<30> {};
    #endif
    
    #ifndef Status10251
    class StatusType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 10251 - AT Command
 *  Used to execute an AT command on a cellular modem
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - The AT command to run. Example: AT+CREG? to query registration status
    CommandType Command;
    
    // 1 - Response to the AT command. Example: +CREG:0,5 If multiple lines are returned as the modem response, each line will be returned in a separate resource.
    ResponseType Response;
    
    // 2 - Status of the command execution as returned by the modem. Typical values:OK ERROR
    StatusType Status;
    
    // Optional resource
    // 3 - Amount of time in seconds allowed for the modem to respond to the command.
    int Timeout;
    
    // 4 - Executing this resource will cause the command to be sent to the modem. And the result to be populated using the Response (1) and Status (2) resources
    Executable Run;

};

enum class RESID {
    Command = 0,
    Response = 1,
    Status = 2,
    Timeout = 3,
    Run = 4,
    
};

/* \brief Class for object 10251 - AT Command
 *  Used to execute an AT command on a cellular modem
 */
class object : public Lwm2mObject<10251, object, instance> {
public:

    // 0 - The AT command to run. Example: AT+CREG? to query registration status
    Resource(0, &instance::Command, O_RES_RW) Command;
    
    // 1 - Response to the AT command. Example: +CREG:0,5 If multiple lines are returned as the modem response, each line will be returned in a separate resource.
    Resource(1, &instance::Response, O_RES_R) Response;
    
    // 2 - Status of the command execution as returned by the modem. Typical values:OK ERROR
    Resource(2, &instance::Status, O_RES_R) Status;
    
    // Optional resource
    // 3 - Amount of time in seconds allowed for the modem to respond to the command.
    Resource(3, &instance::Timeout, O_RES_RW) Timeout;
    
    // 4 - Executing this resource will cause the command to be sent to the modem. And the result to be populated using the Response (1) and Status (2) resources
    Resource(4, &instance::Run) Run;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id10251::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id10251::RESID c1) { return (uint16_t) c1 == c2; }
	