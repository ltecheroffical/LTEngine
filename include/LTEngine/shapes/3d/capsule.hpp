#ifndef _LTENGINE_SHAPE_CAPSULE_HPP_
#define _LTENGINE_SHAPE_CAPSULE_HPP_

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Capsule : public Shape {
        f32 radius;
        f32 height;
    };
}

#endif // _LTENGINE_SHAPE_CAPSULE_HPP_