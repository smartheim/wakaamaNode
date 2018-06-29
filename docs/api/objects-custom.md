# Custom lwM2M objects

The last chapter introducted you to objects of the OMA lwM2M registry. WakaamaNode allows you to define
your own  custom lwm2m object. A unique object ID is necessary.

The next section explains some background information about the object ID namespace.
Thereafter you will find the C++ and C API for lwm2m object definitions.

## About the object ID namespace

The object id namespace is divided into several ObjectID Classes.

| Category | URN | Object ID | range | Description |
|----------|-----|-----------|-------|-------------|
| oma-label| urn:oma:lwm2m:oma:&lt;id&gt;:&lt;version&gt; | 0 - 1023 | Objects Produced by OMA. Only OMA can use this range |
| reserved | | 1024 - 2047 | Reserved for future use |
| ext-label | urn:oma:lwm2m:ext:&lt;id&gt;:&lt;version&gt; | 2048 - 10240 | Objects registered by 3rd party standards organisations or alliances |
| x-label | urn:oma:lwm2m: x:&lt;id&gt;:&lt;version&gt; | 10241 - 26240<br><br>26241 - 32768<br><br>32769 - 42768 | Objects registered by companies or individuals.<br><br>Objects Produced by Vendors to re-use<br><br>Block of objects reserved by vendors (Max 50). Private range, Objects will not be published |

If your use case is not yet considered within the registries objects, it is time to fill out an application for a new object.

For testing purposes, you can use one of the undefined ids (range 42769..65000). If possible, you should at least
make use of the [predefined resource ids (range: 2048..26240)](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html).

Define your custom objects either via C or the C++ interface.

## Object definition C++ API

Include `lwm2m/objects.h`.

### Lwm2mObject class

```cpp
class Lwm2mObject<ObjectID, DerivedObject, ObjectInstance>
```

Lwm2mObject is not to be used directly.
Inherit from Lwm2mObject to implement your own lwM2M object. Specify the **ObjectID**, for example "1024",
the derived object class and the associated object instance class.

To allow WakaamaNode to handle all read/write/execute handling for you, you need to describe the available
resources of an lwM2M object.
Example:

```
class MyObject: public Lwm2mObject<1024, MyObject, MyObjectInstance>
{
public:
    Resource(0, &MyObjectInstance::test, O_RES_RW) test;
};
```

Here a Readable/Writable(O_RES_RW) resource with ResourceID 0 is declared. It references the `&MyObjectInstance::test` class member of "MyObjectInstance"
for reading the resource value and writing to it.
The name of the class member is not relevant and should describe the resource, for example "power" or "volume".

The exact syntax and semantic of `Resource` is described further down in the [Resource class](#resource-class) section.

```cpp
/**
 * @param instance The object instance to add. See Lwm2mObjectInstance. May not be null.
 */
void Lwm2mObject::addInstance(Lwm2mObjectInstance * instance);
```

Add a [Lwm2mObjectInstance](#lwm2mobjectinstance-class) to your object.
The instance is automatically registered to the lwm2m server, if already connected.

```cpp
/**
 * @param instance The instance ID for the instance to remove. See Lwm2mObjectInstance.
 *        Nothing happens if the instance is not known to the object.
 */
void Lwm2mObject::removeInstance(uint16 instanceID);
```

Removes a [Lwm2mObjectInstance](#lwm2mobjectinstance-class) from your object.
The instance is automatically unregistered from the lwm2m server, if already connected.

```cpp
/**
 * @param lwm2mContext The Wakaama context.
 */
void Lwm2mObject::registerObject(void* lwm2mContext, bool allow_dynamic_instance_creation);
```

Registers the object to Wakaama.
The object is automatically registered to the lwM2M server, if already connected.

```cpp
/**
 * @param lwm2mContext The Wakaama context.
 */
void Lwm2mObject::unregisterObject(void* lwm2mContext);
```

Unregisters the object from Wakaama.

```cpp
/**
 * @param instance_id Instance ID
 */
virtual Lwm2mObjectInstance* createInstance(uint16_t instance_id);
```

If creating instances dynamically by the server or with the given ID is not supported return `nullptr`.
Return a working object instance with the given instance ID otherwise.

The default does nothing and returns a `nullptr`.

```cpp
/**
 * @param instance Object instance to delete
 * @return Return COAP_NO_ERROR if no error happened.
 */
virtual int deleteInstance(Lwm2mObjectInstance* instance);
```

Implement this function in your object class to allow to delete an object instance by the server.

```cpp
/**
 * @param lwm2mContext The Wakaama context.
 * @param object_instance_id Object instance id
 * @param res_id Resource id
 */
void resChanged(void* lwm2mContext, uint16_t object_instance_id, uint16_t res_id);
```

Call this method if you have changed a resource of the given instance with the given resource id.

```cpp
/**
 * @param instance Object instance that is going to be modified
 * @param res_id The resource that will get changed
 * @return Return true if change is accepted or false if change is denied.
 */
void* verifyWrite(Lwm2mObjectInstance* instance, uint16_t res_id);
```

Implement a function with the above signature and assign it to the `verifyWrite` object field to verify a change on an object instance resource.


### Lwm2mObjectInstance class

```cpp
class Lwm2mObjectInstance
```

Lwm2mObjectInstance is not to be used directly.
Inherit from this class to implement a data holder for an object instance.
Example:
```cpp
struct MyObjectInstance: public Lwm2mObjectInstance {
    uint8_t  firstResource;
}
```

Allowed data types are 8/16/32/64 bit unsigned/signed integers,
floats, doubles, booleans and unsigned/signed c-strings.

<span id="opaqueExample"></span>
CoAP and lwM2M support opaque resources.
WakaamaNode provides the `Opaque<N>` and `OpaqueIndirect` type.
See [Opaque Resources](#opaque-resources) for an example.

Resources can be executable. Declare a class member of type `Executable` that will be used
as function pointer. See [Executable Resource](#executable-resources) for an example.

The name of the class member is not relevant and should describe the resource, for example "power" or "volume".

Lwm2mObjectInstance does not have any methods.

### Resource class

```cpp
class Resource<ResID, ResourceValueReference, Operations>
```

Use the templated `Resource` class to describe the resource ID, reference to the member variable that stores the value and supported operations in this order.
**Until C++17, the syntax of declaring a Resource needs "(" instead of "<" brackets.**

Supported operations are O_RES_R (read only), O_RES_W (assign only), O_RES_RW (read/write).

### Executable Resources

For an executable resource, you do not need to specify the Operations, because it will always be O_RES_E.

In the following example a constructor is used to force the `MyObjectInstance`
user to assign a function:

```cpp
struct MyObjectInstance: public Lwm2mObjectInstance {
    Executable exec;
    
    MyObjectInstance(Executable anExecutableResourceFunction) : exec(anExecutableResourceFunction) {}
}
```

The corresponding object looks like this:

```
class MyObject: public Lwm2mObject<1024,MyObject,MyObjectInstance>
{
public:
    Resource<0, &MyObjectInstance::exec> exec;
};
```

### Opaque Resources
If you have an opaque resource, you have two options. Either you directly reserve enough space in-place via the `Opaque<N>`
templated class, or you let the class variable point to a memory location, which basically means an indirect memory access. Use `OpaqueIndirect` in this case.
An example:

```cpp
char memory[100];

struct MyObjectInstance: public Lwm2mObjectInstance {
   // Equals an in-place array with the size of 20 bytes
   Opaque<20> opaqueRes;

   // Similar to Opaque, but will be designated as string resource
   PreallocString<20> preallocStringRes;   

   // You need to assign the OpaqueIndirect::data pointer a memory location.
   OpaqueIndirect opaqueIndirectRes;
   
   MyObjectInstance() : opaqueIndirectRes{100,0,memory} {}
};
```

### Read from / Write to resource value function

Instead of storing data in member variables of your object instance, you can make the library to retrieve
the resource value from a function call, or store a new resource value by calling a function.

In the example of an object instance below you can see all three types (read from function, write to function, read/write from/to function):

```cpp
struct MyObjectInstance: public Lwm2mObjectInstance {
    IndirectRead<int8_t> test_read_fun_int8;
    IndirectRead<uint32_t> test_read_fun_uint32;
    
    IndirectRead<const char*> test_read_fun_string;
    IndirectWrite<const char*> test_write_fun_string;
    IndirectReadWrite<const char*> test_readWrite_fun_string;
} your_object_instance_t;
```

As you can see, you will use the templated classes `IndirectRead`, `IndirectWrite` and `IndirectReadWrite`.

The library will crash, if the function pointer is dangling / not assigned to a valid function!

The signature of the read and write methods will always pass the object instance as first parameter,
see the definition of `my_read_method` and `string_write_method` in the example below.

An example object looks like this, with a constructor setting the function pointers:

```
uint32_t my_read_method(Lwm2mObjectInstance*) { return 12; }

void string_write_method(Lwm2mObjectInstance*, const char* v) {}

class MyObject: public Lwm2mObject<1024,MyObject,MyObjectInstance>
{
public:
    Resource(1, &MyObjectInstance::test_read_fun_uint32) test_read_fun_uint32;
    Resource(3, &MyObjectInstance::test_write_fun_string) test_write_fun_string;
    
    MyObject(IndirectRead<uint32_t> readfun, IndirectRead<uint32_t> writefun) :
        test_read_fun_uint32(readfun), test_write_fun_string(writeFun) {}
};

MyObject o(my_read_method, string_write_method);
```


## Object definition C API

Include `lwm2m/c_objects.h`.

```cpp
/**
 * @param context   The wakaama context.
 * @param object   The wakaama lwm2m object with meta information attached.
 * @param allow_dynamic_instance_creation Allows or disallows the use of lwm2m_object_instances_add(). Heap memory will be used.
 * @return The error code or COAP_NO_ERROR if no error.
 */
int lwm2m_add_initialize_object(lwm2m_context_t * contextP,
                                lwm2m_object_t* object,
                                bool allow_dynamic_instance_creation);
```
Initializes an lwm2m object, created with OBJECT_META().
This will also add the object to the wakaama object registry. If the client
is already connected to a server, the server will be notified.

Remove an object with lwm2m_remove_object(context, object_id) again.

```cpp
/**
 * @param context   The wakaama context.
 * @param object The lwm2m_object.
 * @param instance An object instance.
 */
void lwm2m_object_instance_add(lwm2m_context_t * context, lwm2m_object_t* object, lwm2m_list_t* instance);
```
Add an instance to an object.

Ideally you do this before you connect to a server and before you call `lwm2m_add_initialize_object`.
The server will be notified of the updated object otherwise.

A lwm2m object instance consists of one ore more ressources identified by their ressource ids.
A ressource may be an uint8, int8, uint16, int16, uint32, int32, uint64, int64, double, c-string.

Please be aware that your object instance
have to "inherit" lwm2m_list_t::next and lwm2m_list_t::id like in the following example:

```cpp
typedef struct {
   struct _prv_instance_next; // matches lwm2m_list_t::next
   uint16_t shortID;             // matches lwm2m_list_t::id
   ... Your members are defined here...
} your_object_instance_t;
```

If you implement any object with an id registered at
[OMA Object & Resource Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html),
your object instances have to provide all of the defined ressources

### OBJECT_META

To allow WakaamaNode to

- read from resources,
- write to resources and
- execute resources

you have to provide a machine readable description. You do this by definining a
lwm2m_object_meta_information_t. Imagine you have defined an object instance looking like below:

```cpp
typedef struct {
   struct _prv_instance_next; // matches lwm2m_list_t::next
   uint16_t shortID;          // matches lwm2m_list_t::id
   
   uint8_t test;
   ExecutableType exec;
   double dec;
} your_object_instance_t;
```

Use OBJECT_META() to describe your object to the library:

```cpp
OBJECT_META(your_object_instance_t, test_object, 1024, test_object_write_verify_cb,
    {0, O_RES_RW,O_RES_UINT8 , offsetof(your_object_instance_t,test)},
    {1, O_RES_E ,O_RES_EXEC  , offsetof(your_object_instance_t,exec)},
    {2, O_RES_RW,O_RES_DOUBLE, offsetof(your_object_instance_t,dec)}
);
```

Which results in a `test_object` object declaration as well as a pointer to it `test_objectP`, that can be handed over to `lwm2m_add_initialize_object`.

OBJECT_META expects the object instance (here: `your_object_instance_t`),
and the variable name for the object via the first and second argument.

The third argument is the object ID.

The 4th argument may be set to NULL. Otherwise set it to a callback method which is called on
a write to your object instance. You may react on a write in this method and you may deny the write if the new value
is not in range of your allowed values. The callback method needs this signature:

`bool test_object_write_verify_cb(lwm2m_list_t* instance, uint16_t changed_res_id);`

The subsequent arguments describe the ressources of your object instances. Each entry is enclosed in curly brackets and consists of these values:

1. The id of the ressource
2. The Resource access modifier (see next sections).
3. The Resource type (see next sections).
4. Member pointer

### Resource Access modifier
You can use the following access modifiers:

* **O_RES_R**: Read only access
* **O_RES_W**:Write only access
* **O_RES_RW**: Read/Write access
* **O_RES_E**: Makes this resource executable
* **O_RES_E|O_RES_R**: Reads the resource value from a function
* **O_RES_E|O_RES_W**: Writes the resource value to a function
* **O_RES_E|O_RES_RW**: The resource value is read from and written to a function

### Resource type

You can use the following types:

```cpp
typedef enum _lwm2m_object_util_type_ {
    O_RES_EXEC   = 0, ///< Executable resource == no type
    O_RES_BOOL   = 1, ///< A boolean value
    O_RES_DOUBLE = 2, ///< A floating point decimal value
    O_RES_INT8   = 3, ///< Int with range [-128,127]
    O_RES_UINT8  = 4, ///< Int with range [0,255]
    O_RES_INT16  = 5, ///< Int with range [-32000,32000]
    O_RES_UINT16 = 6, ///< Int with range [0,65500]
    O_RES_INT32  = 7, ///< Int with range [-2^31,2^31-1]
    O_RES_UINT32 = 8, ///< Int with range [0, 2^32-1]
    O_RES_INT64  = 9, ///< Int with range [-2^63, 2^63-1]
    O_RES_STRING          = 10, ///< Readonly c-string
    O_RES_STRING_PREALLOC = 11, ///< preallocated space. To be used with OpaqueType(N) in C or Opaque<N> in C++.
    O_RES_OPAQUE_INDIRECT = 12, ///< To be used with type OpaqueIndirect
    O_RES_OPAQUE_PREALLOC = 13  ///< preallocated space. To be used with OpaqueType(N) in C or Opaque<N> in C++.
} lwm2m_object_util_type_t;
```

### Executable Resources

An executable resource expects a function pointer in your object instance struct. Use the special `ExecutableType` type:

```cpp
typedef struct {
   struct _prv_instance_next; // matches lwm2m_list_t::next
   uint16_t shortID;          // matches lwm2m_list_t::id
   ExecutableType myExecRes;
} your_object_instance_t;
```

The signature of your executabe function pointer should be: `void myFun();`.

### Opaque Resources
If you have an opaque resource, you have two options. Either you directly reserve enough space in-place via the `OpaqueType(N)`
macro, or you let the struct variable point to a memory location, which basically means an indirect memory access. Use `OpaqueIndirect` in this case.
An example:

```cpp
typedef struct {
   struct _prv_instance_next; // matches lwm2m_list_t::next
   uint16_t shortID;          // matches lwm2m_list_t::id
   
   // Equals an in-place array with the size of 20 bytes
   OpaqueType(20) opaqueRes;
   
   // You need to assign the OpaqueIndirect::data pointer a memory location.
   OpaqueIndirect opaqueIndirectRes;
} your_object_instance_t;
```

Before you can actually use `your_object_instance_t`, you need to initialize opaque members.

* Set the reserved size: For `opaqueRes` this is done by: `opaqueRes.reserved_len = 20;`.
* Set the used size to 0: `opaqueRes.used_len = 0;`. This value will be updated on a write access.
* Set the function pointer for `OpaqueIndirect`: `opaqueIndirectRes.data = myMemory;`.

The C-API does not reallocate memory. If there's not enough space, a **COAP_413_ENTITY_TOO_LARGE** error code is returned.

### Read from / Write to resource value function

Instead of storing data in member variables of your object instance, you can make the library to retrieve
the resource value from a function call, or store a new resource value by calling a function.

In the example of an object instance below you can see all three types (read from function, write to function, read/write from/to function):

```cpp
typedef struct {
    struct _prv_instance_next; // matches lwm2m_list_t::next
    uint16_t shortID;          // matches lwm2m_list_t::id
   
    IndirectReadType(int8_t,test_read_fun_int8);
    IndirectReadType(uint32_t,test_read_fun_uint32);
    
    IndirectReadType(const char*,test_read_fun_string);
    IndirectWriteType(const char*,test_write_fun_string);
    IndirectReadWriteType(const char*) test_readWrite_fun_string;
} your_object_instance_t;
```

As you can see, you will use the macros `IndirectReadType`, `IndirectWriteType` and `IndirectReadWriteType`.
The first two expect a parameter tuple (type, variable name). The third expects the type only.

The library will crash, if the function pointer is dangling / not assigned to a valid function!

Before you can actually use `your_object_instance_t`, you need to initialize indirect read/write members.

For the example above this would look like:
```cpp
    your_object_instance_t.test_read_fun_int8 = readFun8;
    your_object_instance_t.test_read_fun_uint32 = readFun32;
    
    your_object_instance_t.test_read_fun_string = readFunStr;
    your_object_instance_t.test_write_fun_string = writeFunStr;
    your_object_instance_t.test_readWrite_fun_string.read = readFunStr;
    your_object_instance_t.test_readWrite_fun_string.write = writeFunStr;
```
