#ifndef _LTENGINE_SHAPE_TORUS_HPP_
#define _LTENGINE_SHAPE_TORUS_HPP_

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Torus : public Shape {
        f32 innerRadius;
        f32 tubeRadius;
    };
}

#endif // _LTENGINE_SHAPE_TORUS_HPP_