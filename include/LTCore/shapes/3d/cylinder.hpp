#ifndef _LTCORE_SHAPE_CYLINDER_HPP_
#define _LTCORE_SHAPE_CYLINDER_HPP_

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Cylinder : public Shape {
        f32 radius;
        f32 height;
    };
}

#endif // _LTCORE_SHAPE_CYLINDER_HPP_