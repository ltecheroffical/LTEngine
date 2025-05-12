#ifndef _LTCORE_SHAPE_SPHERE_HPP_
#define _LTCORE_SHAPE_SPHERE_HPP_

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Sphere : public Shape {
        f32 radius;
    };
}

#endif // _LTCORE_SHAPE_SPHERE_HPP_