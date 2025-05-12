#ifndef _LTCORE_C_API_RANDOM_H_
#ifdef LTCORE_COMPONENT_C_API
#define _LTCORE_C_API_RANDOM_H_

#include <LTCore/c_api/common/ctypes.h>
#include <LTCore/common/compiler_utils.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct LTCORE_API {
	void *(*init)();
	void (*free)(void *ctx);

	LTCore_u8 (*next_u8)(void *ctx);
	LTCore_u16 (*next_u16)(void *ctx);
	LTCore_u32 (*next_u32)(void *ctx);
	LTCore_u64 (*next_u64)(void *ctx);

	LTCore_i8 (*next_i8)(void *ctx);
	LTCore_i16 (*next_i16)(void *ctx);
	LTCore_i32 (*next_i32)(void *ctx);
	LTCore_i64 (*next_i64)(void *ctx);

	LTCore_f32 (*next_f32)(void *ctx);
	LTCore_f64 (*next_f64)(void *ctx);

	void (*nextBytes)(void *ctx, void *data, size_t size);
} LTCore_CustomRandomFuncs;

typedef struct {
	LTCore_HANDLE handle;
 } LTCore_HRandom;


LTCore_HRandom LTCORE_API LTCore_CustomRandom(LTCore_CustomRandomFuncs funcs);
void LTCORE_API LTCore_CustomRandom_free(LTCore_HRandom handle);

LTCore_u8 LTCORE_API LTCore_Random_next_u8(LTCore_HRandom handle);
LTCore_u16 LTCORE_API LTCore_Random_next_u16(LTCore_HRandom handle);
LTCore_u32 LTCORE_API LTCore_Random_next_u32(LTCore_HRandom handle);
LTCore_u64 LTCORE_API LTCore_Random_next_u64(LTCore_HRandom handle);

LTCore_i8 LTCORE_API LTCore_Random_next_i8(LTCore_HRandom handle);
LTCore_i16 LTCORE_API LTCore_Random_next_i16(LTCore_HRandom handle);
LTCore_i32 LTCORE_API LTCore_Random_next_i32(LTCore_HRandom handle);
LTCore_i64 LTCORE_API LTCore_Random_next_i64(LTCore_HRandom handle);

LTCore_f32 LTCORE_API LTCore_Random_next_f32(LTCore_HRandom handle);
LTCore_f64 LTCORE_API LTCore_Random_next_f64(LTCore_HRandom handle);


#ifdef __cplusplus
}
#endif
#endif
#endif