#pragma once

#include <LTEngine/rendering/rendering.h>


struct ltrenderer_op_t *ltrenderer_add_op(ltrenderer_t *renderer);

void ltrenderer_set_buffer_pixel(ltrenderer_t *renderer, u32 x, u32 y, ltcolora_t color);
ltcolora_t ltrenderer_get_buffer_pixel(const ltrenderer_t *renderer, u32 x, u32 y);
void ltrenderer_prepare_buffer(ltrenderer_t *renderer, u32 width, u32 height);
void ltrenderer_transfer_buffer_to_screen(ltrenderer_t *renderer, u32 x, u32 y);
