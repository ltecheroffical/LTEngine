#ifndef _LTENGINE_C_API_SHAPE_H_
#define _LTENGINE_C_API_SHAPE_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HShape;
typedef struct {
    LTEngine_HANDLE handle;
} LTEngine_HShapei;

LTEngine_f32 LTENGINE_API LTEngine_Shape_x(const LTEngine_HShape handle);
LTEngine_f32 LTENGINE_API LTEngine_Shape_y(const LTEngine_HShape handle);
LTEngine_f32 LTENGINE_API LTEngine_Shape_rotation(const LTEngine_HShape handle);

void LTENGINE_API LTEngine_Shape_setX(LTEngine_HShape handle, LTEngine_f32 x);
void LTENGINE_API LTEngine_Shape_setY(LTEngine_HShape handle, LTEngine_f32 y);
void LTENGINE_API LTEngine_Shape_setRotation(LTEngine_HShape handle, LTEngine_i32 rotation);


LTEngine_i32 LTENGINE_API LTEngine_Shapei_x(const LTEngine_HShapei handle);
LTEngine_i32 LTENGINE_API LTEngine_Shapei_y(const LTEngine_HShapei handle);
LTEngine_i16 LTENGINE_API LTEngine_Shapei_rotation(const LTEngine_HShapei handle);

void LTENGINE_API LTEngine_Shapei_setX(LTEngine_HShapei handle, LTEngine_i32 x);
void LTENGINE_API LTEngine_Shapei_setY(LTEngine_HShapei handle, LTEngine_i32 y);
void LTENGINE_API LTEngine_Shapei_setRotation(LTEngine_HShapei handle, LTEngine_i16 rotation);

#ifdef __cplusplus
}
#endif
#endif