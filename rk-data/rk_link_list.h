#ifndef RK_LINK_LIST_H
#define RK_LINK_LIST_H
#include "rk_array.h"

#define rk_link_list_get_data(type,node) ((type*)((node)->data))

typedef struct rk_link_list {
    struct rk_link_list *next;
    void *data;
} rk_link_list;

#ifndef RK_LINK_LIST_NO_MALLOC

RK_STATE rk_link_list_new(rk_link_list** node);
RK_STATE rk_link_list_delete_next(rk_link_list* node,RK_STATE (*free_data)(void* node));
RK_STATE rk_link_list_destroy(rk_link_list** node,RK_STATE (*free_data)(void* node));

#endif

size_t rk_link_list_get_length(rk_link_list* head);

RK_STATE rk_link_list_filter_unsafe(rk_link_list* head,RK_STATE (*cmp)(void* data),size_t *nums,rk_array *result);
RK_STATE rk_link_list_filter(rk_link_list* head,RK_STATE (*cmp)(void* data),size_t *nums,rk_array *result);

RK_STATE rk_link_list_filter_delete_unsafe(rk_link_list* head,RK_STATE (*cmp)(void* data),RK_STATE (*free_data)(void* node));
RK_STATE rk_link_list_filter_delete(rk_link_list* head,RK_STATE (*cmp)(void* data),RK_STATE (*free_data)(void* node));

RK_STATE rk_link_list_insert_unsafe(rk_link_list* node,rk_link_list* node_new);
RK_STATE rk_link_list_insert(rk_link_list* node,rk_link_list* node_new);

#endif