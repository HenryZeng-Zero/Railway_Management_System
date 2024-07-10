#ifndef RK_ARRAY_H
#define RK_ARRAY_H
#include <stdlib.h>
#include "rk_def.h"

#ifndef RK_ARRAY_NO_DEFAULT_ITEM_NUMS
#define RK_ARRAY_DEFAULT_ITEM_NUMS 20
#endif

#ifndef RK_ARRAY_NO_DEFAULT_RESIZE_SCALE
#define RK_ARRAY_DEFAULT_RESIZE_SCALE 1.5
#endif

typedef struct rk_array {
    size_t length;
    size_t item_size;
    void *data;
} rk_array;

RK_STATE rk_array_init(rk_array* object,size_t length,size_t item_size,void* data);

#ifndef RK_LINK_LIST_NO_MALLOC

RK_STATE rk_array_new_with_nums(rk_array** object_self,size_t nums,size_t item_size);
RK_STATE rk_array_new(rk_array** object_self,size_t item_size);
RK_STATE rk_array_resize(rk_array* object,size_t new_length);
RK_STATE rk_array_auto_resize(rk_array* object);
RK_STATE rk_array_destroy(rk_array** object);

#endif

RK_STATE rk_array_is_legal_index(rk_array* object,int index);

size_t rk_array_get_length(rk_array* object);

RK_STATE rk_array_get_unsafe(rk_array* object,int index,void *result);
RK_STATE rk_array_get(rk_array* object,int index,void *result);

RK_STATE rk_array_ref_unsafe(rk_array* object,int index,void** result);
RK_STATE rk_array_ref(rk_array* object,int index,void** result);

RK_STATE rk_array_set_unsafe(rk_array* object,int index,void *value);
RK_STATE rk_array_set(rk_array* object,int index,void *value);
#ifndef RK_LINK_LIST_NO_MALLOC
RK_STATE rk_array_set_auto_resize(rk_array* object,int index,void *value);
#endif

RK_STATE rk_array_swap_unsafe(rk_array* object,size_t index_one,size_t index_another);
RK_STATE rk_array_swap(rk_array* object,size_t index_one,size_t index_another);

#endif