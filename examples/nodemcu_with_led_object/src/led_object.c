/*
 MIT Licence
 David Graeff <david.graeff@web.de>
*/

/*
 * Implements an object for screen control
 *
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  state|  0 |    R/W     |    No     |    Yes    |   Bool  |       |       |                       |
 *
 */

#include "led_object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <Arduino.h>


typedef struct _test_object_instance_
{
    /*
     * The first two are mandatories and represent the pointer to the next instance and the ID of this one. The rest
     * is the instance scope user data
     */
    struct test_object_instance_t * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id
    bool     state;
} test_object_instance_t;

// We want to react to a write of the "state" ressource, therefore use the write_verify callback.
bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

// Always do this in an implementation file not a header file
OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {0, O_RES_RW|O_RES_BOOL,  offsetof(test_object_instance_t,state)}
);

lwm2m_object_meta_information_t *led_object_get_meta() {
    return &test_object_meta;
}

lwm2m_list_t* led_object_create_instances() {
    test_object_instance_t * targetP = (test_object_instance_t *)malloc(sizeof(test_object_instance_t));
    if (NULL == targetP) return NULL;
    memset(targetP, 0, sizeof(test_object_instance_t));
    targetP->shortID = 0;
    targetP->state = 0;
    return (lwm2m_list_t*)targetP;
}

#define LED_ON LOW
#define LED_OFF HIGH

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==0) {
        if (i->state)
            digitalWrite(LED_BUILTIN, LED_ON);
        else
            digitalWrite(LED_BUILTIN, LED_ON);
    }

    return true;
}

