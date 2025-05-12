#ifndef _LTCORE_C_API_VEC2_H_
#ifdef LTCORE_COMPONENT_C_API
#define _LTCORE_C_API_VEC2_H_

#include <LTCore/c_api/common/ctypes.h>
#include <LTCore/common/compiler_utils.h>


typedef struct {
    LTCore_HANDLE handle;
} LTCore_HVec2;
typedef struct {
    LTCore_HANDLE handle;
} LTCore_HVec2i;
typedef struct {
    LTCore_HANDLE handle;
} LTCore_HVec2u;


#ifdef __cplusplus
extern "C" {
#endif

LTCore_HVec2 LTCORE_API LTCore_Vec2(LTCore_f32 x, LTCore_f32 y);
void LTCORE_API LTCore_Vec2_free(LTCore_HVec2 handle);

LTCore_f32 LTCORE_API LTCore_Vec2_x(const LTCore_HVec2 handle);
LTCore_f32 LTCORE_API LTCore_Vec2_y(const LTCore_HVec2 handle);

void LTCORE_API LTCore_Vec2_setX(LTCore_HVec2 handle, LTCore_f32 x);
void LTCORE_API LTCore_Vec2_setY(LTCore_HVec2 handle, LTCore_f32 y);

LTCore_HVec2 LTCORE_API LTCore_Vec2_normalize(LTCore_HVec2 handle);
LTCore_f32 LTCORE_API LTCore_Vec2_distance(LTCore_HVec2 handle1, LTCore_HVec2 handle2);


LTCore_HVec2i LTCORE_API LTCore_Vec2i(LTCore_i32 x, LTCore_i32 y);
void LTCORE_API LTCore_Vec2i_free(LTCore_HVec2i handle);

LTCore_i32 LTCORE_API LTCore_Vec2i_x(const LTCore_HVec2i handle);
LTCore_i32 LTCORE_API LTCore_Vec2i_y(const LTCore_HVec2i handle);

void LTCORE_API LTCore_Vec2i_setX(LTCore_HVec2i handle, LTCore_i32 x);
void LTCORE_API LTCore_Vec2i_setY(LTCore_HVec2i handle, LTCore_i32 y);

LTCore_HVec2i LTCORE_API LTCore_Vec2i_normalize(const LTCore_HVec2i handle);
LTCore_f32 LTCORE_API LTCore_Vec2i_distance(const LTCore_HVec2i handle1, const LTCore_HVec2i handle2);


LTCore_HVec2u LTCORE_API LTCore_Vec2u(LTCore_u32 x, LTCore_u32 y);
void LTCORE_API LTCore_Vec2u_free(LTCore_HVec2u handle);

LTCore_u32 LTCORE_API LTCore_Vec2u_x(const LTCore_HVec2u handle);
LTCore_u32 LTCORE_API LTCore_Vec2u_y(const LTCore_HVec2u handle);

void LTCORE_API LTCore_Vec2u_setX(LTCore_HVec2u handle, LTCore_u32 x);
void LTCORE_API LTCore_Vec2u_setY(LTCore_HVec2u handle, LTCore_u32 y);

#ifdef __cplusplus
}
#endif
#endif
#endif
