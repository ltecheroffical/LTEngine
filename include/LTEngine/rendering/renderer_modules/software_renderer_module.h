#pragma once

#include <LTEngine/rendering/renderer.h>


typedef struct {
    ltrenderer_module_t module;

    u32 _width, _height;

    struct {
        ltcolora_t *data;
        u32 width, height;
    } _buffer;

    ltcolor_t *_screen;
    u16 *_z_buffer;

    u16 _z_order;
} ltrenderer_software_module_t;


ltrenderer_software_module_t ltrenderer_software_module_new(u32 width, u32 height);

u32 ltrenderer_software_module_get_pixels(const ltrenderer_software_module_t *module, ltcolor_t *screen);
