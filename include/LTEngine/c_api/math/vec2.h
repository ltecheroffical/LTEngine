#ifndef _LTENGINE_C_API_VEC2_H_
#define _LTENGINE_C_API_VEC2_H_

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


typedef void *LTEngine_HVec2;
typedef void *LTEngine_HVec2i;
typedef void *LTEngine_HVec2u;

typedef LTEngine_HVec2 LTEngine_HVec2f;


#ifdef __cplusplus
extern "C" {
#endif


LTEngine_HVec2 LTENGINE_API LTEngine_CreateVec2(LTEngine_f32 x, LTEngine_f32 y);
void LTENGINE_API LTEngine_DestroyVec2(LTEngine_HVec2 vec2);

void LTENGINE_API LTEngine_SetVec2X(LTEngine_HVec2 vec2, LTEngine_f32 x);
void LTENGINE_API LTEngine_SetVec2Y(LTEngine_HVec2 vec2, LTEngine_f32 y);

LTEngine_f32 LTENGINE_API LTEngine_GetVec2X(const LTEngine_HVec2 vec2);
LTEngine_f32 LTENGINE_API LTEngine_GetVec2Y(const LTEngine_HVec2 vec2);

LTEngine_HVec2 LTENGINE_API LTEngine_NormalizeVec2(LTEngine_HVec2 vec2) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_f32 LTENGINE_API LTEngine_Vec2Distance(const LTEngine_HVec2 a, const LTEngine_HVec2 b);

LTEngine_HVec2 LTENGINE_API LTEngine_AddVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_AddiVec2(LTEngine_HVec2 a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_AddfVec2(LTEngine_HVec2 a, LTEngine_f32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_SubVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_SubiVec2(LTEngine_HVec2 a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_SubfVec2(LTEngine_HVec2 a, LTEngine_f32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_MulVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_MuliVec2(LTEngine_HVec2 a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_MulfVec2(LTEngine_HVec2 a, LTEngine_f32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_DivVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_DiviVec2(LTEngine_HVec2 a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2 LTENGINE_API LTEngine_DivfVec2(LTEngine_HVec2 a, LTEngine_f32 b) LTENGINE_WARN_UNUSED_RESULT;


LTEngine_HVec2i LTENGINE_API LTEngine_CreateVec2i(LTEngine_i32 x, LTEngine_i32 y);
void LTENGINE_API LTEngine_DestroyVec2i(LTEngine_HVec2i vec2);

void LTENGINE_API LTEngine_SetVec2iX(LTEngine_HVec2i vec2, LTEngine_i32 x);
void LTENGINE_API LTEngine_SetVec2iY(LTEngine_HVec2i vec2, LTEngine_i32 y);

LTEngine_i32 LTENGINE_API LTEngine_GetVec2iX(const LTEngine_HVec2i vec2);
LTEngine_i32 LTENGINE_API LTEngine_GetVec2iY(const LTEngine_HVec2i vec2);

LTEngine_HVec2i LTENGINE_API LTEngine_NormalizeVec2i(LTEngine_HVec2i vec2) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_f32 LTENGINE_API LTEngine_Vec2iDistance(const LTEngine_HVec2i a, const LTEngine_HVec2i b);

LTEngine_HVec2i LTENGINE_API LTEngine_AddVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_AddiVec2i(LTEngine_HVec2i a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_SubVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_SubiVec2i(LTEngine_HVec2i a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_MulVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_MuliVec2i(LTEngine_HVec2i a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_DivVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2i LTENGINE_API LTEngine_DiviVec2i(LTEngine_HVec2i a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;


LTEngine_HVec2u LTENGINE_API LTEngine_CreateVec2u(LTEngine_u32 x, LTEngine_u32 y);
void LTENGINE_API LTEngine_DestroyVec2u(LTEngine_HVec2u vec2);

void LTENGINE_API LTEngine_SetVec2uX(LTEngine_HVec2u vec2, LTEngine_u32 x);
void LTENGINE_API LTEngine_SetVec2uY(LTEngine_HVec2u vec2, LTEngine_u32 y);

LTEngine_u32 LTENGINE_API LTEngine_GetVec2uX(const LTEngine_HVec2u vec2);
LTEngine_u32 LTENGINE_API LTEngine_GetVec2uY(const LTEngine_HVec2u vec2);

LTEngine_HVec2u LTENGINE_API LTEngine_AddVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_AddiVec2u(LTEngine_HVec2u a, LTEngine_u32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_SubVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_SubiVec2u(LTEngine_HVec2u a, LTEngine_u32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_MulVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_MuliVec2u(LTEngine_HVec2u a, LTEngine_u32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_DivVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HVec2u LTENGINE_API LTEngine_DiviVec2u(LTEngine_HVec2u a, LTEngine_u32 b) LTENGINE_WARN_UNUSED_RESULT;


#ifdef __cplusplus
}
#endif
#endif
