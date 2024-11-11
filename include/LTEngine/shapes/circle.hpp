#pragma once

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
    struct Circle : public Shape {
        float radius;
    };
}
