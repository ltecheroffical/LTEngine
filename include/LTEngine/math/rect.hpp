#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Math {
    typedef struct ltrect_t {
        f32 x, y;
        u32 w, h;

        ltrect_t(f32 x, f32 y, u32 w, u32 h) : x(x), y(y), w(w), h(h) {}
        ltrect_t(ltvec2_t pos, ltvec2u_t size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    } ltrect_t;

    typedef struct ltrecti_t {
        i32 x, y;
        u32 w, h;

        ltrecti_t(i32 x, i32 y, u32 w, u32 h) : x(x), y(y), w(w), h(h) {}
        ltrecti_t(ltvec2i_t pos, ltvec2u_t size) : x(pos.x), y(pos.y), w(size.x), h(size.y) {}
    } ltrecti_t;
}
