#pragma once

/*
 * Classes, Methods and Enums defined in this file are for easily creating a new lwM2M object definition
 * and object instances. This is for the C++-API.
 */

#include "wakaama/liblwm2m.h"
#include "lwm2m_objects.h" // We need the enums of the C-API as well
#include <inttypes.h>
#include <string.h>
#include "macro_helper.h"
#include <type_traits>
#include <functional>

// The Opaque type. OpaqueIndirect is defined by the C-API.
template<int N>
struct Opaque {
    uint16_t reserved_len=N;
    uint16_t used_len=0;
    uint8_t data[N];

    template<typename T>
    inline void copy(T* d, int size) {
        memcpy(data, d, size);
        used_len = size;
    }
};

// Preallocated string
template<int N>
struct PreallocString {
    uint16_t reserved_len=N;
    uint16_t used_len=0;
    uint8_t data[N];

    template<typename T>
    inline void copy(T* d) {
        used_len = strlen(d);
        memcpy(data, d, used_len+1);
    }
};

template<class T>
struct DynArray {
    T data;
    int len;
    DynArray(T& value, int len) : data(value),len(len){}
};

// The read indirect type
template<class T>
using IndirectRead = T (*)();

// The write indirect type
template<class T>
using IndirectWrite = void (*)(DynArray<T>&);

// The read/write indirect type
template<class T>
struct IndirectReadWrite {
    typedef T type;
    IndirectRead<T> read;
    IndirectWrite<T> write;
    IndirectReadWrite() = default;
    IndirectReadWrite(IndirectRead<T> read, IndirectWrite<T> write) : read(read),write(write){}
};

// The executable type
using Executable = std::add_pointer<void(uint8_t * buffer,int length)>::type;

class Lwm2mObjectInstance : public lwm2m_list_t {
public:
    Lwm2mObjectInstance() : lwm2m_list_t{nullptr,0} {}
    template<class T> inline T* as() {return reinterpret_cast<T*>(this);}
};

// The verify write callback of Lwm2mObjectBase
using VerifyWrite = bool (*)(Lwm2mObjectInstance*, uint16_t);

class Lwm2mObjectBase {
    // Allow offset_of_impl to access the protected constructor
    template<typename T1, typename T2> friend struct offset_of_impl;
public:
    lwm2m_object_t object{};
    VerifyWrite verifyWrite;
    struct alignas(alignof (uintptr_t)) Sizes {
        const uint16_t object;
        const uint16_t object_instance;
    };
    const Sizes sizes;
    void resChanged(lwm2m_context_t * contextP, uint16_t object_instance_id, uint16_t res_id);

    static Lwm2mObjectBase* getBase(lwm2m_object_t* p) {
        const uintptr_t objectP = reinterpret_cast<uintptr_t>(p);
        return reinterpret_cast<Lwm2mObjectBase*>(objectP - offset_of(&Lwm2mObjectBase::object));
    }
    lwm2m_object_res_item_t* resource(uint16_t i) {
        const uint16_t res_len = resources_len();
        const uintptr_t endOfObject = reinterpret_cast<uintptr_t>(this) + sizes.object;
        return reinterpret_cast<lwm2m_object_res_item_t*>(endOfObject - sizeof(lwm2m_object_res_item_t)*(res_len-i));
    }
    constexpr uint16_t resources_len() const {
        return (sizes.object-sizeof(Lwm2mObjectBase))/sizeof(lwm2m_object_res_item_t);
    }

    lwm2m_object_res_item_t* find_ressource(uint16_t id) {
        for (uint16_t index = 0; index < resources_len(); index++) {
            if (resource(index)->ressource_id == id) {
                return resource(index);
            }
        }

        return nullptr;
    }

    constexpr Lwm2mObjectBase(uint16_t derived_size, uint16_t object_instance_size) :
        verifyWrite(defaultVerify), sizes{derived_size,object_instance_size} {}

    void addInstance(lwm2m_context_t * contextP, Lwm2mObjectInstance* instance);
    lwm2m_list_t* removeInstance(lwm2m_context_t * contextP, uint16_t instance_id);
    int registerObject(lwm2m_context_t * contextP, bool allow_dynamic_instance_creation);

    virtual Lwm2mObjectInstance* createInstance(uint16_t instance_id);
    virtual int deleteInstance(Lwm2mObjectInstance* instance);

    protected:
    constexpr static bool defaultVerify(Lwm2mObjectInstance*,uint16_t) { return true; }
    constexpr Lwm2mObjectBase() : verifyWrite(defaultVerify), sizes{0,0} {}
};

template<uint16_t objectID, class Derived, class ObjectInstance>
class Lwm2mObject : public Lwm2mObjectBase {
public:
    Lwm2mObject() :Lwm2mObjectBase(sizeof(Derived), sizeof(ObjectInstance)) {object.objID=objectID;}
};

////// Fallback with error
template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations, typename Enable = void>
class ResourceRaw : public lwm2m_object_res_item_t {
public:
    ResourceRaw() = delete;
};

////// For opaque and string types

template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations>
    class ResourceRaw<ResID,ObjectInstance,ResourceType,offset,Operations,
            typename std::enable_if<std::is_base_of<OpaqueIndirect, ResourceType>::value, ResourceType>::type> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_OPAQUE_INDIRECT,offset} {}
};

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
    class ResourceRaw<ResID,ObjectInstance,OpaqueIndirect,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_OPAQUE_INDIRECT,offset} {}
};

template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,ResourceType,offset,Operations,
        typename std::enable_if<is_base_of_template<ResourceType, Opaque>::value>::type> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_OPAQUE_PREALLOC,offset} {}
};

template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,ResourceType,offset,Operations,
        typename std::enable_if<is_base_of_template<ResourceType, PreallocString>::value>::type> :
        public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING_PREALLOC,offset} {}
};

////// For all other allowed types

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,const char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,unsigned char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,const unsigned char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,Executable,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,O_RES_E,O_RES_EXEC,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,bool,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_BOOL,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,double,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_DOUBLE,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,float,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_DOUBLE,offset} {}
};

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int8_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT8,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint8_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT8,offset} {}
};

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int16_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT16,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint16_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT16,offset} {}
};

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int32_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT32,offset} {}
};
template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint32_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT32,offset} {}
};

template<uint16_t ResID, class ObjectInstance, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int64_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT64,offset} {}
};

//////////// For indirect resources, where we do not need to define operations ///////////

// Fallback for non indirect resources
template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations,class Enable = void>
class IndirectResourceRaw : public ResourceRaw<ResID,ObjectInstance,ResourceType,offset,Operations> {

};

// enable_if prevents this template specialisation to match an Executable
template<uint16_t ResID, class ObjectInstance, size_t offset, typename SubType, uint8_t Operations>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectRead<SubType>,offset,Operations,
        typename std::enable_if<!std::is_same<SubType,void>::value>::type> :
        public ResourceRaw<ResID,ObjectInstance,SubType,offset,O_RES_R|O_RES_E> {
};

template<uint16_t ResID, class ObjectInstance, size_t offset, typename SubType, uint8_t Operations>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectWrite<SubType>,offset,Operations> :
        public ResourceRaw<ResID,ObjectInstance,SubType,offset,O_RES_W|O_RES_E> {
};

template<uint16_t ResID, class ObjectInstance, size_t offset, typename SubType, uint8_t Operations>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectReadWrite<SubType>,offset,Operations> :
        public ResourceRaw<ResID,ObjectInstance,SubType,offset,O_RES_RW|O_RES_E> {
};

// Until C++17 where we have auto for template arguments this macro is necessary
/*
#define Resource(ResID, MemberPtr, ...) \
  IndirectResourceRaw<ResID, baseof_member_pointer<decltype(MemberPtr)>::type, \
            remove_member_pointer<decltype(MemberPtr)>::type, \
            offset_of(MemberPtr) __VA_OPT__(,) __VA_ARGS__>
*/

// Until gnuc++14/c++20 where we can use __VA_OPT__
#define Resource_2(ResID, MemberPtr) \
  IndirectResourceRaw<ResID, baseof_member_pointer<decltype(MemberPtr)>::type, \
            remove_member_pointer<decltype(MemberPtr)>::type, \
            offset_of(MemberPtr), 0>

#define Resource_3(ResID, MemberPtr, Operations) \
  IndirectResourceRaw<ResID, baseof_member_pointer<decltype(MemberPtr)>::type, \
            remove_member_pointer<decltype(MemberPtr)>::type, \
            offset_of(MemberPtr), Operations>

// The interim macro that simply strips the excess and ends up with the required macro
#define Resource_X(x,A,B,C,D,FUNC, ...)  FUNC
#define Resource(...)                    Resource_X(,##__VA_ARGS__,\
                                          Resource_4(__VA_ARGS__),\
                                          Resource_3(__VA_ARGS__),\
                                          Resource_2(__VA_ARGS__),\
                                          Resource_1(__VA_ARGS__),\
                                          Resource_0(__VA_ARGS__)\
                                         )
