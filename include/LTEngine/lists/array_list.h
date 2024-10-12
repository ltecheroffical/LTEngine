#include <stdlib.h>

#include <LTEngine/util/types/inttypes.h>
#include <LTEngine/util/types/floattypes.h>

#ifndef _LTARRAY_LIST_H_
#define _LTARRAY_LIST_H_

#define DEFINE_ARRAY_LIST(type, tname) \
    typedef struct { \
        type *_data; \
        u32 _size; \
        u32 _capacity; \
    } ltarray_list_##tname##_t; \
    \
    \
    inline ltarray_list_##tname##_t ltarray_list_new_##tname() { \
        ltarray_list_##tname##_t list; \
        \
        list._data = (type*)malloc(sizeof(type)); \
        list._size = 0; \
        list._capacity = 1; \
        return list; \
    } \
    inline ltarray_list_##tname##_t ltarray_list_new_capacity_##tname(u32 capacity) { \
        ltarray_list_##tname##_t list; \
        \
        list._data = (type*)malloc(capacity * sizeof(type)); \
        list._size = 0; \
        list._capacity = capacity; \
        return list; \
    } \
    \
    inline void ltarray_list_free_##tname(ltarray_list_##tname##_t *list) { \
        free(list->_data); \
        list->_data = NULL; \
        list->_size = 0; \
        list->_capacity = 0; \
    } \
    \
    \
    inline type ltarray_list_get_##tname(const ltarray_list_##tname##_t *list, u32 index) { \
        return list->_data[index]; \
    } \
    \
    inline void ltarray_list_set_##tname(ltarray_list_##tname##_t *list, u32 index, type data) { \
        list->_data[index] = data; \
    } \
    \
    \
    inline void ltarray_list_push_back_##tname(ltarray_list_##tname##_t *list, type data) { \
        if (list->_size >= list->_capacity) { \
            list->_capacity *= 2; \
            list->_data = (type*)realloc(list->_data, list->_capacity * sizeof(type)); \
        } \
        list->_data[list->_size++] = data; \
    } \
    \
    inline void ltarray_list_push_front_##tname(ltarray_list_##tname##_t *list, type data) { \
        if (list->_size >= list->_capacity) { \
            list->_capacity *= 2; \
            list->_data = (type*)realloc(list->_data, list->_capacity * sizeof(type)); \
        } \
        for (u32 i = list->_size; i > 0; i--) { \
            list->_data[i] = list->_data[i - 1]; \
        } \
        list->_data[0] = data; \
        list->_size++; \
    } \
    \
    inline void ltarray_list_insert_at_##tname(ltarray_list_##tname##_t *list, u32 index, type data) { \
        if (list->_size >= list->_capacity) { \
            list->_capacity *= 2; \
            list->_data = (type*)realloc(list->_data, list->_capacity * sizeof(type)); \
        } \
        for (u32 i = list->_size; i > index; i--) { \
            list->_data[i] = list->_data[i - 1]; \
        } \
        list->_data[index] = data; \
        list->_size++; \
    } \
    \
    inline void ltarray_list_pop_back_##tname(ltarray_list_##tname##_t *list) { \
        list->_size--; \
    } \
    \
    inline void ltarray_list_pop_front_##tname(ltarray_list_##tname##_t *list) { \
        for (u32 i = 0; i < list->_size - 1; i++) { \
            list->_data[i] = list->_data[i + 1]; \
        } \
        list->_size--; \
    } \
    \
    inline void ltarray_list_remove_at_##tname(ltarray_list_##tname##_t *list, u32 index) { \
        for (u32 i = index; i < list->_size - 1; i++) { \
            list->_data[i] = list->_data[i + 1]; \
        } \
        list->_size--; \
    }

DEFINE_ARRAY_LIST(u8, u8)
DEFINE_ARRAY_LIST(u16, u16)
DEFINE_ARRAY_LIST(u32, u32)
DEFINE_ARRAY_LIST(u64, u64)

DEFINE_ARRAY_LIST(i8, i8);
DEFINE_ARRAY_LIST(i16, i16)
DEFINE_ARRAY_LIST(i32, i32)
DEFINE_ARRAY_LIST(i64, i64)

DEFINE_ARRAY_LIST(f32, f32)
DEFINE_ARRAY_LIST(f64, f64)
DEFINE_ARRAY_LIST(f128, f128)

#endif // _ARRAY_LIST_H_
