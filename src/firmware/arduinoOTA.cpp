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
typedef int make_iso_compilers_happy;

#if !defined(_WIN32) && !defined(__unix__) && defined(LWM2M_FIRMWARE_UPGRADES)
#include "lwm2m/connect.h"
#include "lwm2m/object_firmware.hpp"
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>

void writeNewFirmware(void* o, DynArray<uint8_t*>& firmware, lwm2m_context_t* contextP) {
    FirmwareUpdate* fu = reinterpret_cast<FirmwareUpdate*>(o);

    fu->UpdateResult=UPDATE_RESULT_STATE_UNSUPPORTED;
    fu->firmwareObject.resChanged(contextP,0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
}

void executeFirmwareUpdate(void* o, lwm2m_context_t* contextP) {
    FirmwareUpdate* fu = reinterpret_cast<FirmwareUpdate*>(o);

    if (fu->State == UPDATE_STATE_DOWNLOADED){
       fu->State=UPDATE_STATE_UPDATING;
       fu->firmwareObject.resChanged(contextP,0,(uint16_t)KnownObjects::id5::RESID::State);
    }
}

void FirmwareUpdate::process() {
    switch (State) {
        case UPDATE_STATE_IDLE:
            if (PackageURI.data[0]!=0) {
                ESPhttpUpdate.rebootOnUpdate(false);
                HTTPUpdateResult r = ESPhttpUpdate.update(String((char*)PackageURI.data));
                switch (r) {
                    case HTTP_UPDATE_FAILED:
                        State=UPDATE_STATE_IDLE;
                        switch (ESPhttpUpdate.getLastError()) {
                            case HTTP_UE_TOO_LESS_SPACE:
                                UpdateResult=UPDATE_RESULT_STATE_NOFLASH;
                                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_SERVER_NOT_REPORT_SIZE:
                            case HTTP_UE_SERVER_FILE_NOT_FOUND:
                            case HTTP_UE_SERVER_FORBIDDEN:
                            case HTTP_UE_SERVER_WRONG_HTTP_CODE:
                                UpdateResult=UPDATE_RESULT_STATE_BAD_PACKET;
                                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_SERVER_FAULTY_MD5:
                            case HTTP_UE_BIN_VERIFY_HEADER_FAILED:
                                UpdateResult=UPDATE_RESULT_STATE_BAD_PACKET;
                                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_BIN_FOR_WRONG_FLASH:
                                UpdateResult=UPDATE_RESULT_STATE_UNSUPPORTED;
                                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            default:
                                UpdateResult=UPDATE_RESULT_STATE_FAILED;
                                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        };
                        break;
                    case HTTP_UPDATE_OK:
                        State=UPDATE_STATE_DOWNLOADED;
                        UpdateResult=UPDATE_RESULT_STATE_SUCCESS;
                        firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        break;
                    case HTTP_UPDATE_NO_UPDATES:
                    default:
                        State=UPDATE_STATE_IDLE;
                        UpdateResult=UPDATE_RESULT_STATE_IDLE;
                        firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        break;
                };
                firmwareObject.resChanged(get_firmware_lwm2m_context(),0,(uint16_t)KnownObjects::id5::RESID::State);
            }
            break;
        case UPDATE_STATE_UPDATING:
            ESP.restart();
            break;
        default:
            break;
    };
}

FirmwareUpdate::FirmwareUpdate(const char* app_version, lwm2m_update_protocol protocol) {
    Package = writeNewFirmware;
    Update = executeFirmwareUpdate;
    FirmwareUpdateProtocolSupport = protocol;
    FirmwareUpdateDeliveryMethod = UPDATE_DELIVERY_PUSHPULL;
    PkgVersion.copy(app_version);
    State=UPDATE_STATE_IDLE;
    UpdateResult=UPDATE_RESULT_STATE_IDLE;
    PackageURI.data[0] = 0;
}

#endif
