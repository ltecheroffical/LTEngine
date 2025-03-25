#ifndef _LTENGINE_C_API_TRIANGLE_H_I
#ifdef LTENGINE_COMPONENT_C_API
#define _LTENGINE_C_API_TRIANGLE_H_

#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/c_api/math/vec2.h>
#include <LTEngine/c_api/shapes/shape.h>


typedef LTEngine_HShape LTEngine_HTriangle;


#ifdef __cplusplus
extern "C" {
#endif

LTEngine_HTriangle LTEngine_Triangle(const LTEngine_HVec2 p1, const LTEngine_HVec2 p, const LTEngine_HVec2 p3);
void LTEngine_Triangle_free(LTEngine_HTriangle handle);

LTEngine_HVec2 LTEngine_Triangle_p1(const LTEngine_HTriangle handle);
LTEngine_HVec2 LTEngine_Triangle_p2(const LTEngine_HTriangle handle);
LTEngine_HVec2 LTEngine_Triangle_p3(const LTEngine_HTriangle handle);

void LTEngine_Triangle_setP1(const LTEngine_HTriangle handle, const LTEngine_HVec2 value);
void LTEngine_Triangle_setP2(const LTEngine_HTriangle handle, const LTEngine_HVec2 value);
void LTEngine_Triangle_setP3(const LTEngine_HTriangle handle, const LTEngine_HVec2 value);

#ifdef __cplusplus
}
#endif
#endif
#endif