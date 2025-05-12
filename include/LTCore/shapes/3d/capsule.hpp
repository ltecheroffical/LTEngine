#ifndef _LTCORE_SHAPE_CAPSULE_HPP_
#define _LTCORE_SHAPE_CAPSULE_HPP_

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Capsule : public Shape {
        f32 radius;
        f32 height;
    };
}

#endif // _LTCORE_SHAPE_CAPSULE_HPP_