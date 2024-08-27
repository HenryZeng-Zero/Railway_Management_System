#include "rk_link_list.h"

#ifndef RK_LINK_LIST_NO_MALLOC

RK_STATE rk_link_list_new(rk_link_list** node){
    *node = (rk_link_list*)malloc(sizeof(rk_link_list));
    (*node)->next = NULL;
    (*node)->data = NULL;

    return 0;
}

RK_STATE rk_link_list_delete_next(rk_link_list* node,RK_STATE (*free_data)(void* node)){
    rk_link_list *rubbish = node->next;
    node->next = rubbish->next;
    
    if (free_data(rubbish->data)) {
        return 1;
    }

    free(rubbish->data);
    free(rubbish);

    return 0;
}

RK_STATE rk_link_list_destroy(rk_link_list** node,RK_STATE (*free_data)(void* node)){
    rk_link_list *rubbish = (*node)->next,*tmp;
    while (rubbish->next != NULL) {
        if (free_data(rubbish->data)) {
            return 1;
        }
        free(rubbish->data);
        
        tmp = rubbish;
        rubbish = rubbish->next;
        
        free(tmp);
    }

    free((*node));
    *node = NULL;

    return 0;
}

#endif


size_t rk_link_list_get_length(rk_link_list* head){
    rk_link_list* ptr;
    size_t count = 0;

    while (ptr->next != NULL) {
        ++count;
        ptr = ptr->next;
    }

    return count;
}

/**
 *  @param result: A (rk_array*) object or just use NULL
 */
RK_STATE rk_link_list_filter_unsafe(rk_link_list* ptr,RK_STATE (*cmp)(void* data),size_t *nums,rk_array *result){  
    size_t index = 0;
    rk_array* back;

    if (result != NULL) {
        rk_array_new(&back, sizeof(rk_link_list*));
    }
    
    while (ptr->next != NULL) {
        if (ptr->data !=NULL && cmp(ptr->data) == TRUE) {
            if (result != NULL) {
                rk_array_set(back, index, &ptr);
            }

            ++index;
        }

        ptr = ptr->next;
    }

    *nums = index + 1;
    
    if (result != NULL) {
        result = back;
    }

    return 0;
}

RK_STATE rk_link_list_filter(rk_link_list* head,RK_STATE (*cmp)(void* data),size_t *nums,rk_array *result){
    if(cmp == NULL){
        return 1;
    }
    
    if(nums == NULL){
        return 2;
    }

    return rk_link_list_filter_unsafe(head, cmp, nums, result);
}

RK_STATE rk_link_list_filter_delete_unsafe(rk_link_list* ptr,RK_STATE (*cmp)(void* data),RK_STATE (*free_data)(void* node)){
    size_t index = 0;

    while (ptr->next != NULL) {
        if (cmp(ptr->next->data) == TRUE) {
            rk_link_list_delete_next(ptr, free_data);
            ++index;
        }

        ptr = ptr->next;
    }

    return 0;
}

RK_STATE rk_link_list_filter_delete(rk_link_list* head,RK_STATE (*cmp)(void* data),RK_STATE (*free_data)(void* node)){
    if (cmp == NULL) {
        return 1;
    }

    return rk_link_list_filter_delete_unsafe(head,cmp,free_data);
}

RK_STATE rk_link_list_insert_unsafe(rk_link_list* node,rk_link_list* node_new){
    node_new->next = node->next;
    node->next = node_new;
    
    return 0;
}


RK_STATE rk_link_list_insert(rk_link_list* node,rk_link_list* node_new){
    if (node_new == NULL) {
        return 0;
    }

    return rk_link_list_insert_unsafe(node, node_new);
}