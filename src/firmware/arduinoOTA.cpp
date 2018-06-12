#include "lwm2m_connect.h"
#include "object_firmware.hpp"
#if !defined(_WIN32) && !defined(__unix__) && defined(LWM2M_FIRMWARE_UPGRADES)
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>

KnownObjects::id5::object firmwareObject;
KnownObjects::id5::instance firmwareObjectInstance;

void writeNewFirmware(DynArray<uint8_t*>& firmware) {
    firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_UNSUPPORTED;
    firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
}

void executeFirmwareUpdate(uint8_t*, int) {
   if (firmwareObjectInstance.State == UPDATE_STATE_DOWNLOADED){
       firmwareObjectInstance.State=UPDATE_STATE_UPDATING;
       firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::State);
   }
}

void processFirmwareUpgrade() {
    switch (firmwareObjectInstance.State) {
        case UPDATE_STATE_IDLE:
            if (firmwareObjectInstance.PackageURI.data[0]!=0) {
                ESPhttpUpdate.rebootOnUpdate(false);
                HTTPUpdateResult r = ESPhttpUpdate.update(String((char*)firmwareObjectInstance.PackageURI.data));
                switch (r) {
                    case HTTP_UPDATE_FAILED:
                        firmwareObjectInstance.State=UPDATE_STATE_IDLE;
                        switch (ESPhttpUpdate.getLastError()) {
                            case HTTP_UE_TOO_LESS_SPACE:
                                firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_NOFLASH;
                                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_SERVER_NOT_REPORT_SIZE:
                            case HTTP_UE_SERVER_FILE_NOT_FOUND:
                            case HTTP_UE_SERVER_FORBIDDEN:
                            case HTTP_UE_SERVER_WRONG_HTTP_CODE:
                                firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_BAD_PACKET;
                                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_SERVER_FAULTY_MD5:
                            case HTTP_UE_BIN_VERIFY_HEADER_FAILED:
                                firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_BAD_PACKET;
                                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            case HTTP_UE_BIN_FOR_WRONG_FLASH:
                                firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_UNSUPPORTED;
                                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                                break;
                            default:
                                firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_FAILED;
                                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        };
                        break;
                    case HTTP_UPDATE_OK:
                        firmwareObjectInstance.State=UPDATE_STATE_DOWNLOADED;
                        firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_SUCCESS;
                        firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        break;
                    case HTTP_UPDATE_NO_UPDATES:
                    default:
                        firmwareObjectInstance.State=UPDATE_STATE_IDLE;
                        firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_IDLE;
                        firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::UpdateResult);
                        break;
                };
                firmwareObject.resChanged(lwm2m_client_get_context(),0,(uint16_t)KnownObjects::id5::RESID::State);
            }
            break;
        case UPDATE_STATE_UPDATING:
            ESP.restart();
            break;
        default:
            break;
    };
}

// Initalize the KnownObjects::id5::object
class InitModule {
public:
    InitModule() {
        firmwareObjectInstance.Package = writeNewFirmware;
        firmwareObjectInstance.Update = executeFirmwareUpdate;
        firmwareObjectInstance.FirmwareUpdateProtocolSupport = UPDATE_PROTOCOL_HTTP;
        firmwareObjectInstance.FirmwareUpdateDeliveryMethod = UPDATE_DELIVERY_PULL;
        firmwareObjectInstance.PkgVersion.copy(LWM2M_APP_VERSION);
        firmwareObjectInstance.State=UPDATE_STATE_IDLE;
        firmwareObjectInstance.UpdateResult=UPDATE_RESULT_STATE_IDLE;
        firmwareObjectInstance.PackageURI.data[0] = 0;
    }
};
static InitModule initModule;

#endif
