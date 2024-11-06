#pragma once

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    struct CPUShaderIO {
        Math::Vec2i position;
        ColorA color;

        const Color *screen;
        const Math::Vec2u screenSize;
        
        const ColorA *texture;
        const u32 textureWidth;
        const u32 textureHeight;
        const u32 textureX;
        const u32 textureY;

        
        Color getScreenColor(u32 x, u32 y) const {
            if (x < 0 || x >= screenSize.x || y < 0 || y >= screenSize.y) {
                return Color::BLACK;
            }
            return screen[y * screenSize.x + x];
        }

        ColorA getTextureColor(u32 x, u32 y) const {
            if (x < 0 || x >= textureWidth || y < 0 || y >= textureHeight) {
                return ColorA::CLEAR;
            }
            return texture[y * textureWidth + x];
        }
    };

    class CPUShader {
    public:
        virtual ~CPUShader() = 0;

        virtual void fragment(CPUShaderIO *io) = 0;
    };
}
