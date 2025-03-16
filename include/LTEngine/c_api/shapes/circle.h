#ifndef _LTENGINE_C_API_CIRCLE_H_
#define _LTENGINE_C_API_CIRCLE_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/c_api/shapes/shape.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef LTEngine_HShape LTEngine_HCircle;

LTEngine_HCircle LTENGINE_API LTEngine_Circle(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 radius);
void LTENGINE_API LTEngine_Circle_free(LTEngine_HCircle handle);

LTEngine_f32 LTENGINE_API LTEngine_Circle_radius(const LTEngine_HCircle handle);

void LTENGINE_API LTEngine_Circle_setRadius(LTEngine_HCircle handle, LTEngine_f32 radius);

#ifdef __cplusplus
}
#endif
#endif