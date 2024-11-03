#pragma once

#include <vector>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    class Image {
    public:
        Image(u32 width, u32 height);
        Image(const Color *buffer, u32 width, u32 height);
        Image(const ColorA *buffer, u32 width, u32 height);
        ~Image();

        void resize(u32 width, u32 height);

        void setSize(u32 width, u32 height);
        Math::Vec2u getSize() const;

        void setPixel(ColorA color, u32 x, u32 y);
        ColorA getPixel(u32 x, u32 y) const;

        void flipH(), flipV();

    private:
        u32 m_width, m_height;

        std::vector<ColorA> m_data;
    };
}
