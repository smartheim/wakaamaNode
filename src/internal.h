#pragma once
#include "wakaama/liblwm2m.h"
#include "lwm2m/context.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include <sys/time.h> // We need struct timeval + gettimeofday()

#ifndef timercmp
# define timercmp(a, b, CMP) 						      \
  (((a)->tv_sec == (b)->tv_sec) ? 					      \
   ((a)->tv_usec CMP (b)->tv_usec) : 					      \
   ((a)->tv_sec CMP (b)->tv_sec))

# define timersub(a, b, result)						      \
  do {									      \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;			      \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;			      \
    if ((result)->tv_usec < 0) {					      \
      --(result)->tv_sec;						      \
      (result)->tv_usec += 1000000;					      \
    }									      \
  } while (0)
#endif

void init_security_object(lwm2m_client_context_t* ctx);
void init_server_object(lwm2m_client_context_t* ctx);
void init_device_object(lwm2m_client_context_t* ctx);

/**
 * If you plan to implement a read-callback method, you need to be prepared for the case where the
 * server asks for all object ressources. Use this method to allocate memory and assign ressource
 * IDs to the array lwm2m_data_t elements.
 *
 * @param dataArrayP This method will allocate memory that needs needs to be freed with lwm2m_free() again after use.
 * @param metaP The lwm2m object meta information.
 * @return Returns the count of ressources in metaP and therefore allocated lwm2m_data_t objects of dataArrayP or -1 if an error occured (no memory could be acquired). Can return 0 if there are no readable ressources in the object described by the meta object.
 */
int lwm2m_object_prepare_full_response(lwm2m_data_t** dataArrayP, lwm2m_object_meta_information_t* metaP);

/**
 * Assign/transform a lwm2m_object_res_item_t to a lwm2m_data_t structure.
 * Uses lwm2m_data_encode_* methods.
 *
 * @param destination The destination lwm2m_data_t
 * @param resP A meta ressource description (one of lwm2m_object_meta_information_t::ressources)
 * @param instanceP An lwm2m object instance
 */
uint8_t lwm2m_object_assign_single_value(lwm2m_data_t* destination, lwm2m_object_res_item_t* resP, void* instanceP);

/**
 * Looks up a specific security object instance.
 *
 * @param security_instance_id The security object instance id (same as server object instance id).
 * @return Returns a security object instance for the given instance ID or NULL.
 */
security_instance_t* lwm2m_get_security_object(lwm2m_context_t *contextP, uint16_t security_instance_id);

/**
 * Erases public/private keys, certificates etc from the given security instance
 *
 * @param securityInstance A security instance
 */
void internal_erase_security_params(security_instance_t * securityInstance);

bool internal_in_dtls_handshake(lwm2m_context_t *contextP);

#ifdef __cplusplus
}
#endif
