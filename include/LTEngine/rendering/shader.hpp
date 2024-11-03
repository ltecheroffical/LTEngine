#pragma once

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/math/vec2.h>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
    typedef struct {
        ltvec2_t position;
        ltcolora_t color;

        ltvec2u_t screen_size;
        const ltcolor_t *screen;
        
        u32 texture_width;
        u32 texture_height;
        const ltcolora_t *texture;
    } ltshader_cpu_data_t;

    class ltshader_cpu_t {
    public:
        virtual ~ltshader_cpu_t() = 0;

        virtual void fragment(ltshader_cpu_data_t *params) = 0;
    };
}
