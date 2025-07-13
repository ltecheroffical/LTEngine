#ifndef _LTENGINE_SHAPE_CUBE_HPP_
#define _LTENGINE_SHAPE_CUBE_HPP_

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Cube : public Shape {
        f32 w, h, l;
    };
}

#endif // _LTENGINE_SHAPE_CUBE_HPP_