#pragma once

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Rendering {
    typedef struct {
        Math::ltvec2_t position;
        Math::ltvec2_t zoom;
        f32 rotation;

        bool exclude:1;
        bool in_use:1;
    } ltcamera_t;
}
