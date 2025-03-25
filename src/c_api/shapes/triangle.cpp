#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/shapes/triangle.h>

#include <LTEngine/shapes/triangle.hpp>


LTEngine_HTriangle LTEngine_Triangle(const LTEngine_HVec2 p1, const LTEngine_HVec2 p2, const LTEngine_HVec2 p3) {
    auto shape = new LTEngine::Shapes::Triangle();
    shape->p1 = {LTEngine_Vec2_x(p1), LTEngine_Vec2_y(p1)};
    shape->p2 = {LTEngine_Vec2_x(p2), LTEngine_Vec2_y(p2)};
    shape->p3 = {LTEngine_Vec2_x(p3), LTEngine_Vec2_y(p3)};
    return {{ shape }};
}

void LTEngine_Triangle_free(LTEngine_HTriangle handle) {
    delete ((LTEngine::Shapes::Triangle*)handle.handle.ptr);
}


LTEngine_HVec2 LTEngine_Triangle_p1(const LTEngine_HTriangle handle) {
    return LTEngine_Vec2(((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p1.x, ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p1.y);
}

LTEngine_HVec2 LTEngine_Triangle_p2(const LTEngine_HTriangle handle) {
    return LTEngine_Vec2(((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p2.x, ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p2.y);
}

LTEngine_HVec2 LTEngine_Triangle_p3(const LTEngine_HTriangle handle) {
    return LTEngine_Vec2(((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p3.x, ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p3.y);
}


void LTEngine_Triangle_setP1(const LTEngine_HTriangle handle, LTEngine_HVec2 value) {
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p1.x = LTEngine_Vec2_x(value);
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p1.y = LTEngine_Vec2_y(value);
}

void LTEngine_Triangle_setP2(const LTEngine_HTriangle handle, LTEngine_HVec2 value) {
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p2.x = LTEngine_Vec2_x(value);
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p2.y = LTEngine_Vec2_y(value);
}

void LTEngine_Triangle_setP3(const LTEngine_HTriangle handle, LTEngine_HVec2 value) {
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p3.x = LTEngine_Vec2_x(value);
    ((LTEngine::Shapes::Triangle*)handle.handle.ptr)->p3.y = LTEngine_Vec2_y(value);
}

#endif