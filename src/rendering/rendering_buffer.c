#include <stdlib.h>

#include "buffer_utils.h"
#include "rendering_internal.h"


void ltrenderer_set_buffer_pixel(ltrenderer_t *renderer, u32 x, u32 y, ltcolora_t color) {
    renderer->_software.buffer.data[(y * renderer->_software.buffer.width + x)] = color;
}

ltcolora_t ltrenderer_get_buffer_pixel(const ltrenderer_t *renderer, u32 x, u32 y) {
    return renderer->_software.buffer.data[(y * renderer->_software.buffer.width + x)];
}

void ltrenderer_prepare_buffer(ltrenderer_t *renderer, u32 width, u32 height) {
    if (renderer->_software.buffer.size < width * height * sizeof(ltcolora_t)) {
        ltcolora_t *buffer = realloc(renderer->_software.buffer.data, width * height * sizeof(ltcolora_t));
        if (buffer == NULL) {
            return;
        }
        
        renderer->_software.buffer.data = buffer;
        renderer->_software.buffer.size = width * height * sizeof(ltcolora_t);
    }

    renderer->_software.buffer.width = width;
    renderer->_software.buffer.height = height;
}

void ltrenderer_transfer_buffer_to_screen(ltrenderer_t *renderer, u32 x, u32 y) {
    for (u32 j = 0; j < renderer->_software.buffer.height; j++) {
        for (u32 i = 0; i < renderer->_software.buffer.width; i++) {
            if (!renderer->_flags.renderer.screen_only) {
                for (u32 c = 0; c < renderer->_cams.size; c++) {
                    if (!renderer->_cams.cams[c].in_use || renderer->_cams.cams[c].exclude) continue;
                    if (((x + i - renderer->_cams.cams[c].x) < 0 || (x + i - renderer->_cams.cams[c].x) >= renderer->_width || (y + j - renderer->_cams.cams[c].y) < 0 || (y + j - renderer->_cams.cams[c].y) >= renderer->_height) && !renderer->_flags.renderer.unsafe) continue;

                    transfer_pixela_to_buffer(renderer->_cams.cams[c].pixels,
                                              ltrenderer_get_buffer_pixel(renderer, i, j),
                                              ltvec2i_new(x + i - renderer->_cams.cams[c].x, y + j - renderer->_cams.cams[c].y),
                                              renderer->_width, renderer->_height);
                }
                continue;
            }
            if (((x + i) < 0 || (x + i) >= renderer->_width || (y + j) < 0 || (y + j) >= renderer->_height) && !renderer->_flags.renderer.unsafe) continue;
            transfer_pixela_to_buffer(renderer->_software.pixels,
                                      ltrenderer_get_buffer_pixel(renderer, i, j),
                                      ltvec2i_new(x + i, y + j), renderer->_width, renderer->_height);
        }
    }
}
