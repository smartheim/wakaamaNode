#include "wakaama_object_utils.h"
#include "wakaama/liblwm2m.h"

#include <stdarg.h>
#include <string.h>

static lwm2m_object_res_item_t* prv_find_ressource(lwm2m_object_meta_information_t* metaP, uint16_t id) {
    return &metaP->ressources[id];
}

// For opaque fields we always expect to find a size_t member with the length information
// right after the data pointer.
#define OPAQUE_SIZE_MEMBER_P(memberP) ((size_t*)((char*)memberP+sizeof(void*)))

int lwm2m_object_prepare_full_response(lwm2m_data_t ** dataArrayP, lwm2m_object_meta_information_t* metaP)
{
    *dataArrayP = lwm2m_data_new(metaP->ressources_len);
    if (*dataArrayP == NULL) return -1;
    int readable = 0;
    for(unsigned i=0;i<metaP->ressources_len;++i)
    {
        lwm2m_object_res_item_t* resP = &(metaP->ressources[i]);
        if (!(resP->type_and_access & O_RES_R))
            continue;
        lwm2m_data_t* dataP = &(*dataArrayP)[readable];
        dataP->id = resP->ressource_id;
        ++readable;
    }
    return readable;
}

uint8_t lwm2m_object_assign_single_value(lwm2m_data_t* destination, lwm2m_object_res_item_t* resP, void* instanceP)
{
    lwm2m_object_util_type_t res_type = resP->type_and_access & 0x0f;

    void* memberP = (void*)((char*)instanceP + resP->struct_member_offset);

    /// Support for function results as value ///
    if (resP->type_and_access & O_RES_FUNCTION)
    {
        // The following is equal to this: readFunc f = (readFunc)(*(void**)memberP);
        // But the -pedantic switch forces us to use this union construct.
        readFunc f = ((union {readFunc to; void *from;} *)memberP)->to;
        // We do not know the result type of f() yet and use a generic "void*"
        void* fdata = f();
        // Make memberP point to the address of fData.
        // The dereferenced memberP will contain the real data.
        memberP = &fdata;
    }
    ///////////////////////////////////////////////////////////////////////

    switch (res_type)
    {
    case O_RES_STRING:
    case O_RES_STRING_STATIC:
        lwm2m_data_encode_string(*((char**)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_STRING_PREALLOC:
        lwm2m_data_encode_string((char*)memberP, destination);
        return COAP_205_CONTENT;
    case O_RES_OPAQUE:
    case O_RES_OPAQUE_STATIC:
        lwm2m_data_encode_opaque(*((uint8_t**)memberP),*OPAQUE_SIZE_MEMBER_P(memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_BOOL:
        lwm2m_data_encode_bool(*((bool*)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_DOUBLE:
        lwm2m_data_encode_float(*((double*)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_INT8:
    case O_RES_UINT8:
        lwm2m_data_encode_int(*((int8_t*)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_INT16:
    case O_RES_UINT16:
        lwm2m_data_encode_int(*((int16_t*)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_INT32:
    case O_RES_UINT32:
        lwm2m_data_encode_int(*((int32_t*)memberP), destination);
        return COAP_205_CONTENT;
    case O_RES_INT64:
        lwm2m_data_encode_int(*((int64_t*)memberP), destination);
        return COAP_205_CONTENT;
    }

    return COAP_404_NOT_FOUND;
}

static uint8_t prv_read(uint16_t instanceId,
                        int * numDataP,
                        lwm2m_data_t ** dataArrayP,
                        lwm2m_object_t * objectP)
{
    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)objectP)->meta;

    if (*numDataP == 0)
        *numDataP = lwm2m_object_prepare_full_response(dataArrayP, metaP);

    if (*numDataP < 0)
        return COAP_500_INTERNAL_SERVER_ERROR;

    for (int i = 0 ; i < *numDataP ; i++)
    {
        lwm2m_data_t* dataP = &(*dataArrayP)[i];
        unsigned res_id = dataP->id;
        lwm2m_object_res_item_t* resP = prv_find_ressource(metaP, res_id);
        if (!resP)
            return COAP_404_NOT_FOUND;

        if (!(resP->type_and_access & O_RES_R) || resP->struct_member_offset==0)
            return COAP_405_METHOD_NOT_ALLOWED;

        lwm2m_object_assign_single_value(dataP, resP, instanceP);
    }

    return COAP_205_CONTENT;
}


static uint8_t prv_write(uint16_t instanceId,
                         int numData,
                         lwm2m_data_t * dataArray,
                         lwm2m_object_t * objectP)
{
    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)objectP)->meta;

    uint8_t copy_of_entry[metaP->instance_object_size];

    for (unsigned i = 0 ; i < numData ; ++i)
    {
        unsigned res_id = dataArray[i].id;

        lwm2m_object_res_item_t* resP = prv_find_ressource(metaP, res_id);
        if (!resP)
            return COAP_404_NOT_FOUND;

        // Check for write access and if offset is set
        if (!(resP->type_and_access & O_RES_W) || resP->struct_member_offset==0)
            return COAP_405_METHOD_NOT_ALLOWED;

        // Extract ressource type and member pointer from meta object
        lwm2m_object_util_type_t res_type = resP->type_and_access & 0x0f;
        void* memberP = (void*)((char*)copy_of_entry + resP->struct_member_offset);

        union {
            int64_t i;
            double d;
            char* c;
        } temp;

        memcpy(copy_of_entry, instanceP, metaP->instance_object_size);

        switch (res_type)
        {
        case O_RES_STRING:
            // free memory
            temp.c = *((char**)memberP);

            if (temp.c != NULL)
                lwm2m_free(temp.c);

            // continue with _STATIC
        case O_RES_STRING_STATIC:
            temp.c = *((char**)memberP);

            // A _STATIC string the user writes to is automatically converted to a non static variant.
            resP->type_and_access = (0xf0 & resP->type_and_access) | O_RES_STRING;

            temp.c = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length + 1);
            memset(temp.c, 0, dataArray[i].value.asBuffer.length + 1);
            if (temp.c == NULL)
            {
                return COAP_500_INTERNAL_SERVER_ERROR;
            }
            strncpy(temp.c, (char*)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
            *((char**)memberP) = temp.c;

            break;
        case O_RES_OPAQUE:
            // free memory
            temp.c = *((char**)memberP);

            if (temp.c != NULL)
                lwm2m_free(temp.c);
            // continue with _STATIC
        case O_RES_OPAQUE_STATIC:
            temp.c = *((char**)memberP);

            // A _STATIC opaque field the user writes to is automatically converted to a non static variant.
            resP->type_and_access = (0xf0 & resP->type_and_access) | O_RES_OPAQUE;

            // Assign size and copy data
            *OPAQUE_SIZE_MEMBER_P(memberP) = dataArray[i].value.asBuffer.length;
            temp.c = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length);
            if (temp.c == NULL)
                return COAP_500_INTERNAL_SERVER_ERROR;
            memcpy(temp.c, (char*)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
            *((char**)memberP) = temp.c;

            break;
        case O_RES_STRING_PREALLOC: // this is post processed after write verify callback returns true
            *((char**)memberP) = (char*)dataArray[i].value.asBuffer.buffer;
            break;
        case O_RES_BOOL:
            if (1 != lwm2m_data_decode_bool(&dataArray[i], ((bool*)memberP)))
                return COAP_400_BAD_REQUEST;
            break;
        case O_RES_DOUBLE:
            if (1 != lwm2m_data_decode_float(&dataArray[i], &temp.d))
                return COAP_400_BAD_REQUEST;
            *((double*)memberP) = temp.d;
            break;
        case O_RES_INT8:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < INT8_MIN || temp.i > INT8_MAX)
                return COAP_400_BAD_REQUEST;
            *((int8_t*)memberP) = (int8_t)temp.i;
            break;
        case O_RES_UINT8:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < 0 || temp.i > UINT8_MAX)
                return COAP_400_BAD_REQUEST;
            *((uint8_t*)memberP) = (uint8_t)temp.i;
            break;
        case O_RES_INT16:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < INT16_MIN || temp.i > INT16_MAX)
                return COAP_400_BAD_REQUEST;
            *((int16_t*)memberP) = (int16_t)temp.i;
            break;
        case O_RES_UINT16:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < 0 || temp.i > UINT16_MAX)
                return COAP_400_BAD_REQUEST;
            *((uint16_t*)memberP) = (uint16_t)temp.i;
            break;
        case O_RES_INT32:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < INT32_MIN || temp.i > INT32_MAX)
                return COAP_400_BAD_REQUEST;
            *((int32_t*)memberP) = (int32_t)temp.i;
            break;
        case O_RES_UINT32:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i) || temp.i < 0 || temp.i > UINT32_MAX)
                return COAP_400_BAD_REQUEST;
            *((uint32_t*)memberP) = (uint32_t)temp.i;
            break;
        case O_RES_INT64:
            if (1 != lwm2m_data_decode_int(&dataArray[i], &temp.i))
                return COAP_400_BAD_REQUEST;
            *((int64_t*)memberP) = (int64_t)temp.i;
            break;
        default:
            return COAP_500_INTERNAL_SERVER_ERROR;
        }

        if (!metaP->write_verify_cb || metaP->write_verify_cb((lwm2m_list_t*)copy_of_entry, res_id))
        {
            // The string ressource for preallocated space needs some special handling:
            // We do not know the exact size of the allocated space in the structure. We leave it to the
            // developer to check for this in the verify write callback.
            if (res_type == O_RES_STRING_PREALLOC) {
                strncpy((char*)memberP, (char*)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
            }
            memcpy(instanceP, copy_of_entry, metaP->instance_object_size);
        } else {
            return COAP_400_BAD_REQUEST;
        }
    }

    return COAP_204_CHANGED;
}


uint8_t prv_execute(uint16_t instanceId,
                        uint16_t resourceId,
                        uint8_t * buffer,
                        int length,
                        lwm2m_object_t * objectP)
{
    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)objectP)->meta;

    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    lwm2m_object_res_item_t* resP = prv_find_ressource(metaP, resourceId);
    if (!resP)
        return COAP_404_NOT_FOUND;

    if (!(resP->type_and_access & O_RES_E))
        return COAP_405_METHOD_NOT_ALLOWED;

    /// Support for function pointers ///
    if (resP->type_and_access & O_RES_FUNCTION)
    {
        void* memberP = (void*)((char*)instanceP + resP->struct_member_offset);
        // The following is equal to this: execFunc f = (execFunc)(*(void**)memberP);
        // But the -pedantic switch forces us to use this union construct.
        execFunc f = ((union {execFunc to; void *from;} *)memberP)->to;
        f(buffer, length);
        return COAP_204_CHANGED;
    }
    ///////////////////////////////////////////////////////////////////////

    return COAP_405_METHOD_NOT_ALLOWED;
}


static uint8_t prv_discover(uint16_t instanceId,
                            int * numDataP,
                            lwm2m_data_t ** dataArrayP,
                            lwm2m_object_t * objectP)
{
    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_list_find(objectP->instanceList, instanceId);
    if (NULL == instanceP) return COAP_404_NOT_FOUND;

    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)objectP)->meta;

    // is the server asking for the full object ?
    if (*numDataP == 0)
    {
        *dataArrayP = lwm2m_data_new(metaP->ressources_len);
        if (*dataArrayP == NULL)
            return COAP_500_INTERNAL_SERVER_ERROR;
        int readable = 0;
        for(unsigned i=0;i<metaP->ressources_len;++i)
        {
            lwm2m_object_res_item_t* resP = &metaP->ressources[i];
            if (!(resP->type_and_access & O_RES_RWE))
                continue;
            lwm2m_data_t* dataP = &(*dataArrayP)[readable];
            dataP->id = resP->ressource_id;
            ++readable;
        }
        *numDataP = readable;
        return COAP_205_CONTENT;
    }

    for (unsigned i = 0; i < *numDataP; ++i)
    {
        lwm2m_data_t* dataP = &(*dataArrayP)[i];
        if (dataP->id >= metaP->ressources_len) {
            return COAP_404_NOT_FOUND;
        }
    }
    return COAP_205_CONTENT;
}


static uint8_t prv_delete(uint16_t id,
                          lwm2m_object_t * objectP)
{
    lwm2m_list_t * targetP;
    objectP->instanceList = lwm2m_list_remove(objectP->instanceList, id, (lwm2m_list_t **)&targetP);
    if (NULL == targetP) return COAP_404_NOT_FOUND;

    lwm2m_free(targetP);

    return COAP_202_DELETED;
}

static uint8_t prv_create(uint16_t instanceId,
                          int numData,
                          lwm2m_data_t * dataArray,
                          lwm2m_object_t * objectP)
{
    // The meta data pointer is not an official member of the lwm2m_object_t struct.
    lwm2m_object_meta_information_t* metaP = ((lwm2m_object_with_meta_t*)objectP)->meta;

    lwm2m_list_t* instanceP = (lwm2m_list_t *)lwm2m_malloc(metaP->instance_object_size);
    if (NULL == instanceP)
        return COAP_500_INTERNAL_SERVER_ERROR;

    memset(instanceP, 0, metaP->instance_object_size);

    instanceP->id = instanceId;
    objectP->instanceList = LWM2M_LIST_ADD(objectP->instanceList, instanceP);

    uint8_t result = prv_write(instanceId, numData, dataArray, objectP);

    if (result != COAP_204_CHANGED)
    {
        (void)prv_delete(instanceId, objectP);
    }
    else
    {
        result = COAP_201_CREATED;
    }

    return result;
}

inline lwm2m_object_t* lwm2m_object_create(uint16_t object_id,
                                    bool allow_dynamic_instance_creation,
                                    lwm2m_object_meta_information_t* meta_information)
{
    lwm2m_object_with_meta_t * newObj;
    newObj = (lwm2m_object_with_meta_t *)lwm2m_malloc(sizeof(lwm2m_object_with_meta_t));

    if (newObj == NULL)
        return NULL;

    lwm2m_object_create_preallocated(newObj, object_id, allow_dynamic_instance_creation, meta_information);

    return (lwm2m_object_t*)newObj;
}

void lwm2m_object_create_preallocated(lwm2m_object_with_meta_t * object,
                                      uint16_t object_id,
                                      bool allow_dynamic_instance_creation,
                                      lwm2m_object_meta_information_t* meta_information)
{
    memset(object, 0, sizeof(lwm2m_object_with_meta_t));
    object->obj.objID = object_id;
    object->meta = meta_information;


    object->obj.readFunc = prv_read;
    object->obj.writeFunc = prv_write;
    object->obj.discoverFunc = prv_discover;
    object->obj.executeFunc = prv_execute;

    if (allow_dynamic_instance_creation)
    {
        object->obj.createFunc = prv_create;
        object->obj.deleteFunc = prv_delete;
    }
}

void lwm2m_object_instances_add(lwm2m_object_t* object, lwm2m_list_t* instance) {
    object->instanceList = lwm2m_list_add(object->instanceList, instance);
}

void lwm2m_object_free(lwm2m_object_t * object)
{
    LWM2M_LIST_FREE(object->instanceList);
    if (object->userData != NULL)
    {
        lwm2m_free(object->userData);
        object->userData = NULL;
    }
    lwm2m_free(object);
}
