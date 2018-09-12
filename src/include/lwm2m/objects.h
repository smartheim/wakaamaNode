/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#pragma once

/*
 * Classes, Methods and Enums defined in this file are for easily creating a new lwM2M object definition
 * and object instances. This is for the C++-API.
 */

#include "../../wakaama/liblwm2m.h"
#include "../../macro_helper.h"
#include "lwm2m/c_objects.h" // We need the enums of the C-API as well
#include <inttypes.h>
#include <string.h>
#include <type_traits>
#include <functional>

template<class T>
class Lwm2mObjectBase;

using Lwm2mObjectBaseVoid = Lwm2mObjectBase<void>;
class Lwm2mObjectInstance;

int lwm2m_object_prepare_full_response(lwm2m_data_t ** dataArrayP, Lwm2mObjectBaseVoid* metaP);
uint8_t lwm2m_object_assign_single_value(lwm2m_data_t* destination, lwm2m_object_res_item_t* resP,
                                         Lwm2mObjectInstance* instanceP);
uint8_t prv_read(uint16_t instanceId,
                        int * numDataP,
                        lwm2m_data_t ** dataArrayP,
                        lwm2m_object_t * objectP,
                        lwm2m_context_t* context);
uint8_t prv_write(uint16_t instanceId,
                         int numData,
                         lwm2m_data_t * dataArray,
                         lwm2m_object_t * objectP,
                        lwm2m_context_t* context);
uint8_t prv_execute(uint16_t instanceId,
                    uint16_t res_id,
                    lwm2m_context_t* context,
                    lwm2m_object_t * objectP);
uint8_t prv_discover(uint16_t instanceId,
                    int * numDataP,
                    lwm2m_data_t ** dataArrayP,
                    lwm2m_object_t * objectP);
uint8_t prv_delete(uint16_t id, lwm2m_object_t * objectP);
uint8_t prv_create(uint16_t instanceId,
                  int numData,
                  lwm2m_data_t * dataArray,
                  lwm2m_object_t * objectP, lwm2m_context_t *contextP);

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
        if (used_len>reserved_len){
            used_len=reserved_len;
        }
        memcpy(data, d, used_len+1);
    }
};

template<class T>
struct DynArray {
    T data;
    int len;
    DynArray(T& value, int len) : data(value),len(len){}
};

class Lwm2mObjectInstance : public lwm2m_list_t {
public:
    Lwm2mObjectInstance() : lwm2m_list_t{nullptr,0} {}
    template<class T> inline T* as() {return reinterpret_cast<T*>(this);}
};

// The executable type
using Executable = std::add_pointer<void(Lwm2mObjectInstance* instance, lwm2m_context_t* context)>::type;

// The verify write callback of Lwm2mObjectBase
template<class T>
using VerifyWrite = bool (*)(T*, uint16_t);

// The read indirect type
template<class T>
using IndirectRead = T (*)(Lwm2mObjectInstance*);

// The write indirect type
template<class T>
using IndirectWrite = void (*)(Lwm2mObjectInstance*,DynArray<T>&);

// The read/write indirect type
template<class T>
struct IndirectReadWrite {
    typedef T type;
    IndirectRead<T> read;
    IndirectWrite<T> write;
    IndirectReadWrite() = default;
    IndirectReadWrite(IndirectRead<T> read, IndirectWrite<T> write) : read(read),write(write){}
};

template<class ObjectInstance>
class Lwm2mObjectBase {
    // Allow offset_of_impl to access the protected constructor
    template<typename T1, typename T2> friend struct offset_of_impl;
public:
    lwm2m_object_t object{};
    VerifyWrite<ObjectInstance> verifyWrite;
    // Requires 32bit platforms at least and we are wasting some memory on >32bit platforms.
    // But we need to stay aligned for all following class members defined by child classes.
    struct alignas(alignof (uintptr_t)) Sizes {
        const uint16_t object;
        const uint16_t object_instance;
    };
    const Sizes sizes;

    static Lwm2mObjectBase<ObjectInstance>* getBase(lwm2m_object_t* p) {
        const uintptr_t objectP = reinterpret_cast<uintptr_t>(p);
        return reinterpret_cast<Lwm2mObjectBase<ObjectInstance>*>(objectP - offset_of(&Lwm2mObjectBase<void>::object));
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

    constexpr Lwm2mObjectBase(uint16_t derived_size) :
        verifyWrite(defaultVerify), sizes{derived_size,sizeof(ObjectInstance)} {}

    void resChanged(lwm2m_context_t * contextP, uint16_t object_instance_id, uint16_t res_id) {
        lwm2m_uri_t uri = {LWM2M_URI_FLAG_OBJECT_ID|LWM2M_URI_FLAG_INSTANCE_ID|LWM2M_URI_FLAG_RESOURCE_ID,
                           object.objID, object_instance_id, res_id};
        lwm2m_resource_value_changed(contextP, &uri);
    }

    /**
      * Add the given instance to the object and notify connected lwm2m servers.
      */
    void addInstance(lwm2m_context_t * contextP, Lwm2mObjectInstance* instance) {
        if (lwm2m_list_find(object.instanceList,instance->id)) return;

        object.instanceList=lwm2m_list_add(object.instanceList, instance);
        if (contextP->state == STATE_READY && LWM2M_LIST_FIND(contextP->objectList, object.objID) != NULL)
            lwm2m_update_registration(contextP, 0, true);
    }

    /**
      * Remove the given instance from the object and notify connected lwm2m servers.
      */
    lwm2m_list_t* removeInstance(lwm2m_context_t * contextP, uint16_t instance_id) {
        lwm2m_list_t* removed = NULL;
        object.instanceList = lwm2m_list_remove(object.instanceList, instance_id, &removed);

        if (contextP->state == STATE_READY && LWM2M_LIST_FIND(contextP->objectList, object.objID) != NULL)
        {
            lwm2m_update_registration(contextP, 0, true);
        }
        return removed;
    }

    /**
      * Registers an object to the given lwm2m context and notifies connected lwm2m servers.
      */
    int registerObject(lwm2m_context_t * contextP, bool allow_dynamic_instance_creation) {
        object.readFunc = prv_read;
        object.writeFunc = prv_write;
        object.discoverFunc = prv_discover;
        object.executeFunc = prv_execute;

        if (allow_dynamic_instance_creation)
        {
            object.createFunc = prv_create;
            object.deleteFunc = prv_delete;
        }

        return lwm2m_add_object(contextP, &object);
    }

    /**
      * Unregisters an object from the given lwm2m context and notifies connected lwm2m servers.
      */
    int unregisterObject(lwm2m_context_t * contextP) {
        return lwm2m_remove_object(contextP, object.objID);
    }


    /**
      * Dynamically create an instance. Will be called when a lwm2m server requests
      * a new object instance.
      */
    virtual Lwm2mObjectInstance* createInstance(uint16_t instance_id){return nullptr;}
    /**
      * Dynamically delete an instance. Will be called when a lwm2m server requests
      * to delete an object instance.
      */
    virtual int deleteInstance(Lwm2mObjectInstance* instance){return COAP_NO_ERROR;}

    protected:
    constexpr Lwm2mObjectBase() : verifyWrite(defaultVerify), sizes{0,0} {}
    constexpr static bool defaultVerify(ObjectInstance*,uint16_t) { return true; }
};

template<uint16_t objectID, class Derived, class ObjectInstance>
class Lwm2mObject : public Lwm2mObjectBase<ObjectInstance> {
public:
   Lwm2mObject() : Lwm2mObjectBase<ObjectInstance>(sizeof(Derived)) {
       Lwm2mObjectBase<ObjectInstance>::object.objID=objectID;
   }
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

template<uint16_t ResID, class ObjectInstance, class ResourceType, size_t offset, uint8_t Operations>
class ResourceRaw<ResID,ObjectInstance, ResourceType, offset, Operations,
            typename std::enable_if<!std::is_same<int, int32_t>::value && std::is_same<ResourceType, int>::value>::type> : public lwm2m_object_res_item_t {
public:
 ResourceRaw() : lwm2m_object_res_item_t {ResID,Operations,O_RES_INT32,offset} {}
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
