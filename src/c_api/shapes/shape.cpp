#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/shapes/shape.h>

#include <LTEngine/shapes/shape.hpp>


LTEngine_f32 LTEngine_Shape_x(const LTEngine_HShape handle) {
    return ((LTEngine::Shapes::Shape*)handle.handle.ptr)->x;
}

LTEngine_f32 LTEngine_Shape_y(const LTEngine_HShape handle) {
    return ((LTEngine::Shapes::Shape*)handle.handle.ptr)->y;
}

LTEngine_f32 LTEngine_Shape_rotation(const LTEngine_HShape handle) {
    return ((LTEngine::Shapes::Shape*)handle.handle.ptr)->rotation;
}


void LTEngine_Shape_setX(LTEngine_HShape handle, LTEngine_f32 x) {
    ((LTEngine::Shapes::Shape*)handle.handle.ptr)->x = x;
}

void LTEngine_Shape_setY(LTEngine_HShape handle, LTEngine_f32 y) {
    ((LTEngine::Shapes::Shape*)handle.handle.ptr)->y = y;
}

void LTEngine_Shape_setRotation(LTEngine_HShape handle, LTEngine_f32 rotation) {
    ((LTEngine::Shapes::Shape*)handle.handle.ptr)->rotation = rotation;
}


LTEngine_i32 LTEngine_Shapei_x(const LTEngine_HShapei handle) {
    return ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->x;
}

LTEngine_i32 LTEngine_Shapei_y(const LTEngine_HShapei handle) {
    return ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->y;
}

LTEngine_i16 LTEngine_Shapei_rotation(const LTEngine_HShapei handle) {
    return ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->rotation;
}


void LTEngine_Shapei_setX(LTEngine_HShapei handle, LTEngine_i32 x) {
    ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->x = x;
}

void LTEngine_Shapei_setY(LTEngine_HShapei handle, LTEngine_i32 y) {
    ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->y = y;
}

void LTEngine_Shapei_setRotation(LTEngine_HShapei handle, LTEngine_i16 rotation) {
    ((LTEngine::Shapes::Shapei*)handle.handle.ptr)->rotation = rotation;
}

#endif