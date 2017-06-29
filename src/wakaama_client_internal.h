#pragma once
#include "wakaama/liblwm2m.h"
#include "wakaama_object_utils.h"

#include <string.h>
#include <stdint.h>

#define LWM2M_WITH_DTLS

#define LWM2M_SECURITY_URI_ID                 0
#define LWM2M_SECURITY_BOOTSTRAP_ID           1
#define LWM2M_SECURITY_MODE_ID            2
#define LWM2M_SECURITY_PUBLIC_KEY_ID          3
#define LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID   4
#define LWM2M_SECURITY_SECRET_KEY_ID          5
#define LWM2M_SECURITY_SMS_SECURITY_ID        6
#define LWM2M_SECURITY_SMS_KEY_PARAM_ID       7
#define LWM2M_SECURITY_SMS_SECRET_KEY_ID      8
#define LWM2M_SECURITY_SMS_SERVER_NUMBER_ID   9
#define LWM2M_SECURITY_SHORT_SERVER_ID        10
#define LWM2M_SECURITY_HOLD_OFF_ID            11

/*
 *  Resources:
 *
 *          Name            | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Server URI              |  0 |            |  Single   |    Yes    | String  |         |       |
 *  Bootstrap Server        |  1 |            |  Single   |    Yes    | Boolean |         |       |
 *  Security Mode           |  2 |            |  Single   |    Yes    | Integer |   0-3   |       |
 *  Public Key or ID        |  3 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Server Public Key or ID |  4 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Secret Key              |  5 |            |  Single   |    Yes    | Opaque  |         |       |
 *  SMS Security Mode       |  6 |            |  Single   |    Yes    | Integer |  0-255  |       |
 *  SMS Binding Key Param.  |  7 |            |  Single   |    Yes    | Opaque  |   6 B   |       |
 *  SMS Binding Secret Keys |  8 |            |  Single   |    Yes    | Opaque  | 32-48 B |       |
 *  Server SMS Number       |  9 |            |  Single   |    Yes    | Integer |         |       |
 *  Short Server ID         | 10 |            |  Single   |    No     | Integer | 1-65535 |       |
 *  Client Hold Off Time    | 11 |            |  Single   |    Yes    | Integer |         |   s   |
 *
 */

typedef struct _security_instance_
{
    struct _security_instance_ * next;        // matches lwm2m_list_t::next
    uint16_t                     instanceId;  // matches lwm2m_list_t::id
    char *                       uri;
    bool                         isBootstrap;
    uint8_t                      securityMode;
    #ifdef LWM2M_WITH_DTLS
    char *                       publicIdentity;
    uint16_t                     publicIdLen;
    char *                       serverPublicKey;
    uint16_t                     serverPublicKeyLen;
    char *                       secretKey;
    uint16_t                     secretKeyLen;
    #endif
    #ifdef LWM2M_WITH_SMS
    uint8_t                      smsSecurityMode;
    char *                       smsParams; // SMS binding key parameters
    uint16_t                     smsParamsLen;
    char *                       smsSecret; // SMS binding secret key
    uint16_t                     smsSecretLen;
    #endif
    uint16_t                     shortID;
    uint32_t                     clientHoldOffTime;
} security_instance_t;

/*
 *  Resources:
 *
 *          Name         | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Short ID             |  0 |     R      |  Single   |    Yes    | Integer | 1-65535 |       |
 *  Lifetime             |  1 |    R/W     |  Single   |    Yes    | Integer |         |   s   |
 *  Default Min Period   |  2 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Default Max Period   |  3 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Disable              |  4 |     E      |  Single   |    No     |         |         |       |
 *  Disable Timeout      |  5 |    R/W     |  Single   |    No     | Integer |         |   s   |
 *  Notification Storing |  6 |    R/W     |  Single   |    Yes    | Boolean |         |       |
 *  Binding              |  7 |    R/W     |  Single   |    Yes    | String  |         |       |
 *  Registration Update  |  8 |     E      |  Single   |    Yes    |         |         |       |
 *
 */

typedef struct _server_instance_
{
    struct _server_instance_ * next;   // matches lwm2m_list_t::next
    uint16_t    instanceId;            // matches lwm2m_list_t::id
    uint16_t    shortServerId;
    uint32_t    lifetime;
    uint32_t    defaultMinPeriod;
    uint32_t    defaultMaxPeriod;
    uint32_t    disableTimeout;
    bool        storing;
    char        binding[4];
} server_instance_t;

lwm2m_object_t* init_security_object();
lwm2m_object_t* init_server_object();
lwm2m_object_t* init_device_object();

/**
 * If you plan to implement a read-callback method, you need to be prepared for the case where the
 * server asks for all object ressources. Use this method to allocate memory and assign ressource
 * IDs to the array lwm2m_data_t elements.
 * @param dataArrayP This method will allocate memory that needs needs to be freed with lwm2m_free() again after use.
 * @param metaP The lwm2m object meta information.
 * @return Returns the count of ressources in metaP and therefore allocated lwm2m_data_t objects of dataArrayP or -1 if an error occured (no memory could be acquired). Can return 0 if there are no readable ressources in the object described by the meta object.
 */
int lwm2m_object_prepare_full_response(lwm2m_data_t** dataArrayP, lwm2m_object_meta_information_t* metaP);

/**
 *
 * @param destination The destination lwm2m_data_t
 * @param resP A meta ressource description (one of lwm2m_object_meta_information_t::ressources)
 * @param instanceP An lwm2m object instance
 */
uint8_t lwm2m_object_assign_single_value(lwm2m_data_t* destination, lwm2m_object_res_item_t* resP, void* instanceP);
