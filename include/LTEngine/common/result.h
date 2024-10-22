#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


#define DEFINE_LTRESULT(type, name) \
    typedef struct { \
        ltresult_t _type; \
        type _value; \
    } ltresult_##name##_t; \
    \
    static ltresult_##name##_t ltresult_##name##_new(ltresult_t result_type, type value) { \
        ltresult_##name##_t result; \
        result._type = result_type; \
        result._value = value; \
        return result; \
    } \
    \
    static type ltresult_##name##_get_value(ltresult_##name##_t result) { \
        return result._value; \
    } \
    \
    static ltresult_t ltresult_##name##_get_result(ltresult_##name##_t result) { \
        return result._type; \
    }


typedef enum {
    LTRESULT_UNKNOWN = 0,

    LTRESULT_SUCCESS,
    LTRESULT_ERROR,
    

    LTRESULT_ERR_MEMORY,
    LTRESULT_ERR_FILE,
    LTRESULT_ERR_NOT_IMPLEMENTED,

    LTRESULT_ERR_INVALID_PARAM,


    LTRESULT_FATAL_ERROR,

    LTRESULT_FATAL_ERR_MEMORY,
    LTRESULT_FATAL_ERR_FILE,
} ltresult_t;


DEFINE_LTRESULT(u8,  u8)
DEFINE_LTRESULT(u16, u16)
DEFINE_LTRESULT(u32, u32)
DEFINE_LTRESULT(u64, u64)

DEFINE_LTRESULT(s8,  i8)
DEFINE_LTRESULT(s16, i16)
DEFINE_LTRESULT(s32, i32)
DEFINE_LTRESULT(s64, i64)

DEFINE_LTRESULT(f32, f32)
DEFINE_LTRESULT(f64, f64)
