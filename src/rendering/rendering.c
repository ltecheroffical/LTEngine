#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <LTEngine/rendering/rendering.h>

#include "buffer_utils.h"
#include "rendering_internal.h"


ltrenderer_t ltrenderer_new(u32 width, u32 height) {
    ltrenderer_t renderer;

    renderer._width = width;
    renderer._height = height;

    renderer._scale = LTVEC2_ZERO;

    renderer._flags.renderer.unsafe = 0;
    renderer._flags.renderer.screen_only = 0;
    renderer._flags.renderer.flip_h = 0;
    renderer._flags.renderer.flip_v = 0;

    renderer._op_queue.capicity = 1;
    renderer._op_queue.op_count = 0;
    renderer._op_queue.current = 0;
    renderer._op_queue.last_order = 0;
    renderer._op_queue.current_order = 0;

    renderer._op_queue.operations = (struct ltrenderer_op_t*)calloc(1, sizeof(struct ltrenderer_op_t));

    renderer._software.pixels = (ltcolor_t*)calloc(width * height, sizeof(ltcolor_t));

    renderer._software.buffer.data = (ltcolora_t*)calloc(4 * 4, sizeof(ltcolora_t));
    renderer._software.buffer.size = 4 * 4 * sizeof(ltcolora_t);
    renderer._software.buffer.width = 1;
    renderer._software.buffer.height = 1;

    renderer._cams.size = 4;
    renderer._cams.cams = (ltrenderer_camera_t*)calloc(renderer._cams.size, sizeof(ltrenderer_camera_t));

    renderer._creation_time = clock(); 
    return renderer;
}

void ltrenderer_free(ltrenderer_t *renderer) {
    free(renderer->_software.pixels);
    free(renderer->_software.buffer.data);

    renderer->_software.pixels = NULL;
    renderer->_software.buffer.data = NULL;
}


void ltrenderer_set_unsafe(ltrenderer_t *renderer) {
    renderer->_flags.renderer.unsafe = 1;
}

void ltrenderer_clear_unsafe(ltrenderer_t *renderer) {
    renderer->_flags.renderer.unsafe = 0;
}


void ltrenderer_set_screen_only(ltrenderer_t *renderer) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_SET_PARAM;

    op->op_set_param.param = LTRENDERER_OP_PARAM_SCREEN_ONLY;
    op->op_set_param.screen_only = true;
}

void ltrenderer_clear_screen_only(ltrenderer_t *renderer) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_SET_PARAM;

    op->op_set_param.param = LTRENDERER_OP_PARAM_SCREEN_ONLY;
    op->op_set_param.screen_only = false;
}


ltvec2u_t ltrenderer_get_screen_size(const ltrenderer_t *renderer) {
    return ltvec2u_new(renderer->_width, renderer->_height);
}

u32 ltrenderer_get_buffer_size(const ltrenderer_t *renderer) {
    return renderer->_width * renderer->_height * sizeof(ltcolor_t);
}

void ltrenderer_get_screen_data(const ltrenderer_t *renderer, u8 *pixels) {
    memcpy(pixels, renderer->_software.pixels, ltrenderer_get_buffer_size(renderer));
}


bool ltrenderer_resize(ltrenderer_t *renderer, u32 width, u32 height) {
    ltcolor_t *pixels = realloc(renderer->_software.pixels, width * height * sizeof(ltcolor_t));

    if (pixels == NULL) {
        return false;
    }

    renderer->_width = width;
    renderer->_height = height;
    
    renderer->_software.pixels = pixels;
    
    for (u32 c = 0; c < renderer->_cams.size; c++) {
        if (!renderer->_cams.cams[c].in_use && !renderer->_cams.cams[c].exclude) continue;
        ltcolor_t *data = (ltcolor_t*)realloc(renderer->_cams.cams[c].pixels, width * height * sizeof(ltcolor_t));

        if (data == NULL) {
            return false;
        }
        
        renderer->_cams.cams[c].pixels = data;
    }
    return true;
}


void ltrenderer_clear(ltrenderer_t *renderer, ltcolora_t color) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);
    
    op->op = LTRENDERER_OP_RENDER_CLEAR;
    op->op_clear.clear_color = color;

    op->flags.locked = false;
}


ltcolor_t ltrenderer_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position) {
    return renderer->_software.pixels[(position.y * renderer->_width + position.x)];
}
