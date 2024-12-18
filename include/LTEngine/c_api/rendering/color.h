#ifndef _LTENGINE_C_API_COLOR_H_
#define _LTENGINE_C_API_COLOR_H_


#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/common/types/inttypes.h>


typedef void *LTEngine_HColor;
typedef void *LTEngine_HColorA;


#ifdef __cplusplus
extern "C" {
#endif


LTEngine_HColor LTENGINE_API LTEngine_CreateColor(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b);
void LTENGINE_API LTEngine_DestroyColor(LTEngine_HColor color);

void LTENGINE_API LTEngine_SetColor(LTEngine_HColor color, LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b);
void LTENGINE_API LTEngine_SetColorR(LTEngine_HColor color, LTEngine_u8 r);
void LTENGINE_API LTEngine_SetColorG(LTEngine_HColor color, LTEngine_u8 g);
void LTENGINE_API LTEngine_SetColorB(LTEngine_HColor color, LTEngine_u8 b);

LTEngine_u8 LTENGINE_API LTEngine_GetColorR(const LTEngine_HColor color);
LTEngine_u8 LTENGINE_API LTEngine_GetColorG(const LTEngine_HColor color);
LTEngine_u8 LTENGINE_API LTEngine_GetColorB(const LTEngine_HColor color);

LTEngine_HColor LTENGINE_API LTEngine_AddColor(LTEngine_HColor a, const LTEngine_HColor b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_AddiColor(LTEngine_HColor a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_SubColor(LTEngine_HColor a, const LTEngine_HColor b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_SubiColor(LTEngine_HColor a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_MulColor(LTEngine_HColor a, const LTEngine_HColor b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_MuliColor(LTEngine_HColor a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_DivColor(LTEngine_HColor a, const LTEngine_HColor b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColor LTENGINE_API LTEngine_DiviColor(LTEngine_HColor a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;


LTEngine_HColorA LTENGINE_API LTEngine_CreateColorA(LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b);
void LTENGINE_API LTEngine_DestroyColorA(LTEngine_HColorA color);

void LTENGINE_API LTEngine_SetColorA(LTEngine_HColorA color, LTEngine_u8 r, LTEngine_u8 g, LTEngine_u8 b, LTEngine_u8 a);
void LTENGINE_API LTEngine_SetColorAR(LTEngine_HColorA color, LTEngine_u8 r);
void LTENGINE_API LTEngine_SetColorAG(LTEngine_HColorA color, LTEngine_u8 g);
void LTENGINE_API LTEngine_SetColorAB(LTEngine_HColorA color, LTEngine_u8 b);
void LTENGINE_API LTEngine_SetColorAA(LTEngine_HColorA color, LTEngine_u8 a);

LTEngine_u8 LTENGINE_API LTEngine_GetColorAR(const LTEngine_HColorA color);
LTEngine_u8 LTENGINE_API LTEngine_GetColorAG(const LTEngine_HColorA color);
LTEngine_u8 LTENGINE_API LTEngine_GetColorAB(const LTEngine_HColorA color);
LTEngine_u8 LTENGINE_API LTEngine_GetColorAA(const LTEngine_HColorA color);

LTEngine_HColorA LTENGINE_API LTEngine_AddColorA(LTEngine_HColorA a, const LTEngine_HColorA b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_AddiColorA(LTEngine_HColorA a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_SubColorA(LTEngine_HColorA a, const LTEngine_HColorA b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_SubiColorA(LTEngine_HColorA a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_MulColorA(LTEngine_HColorA a, const LTEngine_HColorA b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_MuliColorA(LTEngine_HColorA a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_DivColorA(LTEngine_HColorA a, const LTEngine_HColorA b) LTENGINE_WARN_UNUSED_RESULT;
LTEngine_HColorA LTENGINE_API LTEngine_DiviColorA(LTEngine_HColorA a, LTEngine_i32 b) LTENGINE_WARN_UNUSED_RESULT;


#ifdef __cplusplus
}
#endif
#endif
