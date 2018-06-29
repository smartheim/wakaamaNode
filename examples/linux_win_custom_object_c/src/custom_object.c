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
 *  host |  1 |    R       |    No     |    Yes    | String  |       |       |  Host name            |
 *  name |  2 |    R       |    No     |    Yes    | String  |       |       |  Screen name          |
 *
 */

#include "custom_object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct _test_object_instance_
{
    /*
     * The first two are mandatories and represent the pointer to the next instance and the ID of this one. The rest
     * is the instance scope user data
     */
    struct test_object_instance_t * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id
    bool     state;
    char*    host;
    char*    name;
} test_object_instance_t;

// We want to react to a write of the "state" ressource, therefore use the write_verify callback.
bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);

// Always do this in an implementation file not a header file
OBJECT_META(test_object_instance_t, test_object, 1024, test_object_write_verify_cb,
    {0, O_RES_RW,O_RES_BOOL,          offsetof(test_object_instance_t,state)},
    {1, O_RES_R,O_RES_STRING, offsetof(test_object_instance_t,host)},
    {2, O_RES_R,O_RES_STRING, offsetof(test_object_instance_t,name)}
)

static test_object_instance_t instance;

lwm2m_object_t *get_screen_object() {
    return test_objectP;
}

lwm2m_list_t* get_an_instance() {
    memset(&instance, 0, sizeof(test_object_instance_t));
    instance.shortID = 0;
    instance.state = 0;
    instance.host = "Example host";
    instance.name = "First instance";
    return (lwm2m_list_t*)&instance;
}

bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    if(changed_res_id==0) {
        printf("Changing resource 0 to %i\n", i->state);
    }

    return true;
}

