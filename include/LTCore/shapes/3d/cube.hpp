#ifndef _LTCORE_SHAPE_CUBE_HPP_
#define _LTCORE_SHAPE_CUBE_HPP_

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Cube : public Shape {
        f32 w, h, l;
    };
}

#endif // _LTCORE_SHAPE_CUBE_HPP_