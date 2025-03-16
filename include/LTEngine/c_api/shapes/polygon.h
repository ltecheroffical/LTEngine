#ifndef _LTENGINE_C_API_POLYGON_H_
#define _LTENGINE_C_API_POLYGON_H_

#include <LTEngine/c_api/math/vec2.h>
#include <LTEngine/c_api/common/ctypes.h>
#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/c_api/shapes/shape.h>
#include <LTEngine/c_api/list/dynamic_array.h>

#ifdef __cplusplus
extern "C" {
#endif

LTENGINE_DEFINE_DYNAMIC_ARRAY(LTEngine_HVec2, Vec2);

typedef LTEngine_HShape LTEngine_HPolygon;

LTEngine_HPolygon LTENGINE_API LTEngine_Polygon();
void LTENGINE_API LTEngine_Polygon_free(LTEngine_HPolygon handle);

LTEngine_DynamicArray_Vec2 LTEngine_Polygon_getPoints(const LTEngine_HPolygon handle);

void LTENGINE_API LTEngine_Polygon_setPoints(LTEngine_HPolygon handle, const LTEngine_DynamicArray_Vec2 points);

#ifdef __cplusplus
}
#endif
#endif