#pragma once

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    struct CPUShaderData {
        Math::Vec2 position;
        ColorA color;

        Math::Vec2u screenSize;
        const Color *screen;
        
        u32 textureWidth;
        u32 textureHeight;
        const ColorA *texture;
    };

    class CPUShader {
    public:
        virtual ~CPUShader() = 0;

        virtual void fragment(CPUShaderData *params) = 0;
    };
}
