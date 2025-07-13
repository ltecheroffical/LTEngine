#ifndef _LTENGINE_C_API_RANDOM_H_
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_RANDOM_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct LTENGINE_API {
	void *(*init)();
	void (*free)(void *ctx);

	LTEngine_u8 (*next_u8)(void *ctx);
	LTEngine_u16 (*next_u16)(void *ctx);
	LTEngine_u32 (*next_u32)(void *ctx);
	LTEngine_u64 (*next_u64)(void *ctx);

	LTEngine_i8 (*next_i8)(void *ctx);
	LTEngine_i16 (*next_i16)(void *ctx);
	LTEngine_i32 (*next_i32)(void *ctx);
	LTEngine_i64 (*next_i64)(void *ctx);

	LTEngine_f32 (*next_f32)(void *ctx);
	LTEngine_f64 (*next_f64)(void *ctx);

	void (*nextBytes)(void *ctx, void *data, size_t size);
} LTEngine_CustomRandomFuncs;

typedef struct {
	LTEngine_HANDLE handle;
 } LTEngine_HRandom;


LTEngine_HRandom LTENGINE_API LTEngine_CustomRandom(LTEngine_CustomRandomFuncs funcs);
void LTENGINE_API LTEngine_CustomRandom_free(LTEngine_HRandom handle);

LTEngine_u8 LTENGINE_API LTEngine_Random_next_u8(LTEngine_HRandom handle);
LTEngine_u16 LTENGINE_API LTEngine_Random_next_u16(LTEngine_HRandom handle);
LTEngine_u32 LTENGINE_API LTEngine_Random_next_u32(LTEngine_HRandom handle);
LTEngine_u64 LTENGINE_API LTEngine_Random_next_u64(LTEngine_HRandom handle);

LTEngine_i8 LTENGINE_API LTEngine_Random_next_i8(LTEngine_HRandom handle);
LTEngine_i16 LTENGINE_API LTEngine_Random_next_i16(LTEngine_HRandom handle);
LTEngine_i32 LTENGINE_API LTEngine_Random_next_i32(LTEngine_HRandom handle);
LTEngine_i64 LTENGINE_API LTEngine_Random_next_i64(LTEngine_HRandom handle);

LTEngine_f32 LTENGINE_API LTEngine_Random_next_f32(LTEngine_HRandom handle);
LTEngine_f64 LTENGINE_API LTEngine_Random_next_f64(LTEngine_HRandom handle);


#ifdef __cplusplus
}
#endif
#endif
#endif