#pragma once

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Shapes {
    struct Shape {
        f32 x = 0.f, y = 0.f;
        f32 rotation = 0.f;

        Shape() = default;
        Shape(f32 x, f32 y) : x(x), y(y) {}
        Shape(f32 x, f32 y, f32 rotation) : x(x), y(y), rotation(rotation) {}
    };

    struct Shapei {
        i32 x = 0, y = 0;
        i16 rotation = 0;

        Shapei() = default;
        Shapei(i32 x, i32 y) : x(x), y(y) {}
        Shapei(i32 x, i32 y, i16 rotation) : x(x), y(y), rotation(rotation) {}
    };
}
