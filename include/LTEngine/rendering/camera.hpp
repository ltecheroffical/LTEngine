#pragma once

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Rendering {
    struct Camera {
        Math::Vec2 position;
        Math::Vec2 zoom;
        f32 rotation;

        bool exclude:1;
        bool in_use:1;
    };
}
