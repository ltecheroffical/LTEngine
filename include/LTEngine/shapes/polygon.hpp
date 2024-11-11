#pragma once

#include <vector>

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Shapes {
    struct Polygon {
        std::vector<Math::Vec2> points;
    };
}
