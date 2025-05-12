#ifndef _LTCORE_SHAPE_TORUS_HPP_
#define _LTCORE_SHAPE_TORUS_HPP_

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Torus : public Shape {
        f32 innerRadius;
        f32 tubeRadius;
    };
}

#endif // _LTCORE_SHAPE_TORUS_HPP_