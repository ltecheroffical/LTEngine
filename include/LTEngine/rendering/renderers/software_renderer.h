#pragma once

#include <LTEngine/rendering/renderer.h>


typedef struct {
    ltrenderer_t renderer;

    u32 _width, _height;

    struct {
        ltcolora_t *data;
        u32 width, height;
        u32 size;
        bool in_use:1;
    } _buffer;

    ltcolor_t *_screen;
    u16 *_z_buffer;
} ltrenderer_software_t;


ltrenderer_software_t ltrenderer_software_new(u32 width, u32 height);

u32 ltrenderer_software_get_pixels(const ltrenderer_software_t *renderer, ltcolor_t *screen);
