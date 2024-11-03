#pragma once

#include <vector>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    class ltimage_t {
    public:
        ltimage_t(u32 width, u32 height);
        ltimage_t(const ltcolor_t *buffer, u32 width, u32 height);
        ltimage_t(const ltcolora_t *buffer, u32 width, u32 height);
        ~ltimage_t();

        void resize(u32 width, u32 height);

        void set_size(u32 width, u32 height);
        Math::ltvec2u_t get_size() const;

        void set_pixel(ltcolora_t color, u32 x, u32 y);
        ltcolora_t get_pixel(u32 x, u32 y) const;

        void flip_h(), flip_v();

    private:
        u32 _width, _height;

        std::vector<ltcolora_t> _data;
    };
}
