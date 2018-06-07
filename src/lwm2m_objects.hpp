#pragma once
#ifdef __cplusplus

/*
 * Classes, Methods and Enums defined in this file are for easily creating a new lwM2M object definition
 * and object instances. This is for the C++-API.
 */

#include "wakaama/liblwm2m.h"
#include <inttypes.h>
#include "lwm2m_objects.h" // We need the enums of the C-API as well
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

// The read indirect type
template<class T>
using IndirectRead = T (*)();

// The write indirect type
template<class T>
using IndirectWrite = void (*)(T&);

// The read/write indirect type
template<class T>
struct IndirectReadWrite {
    IndirectRead<T> read;
    IndirectWrite<T> write;
    IndirectReadWrite() = default;
    IndirectReadWrite(IndirectRead<T> read, IndirectWrite<T> write) : read(read),write(write){}
};

// The executable type
using Executable = std::add_pointer<void()>::type;

class Lwm2mObjectInstance : public lwm2m_list_t {
public:
    Lwm2mObjectInstance() : lwm2m_list_t{nullptr,0} {}
};

// The verify write callback of Lwm2mObjectBase
using VerifyWrite = bool (*)(Lwm2mObjectInstance*, uint16_t);

class Lwm2mObjectBase {
    // Allow offset_of_impl to access the protected constructor
    template<typename T1, typename T2> friend struct offset_of_impl;
public:
    lwm2m_object_t object{0};
    VerifyWrite verifyWrite;
    const uint16_t object_size;
    const int object_instance_size;

    static Lwm2mObjectBase* getBase(lwm2m_object_t* p) {
        return (Lwm2mObjectBase*)((char*)p - offset_of(&Lwm2mObjectBase::object));
    }
    lwm2m_object_res_item_t* resource(uint16_t i) {
        const uint16_t res_len = resources_len();
        const char* endOfObject = (char*)this + object_size;
        return (lwm2m_object_res_item_t*)(endOfObject - sizeof(lwm2m_object_res_item_t)*(res_len-i));
    }
    constexpr uint16_t resources_len() const {
        return (object_size-sizeof(Lwm2mObjectBase))/sizeof(lwm2m_object_res_item_t);
    }

    lwm2m_object_res_item_t* find_ressource(uint16_t id) {
        for (uint16_t index = 0; index < resources_len(); index++) {
            if (resource(index)->ressource_id == id) {
                return resource(index);
            }
        }

        return NULL;
    }

    constexpr Lwm2mObjectBase(uint16_t derived_size, uint16_t object_instance_size) :
        verifyWrite(defaultVerify),
        object_size(derived_size),
        object_instance_size(object_instance_size) {}

    void addInstance(lwm2m_context_t * contextP, Lwm2mObjectInstance* instance);
    lwm2m_list_t* removeInstance(lwm2m_context_t * contextP, uint16_t instance_id);
    int registerObject(lwm2m_context_t * contextP, bool allow_dynamic_instance_creation);

    virtual Lwm2mObjectInstance* createInstance(uint16_t instance_id) {return nullptr;}
    virtual int deleteInstance(Lwm2mObjectInstance* instance) {return COAP_NO_ERROR;}

    protected:
    constexpr static bool defaultVerify(Lwm2mObjectInstance*,uint16_t) { return true; }
    constexpr Lwm2mObjectBase() : verifyWrite(defaultVerify),
        object_size(0), object_instance_size(0) {}
};

template<uint16_t objectID, class Derived, class ObjectInstance>
class Lwm2mObject : public Lwm2mObjectBase {
public:
    Lwm2mObject() :Lwm2mObjectBase(sizeof(Derived)-4, sizeof(ObjectInstance)) {object.objID=objectID;}
};

template<uint16_t ResID, class ObjectInstance, class ResourceType, uint16_t offset, uint8_t Operations>
class ResourceRaw : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,0,0,0} {}
    static_assert(offset!=0, "There is no support for this type of resource!");
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,Executable,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_E,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,bool,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_BOOL,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,double,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_DOUBLE,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int8_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT8,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint8_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT8,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int16_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT16,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint16_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT16,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int32_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT32,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,uint32_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_UINT32,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,int64_t,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT64,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,const char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};
template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,char*,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance,OpaqueIndirect,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_OPAQUE_INDIRECT,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations, int N>
class ResourceRaw<ResID,ObjectInstance,Opaque<N>,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_OPAQUE_PREALLOC,offset} {}
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, uint8_t Operations, int N>
class ResourceRaw<ResID,ObjectInstance,PreallocString<N>,offset,Operations> : public lwm2m_object_res_item_t {
public:
    ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_STRING_PREALLOC,offset} {}
};

// Fallback for non indirect resources
template<uint16_t ResID, class ObjectInstance, class ResourceType, uint16_t offset, uint8_t... Operations>
class IndirectResourceRaw : public ResourceRaw<ResID,ObjectInstance,ResourceType,offset,Operations...> {

};

template<uint16_t ResID, class ObjectInstance, uint16_t offset>
class IndirectResourceRaw<ResID,ObjectInstance,Executable,offset> :
        public ResourceRaw<ResID,ObjectInstance,Executable,offset,O_RES_E> {
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, typename SubType>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectRead<SubType>,offset> :
        public ResourceRaw<ResID,ObjectInstance,SubType,offset,O_RES_R|O_RES_E> {
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, typename SubType>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectWrite<SubType>,offset> :
        public ResourceRaw<ResID,ObjectInstance,SubType,offset,O_RES_W|O_RES_E> {
};

template<uint16_t ResID, class ObjectInstance, uint16_t offset, typename SubType>
class IndirectResourceRaw<ResID,ObjectInstance,IndirectReadWrite<SubType>,offset> :
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
            offset_of(MemberPtr)>

#define Resource_3(ResID, MemberPtr, Operations) \
  IndirectResourceRaw<ResID, baseof_member_pointer<decltype(MemberPtr)>::type, \
            remove_member_pointer<decltype(MemberPtr)>::type, \
            offset_of(MemberPtr), Operations>

#define Resource(...) BOOST_PP_OVERLOAD(Resource_,__VA_ARGS__)(__VA_ARGS__)

#endif
