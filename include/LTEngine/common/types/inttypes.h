#ifndef _LTENGINE_INTTYPES_H_
#define _LTENGINE_INTTYPES_H_

#include <stdint.h>


typedef uint8_t LTEngine_uint8;
typedef uint16_t LTEngine_uint16;
typedef uint32_t LTEngine_uint32;
typedef uint64_t LTEngine_uint64;

typedef int8_t LTEngine_int8;
typedef int16_t LTEngine_int16;
typedef int32_t LTEngine_int32;
typedef int64_t LTEngine_int64;


typedef LTEngine_uint8 LTEngine_u8;
typedef LTEngine_uint16 LTEngine_u16;
typedef LTEngine_uint32 LTEngine_u32;
typedef LTEngine_uint64 LTEngine_u64;

typedef LTEngine_int8 LTEngine_i8;
typedef LTEngine_int16 LTEngine_i16;
typedef LTEngine_int32 LTEngine_i32;
typedef LTEngine_int64 LTEngine_i64;


#ifdef __cplusplus
namespace LTEngine {
	typedef LTEngine_uint8 uint8;
	typedef LTEngine_uint16 uint16;
	typedef LTEngine_uint32 uint32;
	typedef LTEngine_uint64 uint64;

	typedef LTEngine_int8 int8;
	typedef LTEngine_int16 int16;
	typedef LTEngine_int32 int32;
	typedef LTEngine_int64 int64;


	typedef LTEngine_uint8 u8;
	typedef LTEngine_uint16 u16;
	typedef LTEngine_uint32 u32;
	typedef LTEngine_uint64 u64;

	typedef LTEngine_int8 i8;
	typedef LTEngine_int16 i16;
	typedef LTEngine_int32 i32;
	typedef LTEngine_int64 i64;
} // namespace LTEngine
#endif


#ifdef LTENGINE_GLOBAL_BASIC_TYPES

typedef LTEngine_uint8 uint8;
typedef LTEngine_uint16 uint16;
typedef LTEngine_uint32 uint32;
typedef LTEngine_uint64 uint64;

typedef LTEngine_int8 int8;
typedef LTEngine_int16 int16;
typedef LTEngine_int32 int32;
typedef LTEngine_int64 int64;


typedef LTEngine_u8 u8;
typedef LTEngine_u16 u16;
typedef LTEngine_u32 u32;
typedef LTEngine_u64 u64;

typedef LTEngine_i8 i8;
typedef LTEngine_i16 i16;
typedef LTEngine_i32 i32;
typedef LTEngine_i64 i64;

#endif
#endif
