#ifndef _LTCORE_C_API_DYNAMIC_ARRAY_
#define _LTCORE_C_API_DYNAMIC_ARRAY_
#ifdef LTCORE_COMPONENT_C_API

#include <stddef.h>
#include <stdlib.h>

#include <LTCore/common/compiler_utils.h>

#define LTCORE_DEFINE_DYNAMIC_ARRAY(type, type_name) \
    typedef struct { \
        type *data; \
        size_t size; \
        size_t capacity; \
    } LTCore_DynamicArray_##type_name; \
    \
    LTCore_DynamicArray_##type_name LTCore_DynamicArray_##type_name##_create(); \
    LTCore_DynamicArray_##type_name LTCore_DynamicArray_##type_name##_createWithCapacity(size_t capacity); \
    void LTCore_DynamicArray_##type_name##_free(LTCore_DynamicArray_##type_name *array); \
    \
    size_t LTCore_DynamicArray_##type_name##_size(const LTCore_DynamicArray_##type_name *array); \
    \
    void LTCore_DynamicArray_##type_name##_add(LTCore_DynamicArray_##type_name *array, type value); \
    void LTCore_DynamicArray_##type_name##_remove(LTCore_DynamicArray_##type_name *array, size_t index); \
    void *LTCore_DynamicArray_##type_name##_ptr(LTCore_DynamicArray_##type_name *array, size_t index); \
    type LTCore_DynamicArray_##type_name##_get(const LTCore_DynamicArray_##type_name *array, size_t index)

#define LTCORE_DEFINE_DYNAMIC_ARRAY_LOGIC(type, type_name) \
    LTCore_DynamicArray_##type_name LTCore_DynamicArray_##type_name##_create() { \
        LTCore_DynamicArray_##type_name array; \
        array.size = 0; \
        array.capacity = 1; \
        array.data = (type*)malloc(sizeof(type)); \
        return array; \
    } \
    LTCore_DynamicArray_##type_name LTCore_DynamicArray_##type_name##_createWithCapacity(size_t capacity) { \
        LTCore_DynamicArray_##type_name array; \
        array.size = 0; \
        array.capacity = capacity; \
        array.data = (type*)malloc(sizeof(type) * array.capacity); \
        return array; \
    } \
    void LTCore_DynamicArray_##type_name##_free(LTCore_DynamicArray_##type_name *array) { \
        array->capacity = 0; \
        array->size = 0; \
        free(array->data); \
    } \
    \
    size_t LTCore_DynamicArray_##type_name##_size(const LTCore_DynamicArray_##type_name *array) { \
        return array->size; \
    } \
    \
    void LTCore_DynamicArray_##type_name##_add(LTCore_DynamicArray_##type_name *array, type value) { \
        if (array->size >= array->capacity) { \
            array->capacity *= 2; \
            array->data = (type*)realloc(array->data, array->capacity); \
        } \
        \
        array->data[array->size] = value; \
        array->size++; \
    } \
    void LTCore_DynamicArray_##type_name##_remove(LTCore_DynamicArray_##type_name *array, size_t index) { \
        for (size_t i = index; i < array->size - 1; i++) { \
            array->data[i] = array->data[i + 1]; \
        } \
        array->size--; \
    } \
    void *LTCore_DynamicArray_##type_name##_ptr(LTCore_DynamicArray_##type_name *array, size_t index) { \
        return &array->data[index]; \
    } \
    type LTCore_DynamicArray_##type_name##_get(const LTCore_DynamicArray_##type_name *array, size_t index) { \
        return array->data[index]; \
    } \
    

#ifdef __cplusplus
extern "C" {
#endif

LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_u8,  u8);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_u16, u16);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_u32, u32);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_u64, u64);

LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_i8,  i8);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_i16, i16);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_i32, i32);
LTCORE_DEFINE_DYNAMIC_ARRAY(LTCore_i64, i64);

#ifdef __cplusplus
}
#endif

#endif
#endif