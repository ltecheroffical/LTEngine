#ifndef _LTENGINE_C_API_VEC2_H_
#define _LTENGINE_C_API_VEC2_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>


typedef LTEngine_HANDLE LTEngine_HVec2;
typedef LTEngine_HANDLE LTEngine_HVec2i;
typedef LTEngine_HANDLE LTEngine_HVec2u;


#ifdef __cplusplus
extern "C" {
#endif

LTEngine_HVec2 LTENGINE_API LTEngine_Vec2_init(LTEngine_f32 x, LTEngine_f32 y);
void LTENGINE_API LTEngine_Vec2_free(LTEngine_HVec2 handle);

LTEngine_f32 LTENGINE_API LTEngine_Vec2_x(const LTEngine_HVec2 handle);
LTEngine_f32 LTENGINE_API LTEngine_Vec2_y(const LTEngine_HVec2 handle);

void LTENGINE_API LTEngine_Vec2_setX(LTEngine_HVec2 handle, LTEngine_f32 x);
void LTENGINE_API LTEngine_Vec2_setY(LTEngine_HVec2 handle, LTEngine_f32 y);

LTEngine_HVec2 LTENGINE_API LTEngine_Vec2_normalize(LTEngine_HVec2 handle);
LTEngine_f32 LTENGINE_API LTEngine_Vec2_distance(LTEngine_HVec2 handle1, LTEngine_HVec2 handle2);


LTEngine_HVec2i LTENGINE_API LTEngine_Vec2i_init(LTEngine_i32 x, LTEngine_i32 y);
void LTENGINE_API LTEngine_Vec2i_free(LTEngine_HVec2i handle);

LTEngine_i32 LTENGINE_API LTEngine_Vec2i_x(const LTEngine_HVec2i handle);
LTEngine_i32 LTENGINE_API LTEngine_Vec2i_y(const LTEngine_HVec2i handle);

void LTENGINE_API LTEngine_Vec2i_setX(LTEngine_HVec2i handle, LTEngine_i32 x);
void LTENGINE_API LTEngine_Vec2i_setY(LTEngine_HVec2i handle, LTEngine_i32 y);

LTEngine_HVec2i LTENGINE_API LTEngine_Vec2i_normalize(LTEngine_HVec2i handle);
LTEngine_f32 LTENGINE_API LTEngine_Vec2i_distance(LTEngine_HVec2i handle1, LTEngine_HVec2i handle2);


LTEngine_HVec2 LTENGINE_API LTEngine_Vec2u_init(LTEngine_u32 x, LTEngine_u32 y);
void LTENGINE_API LTEngine_Vec2u_free(LTEngine_HVec2u handle);

LTEngine_u32 LTENGINE_API LTEngine_Vec2u_x(const LTEngine_HVec2u handle);
LTEngine_u32 LTENGINE_API LTEngine_Vec2u_y(const LTEngine_HVec2u handle);

void LTENGINE_API LTEngine_Vec2u_setX(LTEngine_HVec2u handle, LTEngine_u32 x);
void LTENGINE_API LTEngine_Vec2u_setY(LTEngine_HVec2u handle, LTEngine_u32 y);

#ifdef __cplusplus
}
#endif
#endif
