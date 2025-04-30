#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/shapes/circle.h>

#include <LTEngine/shapes/circle.hpp>


LTEngine_HCircle LTEngine_Circle(LTEngine_f32 x, LTEngine_f32 y, LTEngine_f32 radius) {
    auto circle=  new LTEngine::Shapes::Circle();
    circle->x = x;
    circle->y = y;
    return {{circle}};
}

void LTEngine_Circle_free(LTEngine_HCircle handle) {
    delete (LTEngine::Shapes::Circle*)handle.handle.ptr;
}


LTEngine_f32 LTEngine_Circle_radius(const LTEngine_HCircle handle) {
    return ((LTEngine::Shapes::Circle*)handle.handle.ptr)->radius;
}


void LTEngine_Circle_setRadius(LTEngine_HCircle handle, LTEngine_f32 radius) {
    ((LTEngine::Shapes::Circle*)handle.handle.ptr)->radius = radius;
}

#endif