#ifndef _LTENGINE_SHAPE_CYLINDER_HPP_
#define _LTENGINE_SHAPE_CYLINDER_HPP_

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Cylinder : public Shape {
        f32 radius;
        f32 height;
    };
}

#endif // _LTENGINE_SHAPE_CYLINDER_HPP_