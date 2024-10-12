#include <stdlib.h>

#include <LTEngine/util/types/inttypes.h>
#include <LTEngine/util/types/floattypes.h>

#ifndef _LTDOUBLE_LINKED_LIST_H_
#define _LTDOUBLE_LINKED_LIST_H_

#define DEFINE_DOUBLE_LINKED_LIST(type, tname) \
    typedef struct dll_ltnode_##tname##_t { \
        type _data; \
        struct dll_ltnode_##tname##_t *_next; \
        struct dll_ltnode_##tname##_t *_prev; \
    } dll_ltnode_##tname##_t; \
    \
    \
    inline dll_ltnode_##tname##_t ltdouble_linked_list_new_##tname() { \
        dll_ltnode_##tname##_t list; \
        list._data = (type){0}; \
        list._next = NULL; \
        list._prev = NULL; \
        return list; \
    } \
    \
    inline void ltdouble_linked_list_free_##tname(dll_ltnode_##tname##_t *list) { \
        for (dll_ltnode_##tname##_t *current = list->_next; current != NULL; current = current->_next) { \
            free(current); \
        } \
        list->_next = NULL; \
        list->_prev = NULL; \
        list->_data = (type){0}; \
    } \
    \
    \
    inline dll_ltnode_##tname##_t *double_linked_list_next_##tname(const dll_ltnode_##tname##_t *node) { \
        return node->_next; \
    } \
    \
    inline dll_ltnode_##tname##_t *double_linked_list_prev_##tname(const dll_ltnode_##tname##_t *node) { \
        return node->_prev; \
    } \
    \
    inline type ltdouble_linked_list_get_data_##tname(const dll_ltnode_##tname##_t *node) { \
        return node->_data; \
    } \
    \
    inline void ltdouble_linked_list_set_data_##tname(dll_ltnode_##tname##_t *node, type data) { \
        node->_data = data; \
    } \
    \
    \
    inline void ltdouble_linked_list_add_##tname(dll_ltnode_##tname##_t *node, dll_ltnode_##tname##_t *list, type data) { \
        dll_ltnode_##tname##_t *prev_next = node->_next; \
        \
        dll_ltnode_##tname##_t *new_node = (dll_ltnode_##tname##_t*)malloc(sizeof(dll_ltnode_##tname##_t)); \
        new_node->_data = data; \
        new_node->_next = prev_next; \
        new_node->_prev = node; \
        node->_next = new_node; \
        \
        if (node->_prev != NULL) { \
            node->_prev->_next = new_node; \
        } \
    } \
    \
    inline void ltdouble_linked_list_remove_##tname(dll_ltnode_##tname##_t *node) { \
        if (node->_prev != NULL) { \
            node->_prev->_next = node->_next; \
            node->_next->_prev = node->_prev; \
        } \
        \
        free(node); \
    }
   
DEFINE_DOUBLE_LINKED_LIST(i8, i8)
DEFINE_DOUBLE_LINKED_LIST(i16, i16)
DEFINE_DOUBLE_LINKED_LIST(i32, i32)
DEFINE_DOUBLE_LINKED_LIST(i64, i64)

DEFINE_DOUBLE_LINKED_LIST(u8, u8)
DEFINE_DOUBLE_LINKED_LIST(u16, u16)
DEFINE_DOUBLE_LINKED_LIST(u32, u32)
DEFINE_DOUBLE_LINKED_LIST(u64, u64)

DEFINE_DOUBLE_LINKED_LIST(f32, f32)
DEFINE_DOUBLE_LINKED_LIST(f64, f64)
DEFINE_DOUBLE_LINKED_LIST(f128, f128)

#endif // _DOUBLE_LINKED_LIST_H_
