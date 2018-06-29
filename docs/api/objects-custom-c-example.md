# Example

If you are going to use a lwM2M object, that is defined in the [OMA lwM2M registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html),
head over to the [Registry objects](/api/objects-registry.md) page.
WakamaNode provides ready-to-use, auto-generated c++ classes for all those objects.

For this example, we assume the following custom lwM2M object definition:

| Object | ID   | Multiple Instances | Mandatoty |
|--------|------|--------------------|-----------|
| Test   | 1024 | Yes                | No        |


Ressources:

| Name | ID | Operations |  Type   | Range | Description      |
|------|:--:|------------|---------|-------|-----------------------|
| test |  1 |    R/W     | Integer | 0-128 |                       |
| exec |  2 |     E      |         |       |                       |
| dec  |  3 |    R/W     |  Float  |       |                       |

If you use the object definition API, you only need to provide an object description (meta object data)
and all read/write/execute handling is done for you. 

The meta object data is usually definied in your custom `my_object.c`. We assume the following custom object:

```cpp
typedef struct
{
    struct test_object_instance_t * next;   // matches lwm2m_list_t::next
    uint16_t shortID;                       // matches lwm2m_list_t::id

    uint8_t  test;
    Executable    execF; // function pointer
    double   dec;
    int16_t  sig;
} test_object_instance_t;
```

With the help of the ``OBJECT_META(object_struct, result_variable_name, write_verify_callback, ressources...)`` macro we define the object description:

```cpp
OBJECT_META(test_object_instance_t, test_object_meta, test_object_write_verify_cb,
    {0, O_RES_RW,O_RES_UINT8     , offsetof(test_object_instance_t,test)},
    {1, O_RES_E ,0               , offsetof(test_object_instance_t,execF)},
    {2, O_RES_RW,O_RES_DOUBLE    , offsetof(test_object_instance_t,dec)},
    {3, O_RES_RW,O_RES_INT16     , offsetof(test_object_instance_t,sig)}
);

lwm2m_object_meta_information_t *test_object_get_meta() {
    return &test_object_metaP;
}
```

Remember that we do not use the `result_variable_name` (in this case `test_object_meta`) directly.
It is of type `lwm2m_object_meta_information_t`,
which is not understood by the WakamaNode and Wakaama API. But thankfully `OBJECT_META` also defines
a pointer of type `lwm2m_object_t`, which is named like the given `result_variable_name` with a **P** suffix.
In this case: `test_object_metaP`.

The ressources are described each with an entry of the following form:
`{RES_ID, RES_ACCESS, RES_TYPE, offsetof(object_struct, res_name)}`.

### Input validation

If you have looked carefully at the object definition above, you see that _test_ is restricted to 0..128.
This is less that the data type allows, so we have to provide an input validation method and
make it known to the meta object via the third argument (write_verify_callback).

For the above example such a method could look like this:

```cpp
bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id) {
    test_object_instance_t* i = (test_object_instance_t*)instance;
    // Return false for an invalid object
    if(changed_res_id==1 && i->test > 128) return false;
    // If we return true, the new value will be applied to the instance object for us.
    return true;
}
```

### React to resource write operations

You may "misuse" the validation function to react on an altered resource. Another way is to implement
`void lwm2m_resource_changed_event(uint16_t object_id, uint16_t object_instance_id, uint16_t resource_id)`
and have a giant switch for all resources.

### Add object and object instances

First define a method in your `my_object.c` unit that creates a new object instance, like in the code below:

```cpp
lwm2m_list_t* led_object_create_instances() {
    test_object_instance_t * targetP = (test_object_instance_t *)malloc(sizeof(test_object_instance_t));
    if (NULL == targetP) return NULL;
    memset(targetP, 0, sizeof(test_object_instance_t));
    targetP->shortID = 0; // Assign instance ID
    targetP->state = 0;
    return (lwm2m_list_t*)targetP;
}
```

In your `my_object.h` file, make the method declaration available:

```cpp
#pragma once

lwm2m_object_meta_information_t* led_object_get_meta();
lwm2m_list_t* led_object_create_instances() ;
```

In you application file, create the object and instance and register each.

```cpp
#include "my_object.h"

void setup() {
    // Create object
    lwm2m_object_t* test_object = lwm2m_object_create(5850, true, led_object_get_meta());
    // Add instance
    lwm2m_object_instances_add(test_object, led_object_create_instances());
    // Register object
    lwm2m_add_object(client_context, test_object);

}
```

You can register objects either before or after you are connected to a lwM2M server. If you are already connected,
the register call will be a little bit more expensive, because the object need to be published to the server.

### Remove object or object instance

```cpp
#include "my_object.h"

lwm2m_object_t* test_object = ...;

void exit() {
    lwm2m_object_free(test_object);
}
```
