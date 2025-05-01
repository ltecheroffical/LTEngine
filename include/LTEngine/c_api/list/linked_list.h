#ifndef LTENGINE_C_API_LIST_LINKED_LIST_H_
#define LTENGINE_C_API_LIST_LINKED_LIST_H_
#ifdef LTENGINE_COMPONENT_C_API

#include <stddef.h>
#include <stdlib.h>

#include <LTEngine/common/compiler_utils.h>


#define LTENGINE_DEFINE_LINKED_LIST(type, type_name) \
    typedef struct LTEngine_LinkedListNode_##type_name { \
        struct LTEngine_LinkedListNode_##type_name *next; \
        struct LTEngine_LinkedListNode_##type_name *prev; \
        type data; \
    } LTEngine_LinkedListNode_##type_name; \
    \
    typedef struct { \
        size_t size; \
        LTEngine_LinkedListNode_##type_name *head; \
        LTEngine_LinkedListNode_##type_name *tail; \
    } LTEngine_LinkedList_##type_name; \
    \
    LTEngine_LinkedList_##type_name LTEngine_LinkedList_##type_name##_create(); \
    void LTEngine_LinkedList_##type_name##_free(LTEngine_LinkedList_##type_name *list); \
    \
    size_t LTEngine_LinkedList_##type_name##_size(const LTEngine_LinkedList_##type_name *list); \
    bool LTEngine_LinkedList_##type_name##_add(LTEngine_LinkedList_##type_name *list, type data); \
    bool LTEngine_LinkedList_##type_name##_addToNode(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node, type data); \
    \
    void LTEngine_LinkedList_##type_name##_remove(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node); \
    void LTEngine_LinkedList_##type_name##_set(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node, type data); \
    type LTEngine_LinkedList_##type_name##_get(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node); \
    \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedList_##type_name##_getHead(LTEngine_LinkedList_##type_name *list); \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedList_##type_name##_getTail(LTEngine_LinkedList_##type_name *list); \
    \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedListNode_##type_name##_prev(LTEngine_LinkedListNode_##type_name *node); \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedListNode_##type_name##_next(LTEngine_LinkedListNode_##type_name *node);

#define LTENGINE_DEFINE_LINKED_LIST_LOGIC(type, type_name) \
    LTEngine_LinkedList_##type_name LTEngine_LinkedList_##type_name##_create() { \
        LTEngine_LinkedList_##type_name list; \
        list.size = 0; \
        list.head = NULL; \
        list.tail = NULL; \
        return list; \
    } \
    void LTEngine_LinkedList_##type_name##_free(LTEngine_LinkedList_##type_name *list) { \
        if (list->tail != NULL) { \
            LTEngine_LinkedListNode_##type_name *node = list->tail; \
            LTEngine_LinkedListNode_##type_name *prev = node->prev; \
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
    size_t LTEngine_LinkedList_##type_name##_size(const LTEngine_LinkedList_##type_name *list) { \
        return list->size; \
    } \
    \
    bool LTEngine_LinkedList_##type_name##_add(LTEngine_LinkedList_##type_name *list, type data) { \
        LTEngine_LinkedListNode_##type_name *node = (LTEngine_LinkedListNode_##type_name *)malloc(sizeof(LTEngine_LinkedListNode_##type_name)); \
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
    bool LTEngine_LinkedList_##type_name##_addToNode(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node, type data) { \
        LTEngine_LinkedListNode_##type_name *newNode = (LTEngine_LinkedListNode_##type_name *)malloc(sizeof(LTEngine_LinkedListNode_##type_name)); \
        if (newNode == NULL) { \
            return false; \
        } \
        LTEngine_LinkedListNode_##type_name *prevNext = node->next; \
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
    void LTEngine_LinkedList_##type_name##_remove(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node) { \
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
    void LTEngine_LinkedList_##type_name##_set(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node, type data) { \
        node->data = data; \
    } \
    type LTEngine_LinkedList_##type_name##_get(LTEngine_LinkedList_##type_name *list, LTEngine_LinkedListNode_##type_name *node) { \
        return node->data; \
    } \
    \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedList_##type_name##_getHead(LTEngine_LinkedList_##type_name *list) { \
        return list->head; \
    } \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedList_##type_name##_getTail(LTEngine_LinkedList_##type_name *list) { \
        return list->tail; \
    } \
    \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedListNode_##type_name##_prev(LTEngine_LinkedListNode_##type_name *node) { \
        return node->prev; \
    } \
    LTEngine_LinkedListNode_##type_name *LTEngine_LinkedListNode_##type_name##_next(LTEngine_LinkedListNode_##type_name *node) { \
        return node->next; \
    }
    

#ifdef __cplusplus
extern "C" {
#endif

LTENGINE_DEFINE_LINKED_LIST(LTEngine_u8,  u8);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_u16, u16);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_u32, u32);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_u64, u64);

LTENGINE_DEFINE_LINKED_LIST(LTEngine_i8,  i8);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_i16, i16);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_i32, i32);
LTENGINE_DEFINE_LINKED_LIST(LTEngine_i64, i64);

#ifdef __cplusplus
}
#endif
#endif
#endif // LTENGINE_C_API_LIST_LINKED_LIST_H_