#ifndef _LTENGINE_C_API_DYNAMIC_ARRAY_
#define _LTENGINE_C_API_DYNAMIC_ARRAY_

#include <stddef.h>
#include <stdlib.h>

#include <LTEngine/common/compiler_utils.h>

#define LTENGINE_DEFINE_DYNAMIC_ARRAY(type, type_name) \
    typedef struct { \
        type *data; \
        size_t size; \
        size_t capacity; \
    } LTEngine_DynamicArray_##type_name; \
    \
    LTEngine_DynamicArray_##type_name LTEngine_DynamicArray_##type_name##_create(); \
    LTEngine_DynamicArray_##type_name LTEngine_DynamicArray_##type_name##_createWithCapacity(size_t capacity); \
    void LTEngine_DynamicArray_##type_name##_free(LTEngine_DynamicArray_##type_name *array); \
    \
    size_t LTEngine_DynamicArray_##type_name##_size(const LTEngine_DynamicArray_##type_name *array); \
    \
    void LTEngine_DynamicArray_##type_name##_add(LTEngine_DynamicArray_##type_name *array, type value); \
    void LTEngine_DynamicArray_##type_name##_remove(LTEngine_DynamicArray_##type_name *array, size_t index); \
    void *LTEngine_DynamicArray_##type_name##_ptr(LTEngine_DynamicArray_##type_name *array, size_t index); \
    type LTEngine_DynamicArray_##type_name##_get(const LTEngine_DynamicArray_##type_name *array, size_t index)

#define LTENGINE_DEFINE_DYNAMIC_ARRAY_LOGIC(type, type_name) \
    LTEngine_DynamicArray_##type_name LTEngine_DynamicArray_##type_name##_create() { \
        LTEngine_DynamicArray_##type_name array; \
        array.size = 0; \
        array.capacity = 1; \
        array.data = (type*)malloc(sizeof(type)); \
        return array; \
    } \
    LTEngine_DynamicArray_##type_name LTEngine_DynamicArray_##type_name##_createWithCapacity(size_t capacity) { \
        LTEngine_DynamicArray_##type_name array; \
        array.size = 0; \
        array.capacity = capacity; \
        array.data = (type*)malloc(sizeof(type) * array.capacity); \
        return array; \
    } \
    void LTEngine_DynamicArray_##type_name##_free(LTEngine_DynamicArray_##type_name *array) { \
        array->capacity = 0; \
        array->size = 0; \
        free(array->data); \
    } \
    \
    size_t LTEngine_DynamicArray_##type_name##_size(const LTEngine_DynamicArray_##type_name *array) { \
        return array->size; \
    } \
    \
    void LTEngine_DynamicArray_##type_name##_add(LTEngine_DynamicArray_##type_name *array, type value) { \
        if (array->size >= array->capacity) { \
            array->capacity *= 2; \
            array->data = (type*)realloc(array->data, array->capacity); \
        } \
        \
        array->data[array->size] = value; \
        array->size++; \
    } \
    void LTEngine_DynamicArray_##type_name##_remove(LTEngine_DynamicArray_##type_name *array, size_t index) { \
        for (size_t i = index; i < array->size - 1; i++) { \
            array->data[i] = array->data[i + 1]; \
        } \
        array->size--; \
    } \
    void *LTEngine_DynamicArray_##type_name##_ptr(LTEngine_DynamicArray_##type_name *array, size_t index) { \
        return &array->data[index]; \
    } \
    type LTEngine_DynamicArray_##type_name##_get(const LTEngine_DynamicArray_##type_name *array, size_t index) { \
        return array->data[index]; \
    } \
    


LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_u8,  u8);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_u16, u16);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_u32, u32);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_u64, u64);

LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_i8,  i8);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_i16, i16);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_i32, i32);
LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_i64, i64);

#endif