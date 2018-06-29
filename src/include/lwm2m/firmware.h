/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#pragma once
#include "lwm2m/objects.h"
#include "wakaama_config.h"

#ifdef LWM2M_FIRMWARE_UPGRADES

/**
 * The firmware update / OTA support is only available for a C++ project.
 */

/** \brief This resource indicates what protocols the LwM2M Client implements to retrieve firmware images.
 *
 * The LwM2M server uses this information to decide what URI to include in the Package URI.
 * A LwM2M Server MUST NOT include a URI in the Package URI object that uses a protocol that
 * is unsupported by the LwM2M client.For example, if a LwM2M client indicates that it
 * supports CoAP and CoAPS then a LwM2M Server must not provide an HTTP URI in the Packet URI.
 * The following values are defined by this version of the specification:
 *
 * 0 – CoAP (as defined in RFC 7252) with the additional support for block-wise transfer.
 * CoAP is the default setting.
 * 1 – CoAPS (as defined in RFC 7252) with the additional support for block-wise transfer
 * 2 – HTTP 1.1 (as defined in RFC 7230)
 * 3 – HTTPS 1.1 (as defined in RFC 7230)
 * Additional values MAY be defined in the future. Any value not understood by the LwM2M Server MUST be ignored.
 */
enum lwm2m_update_protocol {
    UPDATE_PROTOCOL_COAP = 0,
    UPDATE_PROTOCOL_COAPS = 1,
    UPDATE_PROTOCOL_HTTP = 2,
    UPDATE_PROTOCOL_HTTPS = 3,
};

/**
 * The LwM2M Client uses this resource to indicate its support for transferring
 * firmware images to the client either via the Package Resource (=push) or
 * via the Package URI Resource (=pull) mechanism.
 * 0 – Pull only
 * 1 – Push only
 * 2 – Both.
 * In this case the LwM2M Server MAY choose the preferred mechanism for conveying
 * the firmware image to the LwM2M Client.
 */
enum lwm2m_update_delivery_method {
    UPDATE_DELIVERY_PULL = 0,
    UPDATE_DELIVERY_PUSH = 1,
    UPDATE_DELIVERY_PUSHPULL = 2,
};

/*
 * \brief Indicates current state with respect to this firmware update.
 *
If writing the firmware package to Package Resource is done, or,
if the device has downloaded the firmware package from the Package URI the state changes to Downloaded.
Writing an empty string to Package URI Resource or setting the Package Resource to NULL (‘\0’),
resets the Firmware Update State Machine: the State Resource value is set to Idle and the
Update Result Resource value is set to 0.
When in Downloaded state, and the executable Resource Update is triggered,
the state changes to Updating.
If the Update Resource failed, the state returns at Downloaded.
If performing the Update Resource was successful, the state changes from Updating to Idle.
Firmware Update mechanisms are illustrated below in Figure 29 of the LwM2M version 1.0 specification.
*/
enum lwm2m_update_state {
    UPDATE_STATE_IDLE = 0,
    UPDATE_STATE_DOWLOADING = 1,
    UPDATE_STATE_DOWNLOADED = 2,
    UPDATE_STATE_UPDATING = 3
};

/* \brief Contains the result of downloading or updating the firmware
 * 0: Initial value. Once the updating process is initiated (Download /Update),
 * this Resource MUST be reset to Initial value.
 * 1: Firmware updated successfully,
 * 2: Not enough flash memory for the new firmware package.
 * 3. Out of RAM during downloading process.
 * 4: Connection lost during downloading process.
 * 5: Integrity check failure for new downloaded package.
 * 6: Unsupported package type.
 * 7: Invalid URI
 * 8: Firmware update failed
 * 9: Unsupported protocol.
 * A LwM2M client indicates the failure to retrieve the firmware image using
 * the URI provided in the Package URI resource by writing the value 9 to the
 * /5/0/5 (Update Result resource) when the URI contained a URI scheme unsupported
 * by the client. Consequently, the LwM2M Client is unable to retrieve
 * the firmware image using the URI provided by the LwM2M Server in the Package URI
 * when it refers to an unsupported protocol.
*/
enum lwm2m_update_result_state {
    UPDATE_RESULT_STATE_IDLE = 0,
    UPDATE_RESULT_STATE_SUCCESS = 1,
    UPDATE_RESULT_STATE_NOFLASH = 2,
    UPDATE_RESULT_STATE_NORAM = 3,
    UPDATE_RESULT_STATE_CONN_LOST = 4,
    UPDATE_RESULT_STATE_BAD_PACKET = 5,
    UPDATE_RESULT_STATE_UNSUPPORTED = 6,
    UPDATE_RESULT_STATE_INVALID_URI = 7,
    UPDATE_RESULT_STATE_FAILED = 8,
    UPDATE_RESULT_STATE_PROTOCOL_UNKNOWN = 9,
};

namespace KnownObjects {
namespace id5 {
#define Package5
#define PackageURI5
#define PkgVersion5

#define PackageType IndirectWrite<uint8_t*>
class PackageURIType : public PreallocString<30> {};
class PkgVersionType : public PreallocString<30> {};
}
}
#include "lwm2mObjects/5.h"

class FirmwareUpdate : public KnownObjects::id5::instance {
public:
    /**
     * Creates a firmware update object.
     *
     * @param app_version The current APP version
     */
    FirmwareUpdate(const char* app_version, lwm2m_update_protocol protocol);

    #if (defined(_WIN32) || defined(__unix__))
    /**
     * Check if this executable is the new updated one.
     * If this is the new one:
     * Waits for the old executable to finish. We expect a
     * command line parameter "oldexe=PID" with the PID of the
     * old executable. To notify the old executable about our
     * successful start up, a POSIX signal USR1 is send.
     *
     * @param argc Command line argument count
     * @param argv Command line arguments
     */
    void checkIsUpdated(int argc, char** argv);
    std::string executableFilename;
    #endif

    /**
     * Call this in your main loop to check for new updates,
     * initiate the download and restart if necessary
     */
    void process();

    KnownObjects::id5::object firmwareObject;
};

#endif
