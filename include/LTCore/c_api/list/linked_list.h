#ifndef LTCORE_C_API_LIST_LINKED_LIST_H_
#define LTCORE_C_API_LIST_LINKED_LIST_H_
#ifdef LTCORE_COMPONENT_C_API

#include <stddef.h>
#include <stdlib.h>

#include <LTCore/common/compiler_utils.h>


#define LTCORE_DEFINE_LINKED_LIST(type, type_name) \
    typedef struct LTCore_LinkedListNode_##type_name { \
        struct LTCore_LinkedListNode_##type_name *next; \
        struct LTCore_LinkedListNode_##type_name *prev; \
        type data; \
    } LTCore_LinkedListNode_##type_name; \
    \
    typedef struct { \
        size_t size; \
        LTCore_LinkedListNode_##type_name *head; \
        LTCore_LinkedListNode_##type_name *tail; \
    } LTCore_LinkedList_##type_name; \
    \
    LTCore_LinkedList_##type_name LTCore_LinkedList_##type_name##_create(); \
    void LTCore_LinkedList_##type_name##_free(LTCore_LinkedList_##type_name *list); \
    \
    size_t LTCore_LinkedList_##type_name##_size(const LTCore_LinkedList_##type_name *list); \
    bool LTCore_LinkedList_##type_name##_add(LTCore_LinkedList_##type_name *list, type data); \
    bool LTCore_LinkedList_##type_name##_addToNode(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node, type data); \
    \
    void LTCore_LinkedList_##type_name##_remove(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node); \
    void LTCore_LinkedList_##type_name##_set(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node, type data); \
    type LTCore_LinkedList_##type_name##_get(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node); \
    \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedList_##type_name##_getHead(LTCore_LinkedList_##type_name *list); \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedList_##type_name##_getTail(LTCore_LinkedList_##type_name *list); \
    \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedListNode_##type_name##_prev(LTCore_LinkedListNode_##type_name *node); \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedListNode_##type_name##_next(LTCore_LinkedListNode_##type_name *node);

#define LTCORE_DEFINE_LINKED_LIST_LOGIC(type, type_name) \
    LTCore_LinkedList_##type_name LTCore_LinkedList_##type_name##_create() { \
        LTCore_LinkedList_##type_name list; \
        list.size = 0; \
        list.head = NULL; \
        list.tail = NULL; \
        return list; \
    } \
    void LTCore_LinkedList_##type_name##_free(LTCore_LinkedList_##type_name *list) { \
        if (list->tail != NULL) { \
            LTCore_LinkedListNode_##type_name *node = list->tail; \
            LTCore_LinkedListNode_##type_name *prev = node->prev; \
            while (node != NULL) { \
                free(node); \
                node = prev; \
                prev = node->prev; \
            } \
        } \
        list->size = 0; \
        list->head = NULL; \
        list->tail = NULL; \
    } \
    \
    \
    size_t LTCore_LinkedList_##type_name##_size(const LTCore_LinkedList_##type_name *list) { \
        return list->size; \
    } \
    \
    bool LTCore_LinkedList_##type_name##_add(LTCore_LinkedList_##type_name *list, type data) { \
        LTCore_LinkedListNode_##type_name *node = (LTCore_LinkedListNode_##type_name *)malloc(sizeof(LTCore_LinkedListNode_##type_name)); \
        if (node == NULL) { \
            return false; \
        } \
        node->next = NULL; \
        node->prev = list->tail; \
        if (list->tail == NULL) { \
            list->head = node; \
        } else { \
            list->tail->next = node; \
        } \
        node->data = data; \
        list->tail = node; \
        list->size++; \
        return true; \
    } \
    \
    bool LTCore_LinkedList_##type_name##_addToNode(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node, type data) { \
        LTCore_LinkedListNode_##type_name *newNode = (LTCore_LinkedListNode_##type_name *)malloc(sizeof(LTCore_LinkedListNode_##type_name)); \
        if (newNode == NULL) { \
            return false; \
        } \
        LTCore_LinkedListNode_##type_name *prevNext = node->next; \
        if (prevNext != NULL) { \
            prevNext->prev = newNode; \
        } else { \
            list->tail = newNode; \
        } \
        newNode->next = prevNext; \
        newNode->prev = node; \
        newNode->data = data; \
        node->next = newNode; \
        list->size++; \
        return true; \
    } \
    \
    void LTCore_LinkedList_##type_name##_remove(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node) { \
        if (node == list->head) { \
            list->head = node->next; \
        } \
        if (node == list->tail) { \
            list->tail = node->prev; \
        } \
        \
        if (node->next != NULL) { \
            node->next->prev = node->prev; \
        } \
        if (node->prev != NULL) { \
            node->prev->next = node->next; \
        } \
        free(node); \
        list->size--; \
    } \
    \
    void LTCore_LinkedList_##type_name##_set(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node, type data) { \
        node->data = data; \
    } \
    type LTCore_LinkedList_##type_name##_get(LTCore_LinkedList_##type_name *list, LTCore_LinkedListNode_##type_name *node) { \
        return node->data; \
    } \
    \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedList_##type_name##_getHead(LTCore_LinkedList_##type_name *list) { \
        return list->head; \
    } \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedList_##type_name##_getTail(LTCore_LinkedList_##type_name *list) { \
        return list->tail; \
    } \
    \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedListNode_##type_name##_prev(LTCore_LinkedListNode_##type_name *node) { \
        return node->prev; \
    } \
    LTCore_LinkedListNode_##type_name *LTCore_LinkedListNode_##type_name##_next(LTCore_LinkedListNode_##type_name *node) { \
        return node->next; \
    }
    

#ifdef __cplusplus
extern "C" {
#endif

LTCORE_DEFINE_LINKED_LIST(LTCore_u8,  u8);
LTCORE_DEFINE_LINKED_LIST(LTCore_u16, u16);
LTCORE_DEFINE_LINKED_LIST(LTCore_u32, u32);
LTCORE_DEFINE_LINKED_LIST(LTCore_u64, u64);

LTCORE_DEFINE_LINKED_LIST(LTCore_i8,  i8);
LTCORE_DEFINE_LINKED_LIST(LTCore_i16, i16);
LTCORE_DEFINE_LINKED_LIST(LTCore_i32, i32);
LTCORE_DEFINE_LINKED_LIST(LTCore_i64, i64);

#ifdef __cplusplus
}
#endif
#endif
#endif // LTCORE_C_API_LIST_LINKED_LIST_H_