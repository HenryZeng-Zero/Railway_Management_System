#include "rk_array.h"
#include <string.h>

RK_STATE rk_array_init(rk_array* object,size_t length,size_t item_size,void* data){
    object->length = length;
    object-> item_size = item_size;
    object->data = data;
    return 0;
}

#ifndef RK_LINK_LIST_NO_MALLOC

RK_STATE rk_array_new_with_nums(rk_array** object_self,size_t nums,size_t item_size){
    *object_self = (rk_array*)malloc(sizeof(rk_array));
    void* data = malloc(nums * item_size);

    return rk_array_init(*object_self, nums, item_size, data);
}

RK_STATE rk_array_new(rk_array** object_self,size_t item_size){
    return rk_array_new_with_nums(object_self,RK_ARRAY_DEFAULT_ITEM_NUMS,item_size);
}

RK_STATE rk_array_resize(rk_array* object,size_t new_length){
    void* resized_data = malloc(object->item_size * new_length);

    memcpy(resized_data, object->data, object->item_size * object->length);

    ((rk_array*)resized_data)->length = new_length;
    
    return 0;
}

RK_STATE rk_array_auto_resize(rk_array* object){
    return rk_array_resize(object, (int)((float)object->length * RK_ARRAY_DEFAULT_RESIZE_SCALE));
}

RK_STATE rk_array_destroy(rk_array** object){
    free((*object)->data);
    free(*object);
    *object = NULL;
    return 0;
}

#endif

RK_STATE rk_array_is_legal_index(rk_array* object,int index){
    return index < object->length;
}

size_t rk_array_get_length(rk_array* object){
    return object->length;
}

RK_STATE rk_array_get_unsafe(rk_array* object,int index,void *result){
    void *src_pointer;
    if (rk_array_ref_unsafe(object, index, &src_pointer)) {
        return 1;
    }

    memcpy(result, src_pointer, object->item_size);

    return 0;
}

RK_STATE rk_array_get(rk_array* object,int index,void *result){
    if(rk_array_is_legal_index(object, index)){
        // rk_array_is_legal_index(...) : if index is ok, back 0
        return 1;
    }
    
    if(result == NULL){
        return 2;
    }

    return rk_array_get_unsafe(object, index, result);
}

RK_STATE rk_array_ref_unsafe(rk_array* object,int index,void** result){
    *result = object->data + index * object->item_size;
    return 0;
}

RK_STATE rk_array_ref(rk_array* object,int index,void** result){
    if(rk_array_is_legal_index(object, index)){
        // rk_array_is_legal_index(...) : if index is ok, back 0
        return 1;
    }
    
    if(result == NULL){
        return 2;
    }

    return rk_array_ref_unsafe(object, index, result);
}

RK_STATE rk_array_set_unsafe(rk_array* object,int index,void *value){
    void *src_pointer;
    if (rk_array_ref_unsafe(object, index, &src_pointer)) {
        return 1;
    }

    memcpy(src_pointer, value, object->item_size);
    
    return 0;
}

RK_STATE rk_array_set(rk_array* object,int index,void *value){
    if(rk_array_is_legal_index(object, index)){
        // rk_array_is_legal_index(...) : if index is ok, back 0
        return 1;
    }
    
    if(value == NULL){
        return 2;
    }

    return rk_array_set_unsafe(object, index, value);
}

#ifndef RK_LINK_LIST_NO_MALLOC
RK_STATE rk_array_set_auto_resize(rk_array* object,int index,void *value){
    if(rk_array_is_legal_index(object, index)){
        // rk_array_is_legal_index(...) : if index is ok, back 0
        rk_array_auto_resize(object); // auto resize
    }
    
    if(value == NULL){
        return 2;
    }

    return rk_array_set_unsafe(object, index, value);
}
#endif

RK_STATE rk_array_swap_unsafe(rk_array* object,size_t index_one,size_t index_another){
    // using a feture of c language : VLA (variable-length array)
    unsigned char buffer[object->item_size];

    rk_array_get_unsafe(object, index_another, buffer);

    memcpy( object->data + index_another * object->item_size,
            object->data + index_one * object->item_size, 
            object->item_size);

    rk_array_set_unsafe(object, index_one, buffer);
    return 0;
}

RK_STATE rk_array_swap(rk_array* object,size_t index_one,size_t index_another){
    if (rk_array_is_legal_index(object, index_one)) {
        return 1;
    }

    if (rk_array_is_legal_index(object, index_another)) {
        return 2;
    }

    return rk_array_swap_unsafe(object, index_one, index_another);
}