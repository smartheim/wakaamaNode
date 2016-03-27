/*
 Released to the public domain.

 David Graeff <david.graeff@web.de>
*/

/*
 * Implements an object for testing purpose
 *
 *                 Multiple
 * Object |  ID  | Instances | Mandatoty |
 *  Test  | 1024 |    Yes    |    No     |
 *
 *  Ressources:
 *              Supported    Multiple
 *  Name | ID | Operations | Instances | Mandatory |  Type   | Range | Units |      Description      |
 *  test |  0 |    R/W     |    No     |    Yes    | Integer | 0-128 |       |                       |
 *  exec |  1 |     E      |    No     |    Yes    |         |       |       |                       |
 *  dec  |  2 |    R/W     |    No     |    Yes    |  Float  |       |       |                       |
 *  sig  |  3 |    R/W     |    No     |    Yes    | Integer |       |       | 16-bit signed integer |
 *
 */

#include "test_object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct _test_object_instance_
{
    /*
     * The first two are mandatories and represent the pointer to the next instance and the ID of this one. The rest
     * is the instance scope user data (uint8_t test in this case)
     */
    struct test_object_instance_t * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id
    uint8_t  test;
    double   dec;
    int16_t  sig;
} test_object_instance_t;

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {O_RES_RW|O_RES_UINT8,  offsetof(test_object_instance_t,test)},
    {O_RES_E                       ,  0},
    {O_RES_RW|O_RES_DOUBLE, offsetof(test_object_instance_t,dec)},
    {O_RES_RW|O_RES_INT16,  offsetof(test_object_instance_t,sig)}
);

lwm2m_object_meta_information_t *test_object_get_meta() {
    return &test_object_meta;
}

lwm2m_list_t* test_object_create_instance(uint16_t instance_id) {
    test_object_instance_t * targetP = (test_object_instance_t *)malloc(sizeof(test_object_instance_t));
    if (NULL == targetP) return NULL;
    memset(targetP, 0, sizeof(test_object_instance_t));
    targetP->shortID = instance_id;
    targetP->test    = 20 + instance_id;
    targetP->dec     = -30 + instance_id + (double)instance_id/100.0;
    targetP->sig     = 0 - instance_id;
    return (lwm2m_list_t*)targetP;
}

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==1 && i->test > 128) return false;

    return true;
}

uint8_t test_object_execute_cb(uint16_t instanceId,
                        uint16_t resourceId,
                        uint8_t * buffer,
                        int length,
                        lwm2m_object_t * objectP)
{
    if (NULL == lwm2m_list_find(objectP->instanceList, instanceId))
        return COAP_404_NOT_FOUND;

    if (resourceId == 1) {
        fprintf(stdout, "\r\n-----------------\r\n"
                        "Execute on %hu/%d/%d\r\n"
                        " Parameter (%d bytes):\r\n",
                        objectP->objID, instanceId, resourceId, length);
        //prv_output_buffer((uint8_t*)buffer, length);
        fprintf(stdout, "-----------------\r\n\r\n");
        return COAP_204_CHANGED;
    }
    return COAP_405_METHOD_NOT_ALLOWED;
}
