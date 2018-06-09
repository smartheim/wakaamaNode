#define ARDUINO
#define LWM2M_FIRMWARE_UPGRADES

#include "object_firmware.hpp"
#include "lwm2m_connect.h"

#if (defined(ARDUINO) || defined(LWM2M_FIRMWARE_UPGRADES))
#include <ArduinoOTA.h>

void writeNewFirmware(DynArray<uint8_t*>& firmware) {}

void executeFirmwareUpdate(uint8_t*, int) {
   if (firmwareObjectInstance.State == UPDATE_STATE_DOWNLOADED)
        ESP.restart();
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
    }
};
static InitModule initModule;

#endif
