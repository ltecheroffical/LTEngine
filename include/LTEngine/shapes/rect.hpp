#pragma once

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
    struct Rect : public Shape {
        u32 w, h;

        Rect(f32 x, f32 y, u32 w, u32 h) : Shape(x, y), w(w), h(h) {}
        Rect(Math::Vec2 pos, Math::Vec2u size) : Shape(pos.x, pos.y), w(size.x), h(size.y) {}
    };

    struct Recti : public Shapei {
        u32 w, h;

        Recti(i32 x, i32 y, u32 w, u32 h) : Shapei(x, y), w(w), h(h) {}
        Recti(Math::Vec2i pos, Math::Vec2u size) : Shapei(pos.x, pos.y), w(size.x), h(size.y) {}
    };
}
