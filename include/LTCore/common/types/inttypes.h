#ifndef _LTCORE_INTTYPES_H_
#define _LTCORE_INTTYPES_H_

#include <stdint.h>


typedef uint8_t LTCore_uint8;
typedef uint16_t LTCore_uint16;
typedef uint32_t LTCore_uint32;
typedef uint64_t LTCore_uint64;

typedef int8_t LTCore_int8;
typedef int16_t LTCore_int16;
typedef int32_t LTCore_int32;
typedef int64_t LTCore_int64;


typedef LTCore_uint8 LTCore_u8;
typedef LTCore_uint16 LTCore_u16;
typedef LTCore_uint32 LTCore_u32;
typedef LTCore_uint64 LTCore_u64;

typedef LTCore_int8 LTCore_i8;
typedef LTCore_int16 LTCore_i16;
typedef LTCore_int32 LTCore_i32;
typedef LTCore_int64 LTCore_i64;


#ifdef __cplusplus
namespace LTCore {
	typedef LTCore_uint8 uint8;
	typedef LTCore_uint16 uint16;
	typedef LTCore_uint32 uint32;
	typedef LTCore_uint64 uint64;

	typedef LTCore_int8 int8;
	typedef LTCore_int16 int16;
	typedef LTCore_int32 int32;
	typedef LTCore_int64 int64;


	typedef LTCore_uint8 u8;
	typedef LTCore_uint16 u16;
	typedef LTCore_uint32 u32;
	typedef LTCore_uint64 u64;

	typedef LTCore_int8 i8;
	typedef LTCore_int16 i16;
	typedef LTCore_int32 i32;
	typedef LTCore_int64 i64;
} // namespace LTCore
#endif


#ifdef LTCORE_GLOBAL_BASIC_TYPES

typedef LTCore_uint8 uint8;
typedef LTCore_uint16 uint16;
typedef LTCore_uint32 uint32;
typedef LTCore_uint64 uint64;

typedef LTCore_int8 int8;
typedef LTCore_int16 int16;
typedef LTCore_int32 int32;
typedef LTCore_int64 int64;


typedef LTCore_u8 u8;
typedef LTCore_u16 u16;
typedef LTCore_u32 u32;
typedef LTCore_u64 u64;

typedef LTCore_i8 i8;
typedef LTCore_i16 i16;
typedef LTCore_i32 i32;
typedef LTCore_i64 i64;

#endif
#endif
