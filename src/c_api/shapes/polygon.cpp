#include <LTEngine/c_api/shapes/polygon.h>

#include <LTEngine/shapes/polygon.hpp>

LTENGINE_DEFINE_DYNAMIC_ARRAY_LOGIC(LTEngine_HVec2, Vec2);


LTEngine_HPolygon LTEngine_Polygon() {
    return {{ new LTEngine::Shapes::Polygon() }};
}

void LTEngine_Polygon_free(LTEngine_HPolygon handle) {
    delete (LTEngine::Shapes::Polygon*)handle.handle.ptr;
}


LTEngine_DynamicArray_Vec2 LTEngine_Polygon_getPoints(const LTEngine_HPolygon handle) {
    auto array = LTEngine_DynamicArray_Vec2_createWithCapacity(((LTEngine::Shapes::Polygon*)handle.handle.ptr)->points.size());

    for (auto vec2 : ((LTEngine::Shapes::Polygon*)handle.handle.ptr)->points) {
        LTEngine_DynamicArray_Vec2_add(&array, LTEngine_Vec2(vec2.x, vec2.y));
    } 

    return array;
}