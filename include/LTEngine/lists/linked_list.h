#include <stdlib.h>

#include <LTEngine/util/types/inttypes.h>
#include <LTEngine/util/types/floattypes.h>

#ifndef _LTLINKED_LIST_H_
#define _LTLINKED_LIST_H_

#define DEFINE_LINKED_LIST(type, tname) \
    typedef struct ll_ltnode_##tname##_t { \
        type _data; \
        struct ll_ltnode_##tname##_t *_next; \
    } ll_ltnode_##tname##_t; \
    \
    \
    inline ll_ltnode_##tname##_t ltlinked_list_new_##tname() { \
        ll_ltnode_##tname##_t list; \
        list._data = (type){0}; \
        list._next = NULL; \
        return list; \
    } \
    \
    inline void ltlinked_list_free_##tname(ll_ltnode_##tname##_t *list) { \
        for (ll_ltnode_##tname##_t *current = list->_next; current != NULL; current = current->_next) { \
            free(current); \
        } \
        list->_next = NULL; \
        list->_data = (type){0}; \
    } \
    \
    \
    inline ll_ltnode_##tname##_t *ltlinked_list_next_##tname(const ll_ltnode_##tname##_t *node) { \
        return node->_next; \
    } \
    \
    inline ll_ltnode_##tname##_t *ltlinked_list_prev_##tname(ll_ltnode_##tname##_t *list, const ll_ltnode_##tname##_t *node) { \
        for (ll_ltnode_##tname##_t *current = list; current != NULL; current = current->_next) { \
            if (current->_next == node) { \
                return current; \
            } \
        } \
        return NULL; \
    } \
    \
    \
    inline void ltlinked_list_add_##tname(ll_ltnode_##tname##_t *node, ll_ltnode_##tname##_t *list, type data) { \
        ll_ltnode_##tname##_t *prev_next = node->_next; \
        ll_ltnode_##tname##_t *prev = ltlinked_list_prev_##tname(list, node); \
        \
        ll_ltnode_##tname##_t *new_node = (ll_ltnode_##tname##_t*)malloc(sizeof(ll_ltnode_##tname##_t)); \
        new_node->_data = data; \
        new_node->_next = prev_next; \
        node->_next = new_node; \
        \
        if (prev != NULL) { \
            prev->_next = new_node; \
        } \
    } \
    \
    inline void ltlinked_list_remove_##tname(ll_ltnode_##tname##_t *node, ll_ltnode_##tname##_t *list) { \
        ll_ltnode_##tname##_t *prev = ltlinked_list_prev_##tname(list, node); \
        \
        if (prev != NULL) { \
            prev->_next = node->_next; \
        } \
        \
        free(node); \
    }
   
DEFINE_LINKED_LIST(i8, i8)
DEFINE_LINKED_LIST(i16, i16)
DEFINE_LINKED_LIST(i32, i32)
DEFINE_LINKED_LIST(i64, i64)

DEFINE_LINKED_LIST(u8, u8)
DEFINE_LINKED_LIST(u16, u16)
DEFINE_LINKED_LIST(u32, u32)

DEFINE_LINKED_LIST(f32, f32)
DEFINE_LINKED_LIST(f64, f64)
DEFINE_LINKED_LIST(f128, f128)

#endif // _LINKED_LIST_H_
