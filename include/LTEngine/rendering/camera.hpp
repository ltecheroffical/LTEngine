#pragma once

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    struct Camera {
        Math::Vec2 position = Math::Vec2::ZERO;
        Math::Vec2 zoom = Math::Vec2::ONE;
        f32 rotation = 0.f;

        bool exclude:1;
        
        u32 id;
    };
}
