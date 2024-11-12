#pragma once

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
    struct Triangle : public Shape {
        Math::Vec2 p1;
        Math::Vec2 p2;
        Math::Vec2 p3;
    };
}
