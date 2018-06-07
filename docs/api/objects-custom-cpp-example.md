# Example

If you are going to use a lwM2M object, that is defined in the [OMA lwM2M registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html),
head over to the [Registry objects](/api/objects-registry.md) page.
WakamaNode provides ready-to-use, auto-generated c++ classes for all those objects.

For this example, we assume the following custom lwM2M object definition:

| Object | ID   | Multiple Instances | Mandatoty |
|--------|------|--------------------|-----------|
| Test   | 1024 | Yes                | No        |


Ressources:

| Name | ID | Operations | Mult Inst | Mandatory |  Type   | Range | Description      |
|------|:--:|------------|:---------:|:---------:|---------|-------|-----------------------|
| test |  0 |    R/W     |    No     |    Yes    | Integer | 0-128 |                       |
| exec |  1 |     E      |    No     |    Yes    |         |       |                       |
| dec  |  2 |    R/W     |    No     |    Yes    |  Float  |       |                       |
| sig  |  3 |    R/W     |    No     |    Yes    | Integer |       | 16-bit signed integer |
| text |  4 |    R/W     |    No     |    Yes    | String  |       | char* c-string        |
| opaq |  5 |     W      |    No     |    Yes    | Opaque  |32 Byte| void* data            |
| read |  9 |     R      |    No     |    Yes    | Integer |       | Read value from method|

If you use the C++ object definition API, you only need to provide an object description (meta object data)
and all read/write/execute handling is done for you. 

Create an object instance class, that serves as data holder for each individual instance.

```cpp
using MyReadIntFunction = int (*)();

struct MyObjectInstance: public Lwm2mObjectInstance {
    uint8_t  test;
    Executable exec;
    double   dec;
    int16_t  sig;
    
    char*    text;

    Opaque<32> opaque;

    IndirectRead<int>    read;
    
    // Force the MyObjectInstance user to assign a read and execute funtion. We don't want to crash!
    MyObjectInstance(MyReadIntFunction* readF, MyExecuteFunction* execF) : exec(execF) read(readF) {}
};
```

You inherit from `Lwm2mObjectInstance` for the object instance data holder.

Declare an object class that describes object 1024 to the library:

```cpp
// Object with LwM2M ID 1024
class MyObject: public Lwm2mObject<1024,MyObject,MyObjectInstance>
{
public:
    Resource(0, &MyObjectInstance::test, O_RES_RW) test;
    Resource(1, &MyObjectInstance::exec, O_RES_E ) exec;
    Resource(2, &MyObjectInstance::dec,  O_RES_RW) dec;
    Resource(3, &MyObjectInstance::sig,  O_RES_RW) sig;

    Resource(4, &MyObjectInstance::text, O_RES_RW) text;

    Resource(5, &MyObjectInstance::opaque,O_RES_W) opaque;
    
    // You don't need to specify the operation, if it is a
    // IndirectRead, IndirectWrite, IndirectReadWrite type
    Resource(9, &MyObjectInstance::read) read;

    MyObject() : test([](uint8_t val){return val<=128;});

    // Allow dynamic new instances. Default is to not allow new instances
    virtual bool allowNewInstance(uint16_t instanceID) override { return true; } 
};
```

Inherit from `Lwm2mObject` and specify the object ID as template parameter for your object class.
Notice the `#pragma pack`, which is important!

Use the templated `Resource` class to describe the resource ID, reference to the member variable and supported operations in this order.

Supported operations are O_RES_R (read only), O_RES_W (assign only), O_RES_RW (read/write), O_RES_E (executable).

## Read resource value from function
It is possible to read a resource value from a function instead of a classes member variable.
Use `PollingResource` and define the resource ID and resource type.

In this example `my_read_method` would look like this:

```cpp
int my_read_method() { return 12; }
```

## Input validation
If you have looked carefully at the object definition, you see that _test_ is restricted to 0..128:
```cpp
              Supported    Multiple
  Name | ID | Operations | Instances | Mandatory |  Type   | Range |
  test |  0 |    R/W     |    No     |    Yes    | Integer | 0-128 |
```

This is less that the data type allows, so we have to provide an input validation method. Thankfully, the
`Resource` classes constructor takes a validation function.

We provide it in the `Test` constructor as a lambda function, that takes an input value `val` and returns `false` if the value is greater than 128:

```cpp
MyObject() : test([](uint8_t val){return val<=128;});
```

## React to resource write operations

You may "abuse" the validation function to react on an altered resource.

Another way is a giant switch in
a defined `void lwm2m_resource_changed_event(uint16_t object_id, uint16_t object_instance_id, uint16_t resource_id)`.
If you do not implement this method somewhere, a default no-op method will be used.

## Add object and object instances

An example for adding an object `MyObject` with one instance `MyObjectInstance` is provided below.


```cpp
MyObject myObj(false);

int my_read_method() { return 12; }
MyObjectInstance myInstance(my_read_method);

void setup() {
    myObj.addInstance(lwm2mContext, &myInstance);
    myObj.registerObject(lwm2mContext);
}
```

You can register objects either before or after you are connected to a lwM2M server. If you are already connected,
the register call will be a little bit more expensive, because the object need to be published to the server.

## Remove object or object instance

```cpp
MyObject myObj(false);

int my_read_method() { return 12; }
MyObjectInstance myInstance(my_read_method);

void exit() {
    myObj.removeInstance(lwm2mContext, myInstance.instanceID);
    myObj.unregisterObject(lwm2mContext);
}
```
