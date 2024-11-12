#pragma once

#include <vector>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
    struct Polygon : public Shape {
        std::vector<Math::Vec2> points;
    };
}
