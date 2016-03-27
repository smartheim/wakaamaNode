#pragma once
#include "wakaama/liblwm2m.h"
#include "wakaama_device_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the device information object.
 * Change this object before you connect to a server.
 * @return
 */
device_instance_t * lwm2m_device_data_get();

/**
 * @brief Call this if you have changed a ressource in the device_instance_t object.
 * You only have to do this after you have connected to a lwm2m server.
 *
 * To change a device information (version number etc), do the following:
 * - device_instance_t* device = lwm2m_device_data_get();
 * - device->firmware_ver = "1.2";
 * - lwm2m_device_res_has_changed(RES_O_FIRMWARE_VERSION);
 *
 * Some device information are obtained by calling a function.
 * The battery level is an example.
 * Just call lwm2m_device_res_has_changed(RES_O_BATTERY_LEVEL) periodically or after
 * the battery level has changed for a reason and the runtime will retrieve the new data by
 * calling lwm2m_get_bat_level().
 *
 * @param res_id The ressource id of the value you have changed in device_instance_t.
 */
void lwm2m_device_res_has_changed(uint16_t res_id);

/**
 * @brief Initialize wakaame in client mode.
 * Will allocate objects and initializes them.
 * This method can only be called once! Close the client context with lwm2m_client_close().
 * @param endpointName
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_init(const char * endpointName);

/**
 * @brief Return the context created by lwm2m_client_init().
 * @return A wakaama context.
 */
lwm2m_context_t * lwm2m_client_get_context();

/**
 * @brief Close the wakaama client context and release dynamically aquired ressources.
 * This will not release objects created by lwm2m_object_create.
 */
void lwm2m_client_close();

// CoAP result code
uint8_t lwm2m_add_server(uint16_t shortServerID, const char* uri, uint32_t lifetime, bool storing, const char* publicId, const char* psk, size_t pskLen);

void lwm2m_unregister_server(uint16_t security_instance_id);

void lwm2m_remove_unregistered_servers();

bool lwm2m_get_server_uri(uint16_t security_instance_id, char* uriBuffer, size_t buffer_len);

/**
 * @brief Return true if wakaama is connected to a lwm2m server.
 * @return
 */
bool lwm2m_is_connected();

#ifdef __cplusplus
}
#endif
