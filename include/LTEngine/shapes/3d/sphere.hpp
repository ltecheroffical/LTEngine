#ifndef _LTENGINE_SHAPE_SPHERE_HPP_
#define _LTENGINE_SHAPE_SPHERE_HPP_

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Sphere : public Shape {
        f32 radius;
    };
}

#endif // _LTENGINE_SHAPE_SPHERE_HPP_