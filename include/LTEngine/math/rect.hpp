#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Math {
    struct Rect {
        f32 x, y;
        u32 w, h;

        Rect(f32 x, f32 y, u32 w, u32 h) : x(x), y(y), w(w), h(h) {}
        Rect(Vec2 pos, Vec2u size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    };

    struct Recti {
        i32 x, y;
        u32 w, h;

        Recti(i32 x, i32 y, u32 w, u32 h) : x(x), y(y), w(w), h(h) {}
        Recti(Vec2i pos, Vec2u size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    };
}
