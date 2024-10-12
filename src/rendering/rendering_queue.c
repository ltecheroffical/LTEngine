#include <stdlib.h>

#include "buffer_utils.h"
#include "rendering_internal.h"


struct ltrenderer_op_t *ltrenderer_add_op(ltrenderer_t *renderer) {
    for (u32 i = 0; i < renderer->_op_queue.capicity; i++) {
        if (!renderer->_op_queue.operations[i].flags.active) {
            renderer->_op_queue.operations[i].flags.active = true;
            renderer->_op_queue.operations[i].flags.locked = true;
            renderer->_op_queue.operations[i].order = ++renderer->_op_queue.last_order;
            renderer->_op_queue.op_count++;
            return &renderer->_op_queue.operations[i];
        }
    }
    
    struct ltrenderer_op_t *ops = (struct ltrenderer_op_t*)realloc(renderer->_op_queue.operations, sizeof(struct ltrenderer_op_t) * (renderer->_op_queue.capicity * 2));
    u32 prev_capicity = renderer->_op_queue.capicity;
    renderer->_op_queue.capicity *= 2;
    
    for (u32 op = prev_capicity; op < renderer->_op_queue.capicity; op++) {
        ops[op].flags.active = false;
    }

    ops[prev_capicity].flags.active = true;
    ops[prev_capicity].flags.locked = true;
    ops[prev_capicity].order = ++renderer->_op_queue.last_order;

    renderer->_op_queue.operations = ops;
    renderer->_op_queue.op_count++;

    return &renderer->_op_queue.operations[prev_capicity];
}


bool ltrenderer_process(ltrenderer_t *renderer) {
    if (renderer->_op_queue.op_count <= 0) {
        renderer->_op_queue.current = 0;
        renderer->_op_queue.current_order = 1;
        renderer->_op_queue.last_order = 0;
        return false;
    }

    struct ltrenderer_op_t *ops = renderer->_op_queue.operations;
    while (!ops[renderer->_op_queue.current].flags.active && renderer->_op_queue.current_order >= ops[renderer->_op_queue.current].order) {
        if (renderer->_op_queue.current >= renderer->_op_queue.capicity) {
            renderer->_op_queue.current = 0;
        }
        renderer->_op_queue.current++;
    }
    renderer->_op_queue.current_order++;

    struct ltrenderer_op_t *op = &ops[renderer->_op_queue.current];

    switch (op->op) {
        case LTRENDERER_OP_SET_PARAM:
            switch (op->op_set_param.param) {
                case LTRENDERER_OP_PARAM_SCREEN_ONLY:
                    renderer->_flags.renderer.screen_only = op->op_set_param.screen_only;
                    break;
                default:
                    break;
            }
            break;
        case LTRENDERER_OP_UPDATE_CAM:
            switch (op->op_update_cam.param) {
                case LTRENDERER_OP_CAM_PARAM_POSITION:
                    renderer->_cams.cams[op->op_update_cam.id].x = op->op_update_cam.position.x;
                    renderer->_cams.cams[op->op_update_cam.id].y = op->op_update_cam.position.y;
                    break;
                case LTRENDERER_OP_CAM_PARAM_ZOOM:
                    renderer->_cams.cams[op->op_update_cam.id].zoom = op->op_update_cam.zoom;
                    break;
                case LTRENDERER_OP_CAM_PARAM_EXCLUSION:
                    renderer->_cams.cams[op->op_update_cam.id].exclude = op->op_update_cam.exculde;
                default:
                    break;
            }
            break;

        case LTRENDERER_OP_SET_PIXEL:
            if (!renderer->_flags.renderer.screen_only) {
                for (u32 cam = 0; cam < renderer->_cams.size; cam++) {
                    if (!renderer->_cams.cams[cam].in_use || renderer->_cams.cams[cam].exclude) continue;

                    transfer_pixela_to_buffer(renderer->_cams.cams[cam].pixels,
                                              op->op_set_pixel.color,
                                              ltvec2i_new(op->op_set_pixel.pos.x, op->op_set_pixel.pos.y),
                                              renderer->_width, renderer->_height);
                }
            } else {
                transfer_pixela_to_buffer(renderer->_software.pixels,
                                          op->op_set_pixel.color,
                                          ltvec2i_new(op->op_set_pixel.pos.x, op->op_set_pixel.pos.y),
                                          renderer->_width, renderer->_height);
            }
            break;

        case LTRENDERER_OP_RENDER_CLEAR:
            if (!renderer->_flags.renderer.screen_only) {
                for (u32 cam = 0; cam < renderer->_cams.size; cam++) {
                    if (!renderer->_cams.cams[cam].in_use || renderer->_cams.cams[cam].exclude) continue;

                    for (u32 i = 0; i < renderer->_width * renderer->_height; i++) {
                        ltcolor_t bg = renderer->_cams.cams[cam].pixels[i];
                        f32 A_n = op->op_clear.clear_color.a / 255.0f;

                        renderer->_cams.cams[cam].pixels[i] = ltcolor_add(
                                                                    ltcolor_mulf(ltcolor_fromA(op->op_clear.clear_color), A_n),
                                                                    ltcolor_mulf(bg, (1 - A_n)));
                    }
                }
            } else {
                for (u32 i = 0; i < renderer->_width * renderer->_height; i++) {
                    ltcolor_t bg = renderer->_software.pixels[i];
                    f32 A_n = op->op_clear.clear_color.a / 255.0f;

                    renderer->_software.pixels[i] = ltcolor_add(
                                                        ltcolor_mulf(ltcolor_fromA(op->op_clear.clear_color), A_n),
                                                        ltcolor_mulf(bg, (1 - A_n)));
                }
            }
            break;
        
        case LTRENDERER_OP_RENDER_CAM: {
            ltrenderer_camera_t *camera = &renderer->_cams.cams[op->op_render_camera.id];
            

            ltrenderer_prepare_buffer(renderer, op->op_render_camera.size.x, op->op_render_camera.size.y);

            for (u32 y = 0; y < op->op_render_camera.size.y; y++) {
                for (u32 x = 0; x < op->op_render_camera.size.x; x++) {
                    ltrenderer_set_buffer_pixel(renderer, x, y, ltcolora_from(camera->pixels[y * renderer->_width + x]));
                }
            }

            ltrenderer_transfer_buffer_to_screen(renderer, op->op_render_camera.position.x, op->op_render_camera.position.y);
        }
        case LTRENDERER_OP_RENDER_SQUARE:
            ltrenderer_prepare_buffer(renderer, op->op_render_square.rect.w, op->op_render_square.rect.h);

            for (u32 y = 0; y < op->op_render_square.rect.h; y++) {
                for (u32 x = 0; x < op->op_render_square.rect.w; x++) {
                    ltrenderer_set_buffer_pixel(renderer, x, y, op->op_render_square.color);
                }
            }

            ltrenderer_transfer_buffer_to_screen(renderer, op->op_render_square.rect.x,
                                                           op->op_render_square.rect.y);
            break;
        case LTRENDERER_OP_RENDER_SPRITE:
            ltrenderer_prepare_buffer(renderer, op->op_render_sprite.region.w, op->op_render_sprite.region.h);

            for (u32 x = 0; x < op->op_render_sprite.region.w; x++) {
                for (u32 y = 0; y < op->op_render_sprite.region.h; y++) {
                    ltrenderer_set_buffer_pixel(renderer, x, y, 
                                                ltcolora_mix(op->op_render_sprite.color, 
                                                             lttexture_cpu_get_pixel(
                                                                op->op_render_sprite.texture, x, y)));
                }
            }
            ltrenderer_transfer_buffer_to_screen(renderer, op->op_render_sprite.pos.x, op->op_render_sprite.pos.y);
            break;
        default:
            break;
    }

    op->flags.active = false;
    renderer->_op_queue.op_count--;
    return true;
}


// General
void ltrenderer_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_SET_PIXEL;
    op->op_set_pixel.pos = position;
    op->op_set_pixel.color = color;

    op->flags.locked = false;
}


// Shapes
void ltrenderer_draw_rect(ltrenderer_t *renderer, ltrect_t rect, ltcolora_t color) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_RENDER_SQUARE;
    op->op_render_square.rect = (ltrecti_t){rect.x, rect.y, rect.w, rect.h};
    op->op_render_square.color = color;

    op->flags.locked = false;
}


// Textures
void ltrenderer_draw_cpu_texture_region(ltrenderer_t *renderer, const lttexture_cpu_t *texture, ltvec2_t position, ltrecti_t region, ltcolora_t color) {
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_RENDER_SPRITE;
    op->op_render_sprite.pos = (ltvec2i_t){position.x, position.y};
    op->op_render_sprite.region = region;
    op->op_render_sprite.color = color;
    op->op_render_sprite.texture = texture;

    op->flags.locked = false;
}

void ltrenderer_draw_cpu_texture(ltrenderer_t *renderer, const lttexture_cpu_t *texture, ltvec2_t position, ltcolora_t color) {
    ltrenderer_draw_cpu_texture_region(renderer, texture, position, (ltrecti_t){ 0, 0, texture->_width, texture->_height }, color);
}


// Camera
void ltrenderer_draw_camera(ltrenderer_t *renderer, u32 id, ltvec2_t position, ltvec2u_t size) {
    if (renderer->_cams.size < id) {
        return;
    }

    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_RENDER_CAM;

    op->op_render_camera.id = id;
    op->op_render_camera.position = position;
    op->op_render_camera.size = size;

    op->flags.locked = false;
}

void ltrenderer_set_camera_position(ltrenderer_t *renderer, u32 index, ltvec2_t position) {
    if (renderer->_cams.size < index) {
        return;
    }
    
    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_UPDATE_CAM;
    
    op->op_update_cam.param = LTRENDERER_OP_CAM_PARAM_POSITION;
    op->op_update_cam.id = index;
    op->op_update_cam.position = position;
    
    op->flags.locked = false;

}

void ltrenderer_set_camera_zoom(ltrenderer_t *renderer, u32 index, ltvec2_t zoom) {
    if (renderer->_cams.size < index) {
        return;
    }

    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_UPDATE_CAM;

    op->op_update_cam.param = LTRENDERER_OP_CAM_PARAM_ZOOM;
    op->op_update_cam.id = index;
    op->op_update_cam.zoom = zoom;
    
    op->flags.locked = false;
}

void ltrenderer_exclude_camera(ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return;
    }

    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_UPDATE_CAM;
    
    op->op_update_cam.param = LTRENDERER_OP_CAM_PARAM_EXCLUSION;
    op->op_update_cam.id = id;
    op->op_update_cam.exculde = true;
    
    op->flags.locked = false;
}

void ltrenderer_include_camera(ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return;
    }

    struct ltrenderer_op_t *op = ltrenderer_add_op(renderer);

    op->op = LTRENDERER_OP_UPDATE_CAM;
    
    op->op_update_cam.param = LTRENDERER_OP_CAM_PARAM_EXCLUSION;
    op->op_update_cam.id = id;
    op->op_update_cam.exculde = false;
    
    op->flags.locked = false;
}

void ltrenderer_include_cameras(ltrenderer_t *renderer) {
    for (u32 i = 0; i < renderer->_cams.size; i++) {
        ltrenderer_include_camera(renderer, i);
    }
}
