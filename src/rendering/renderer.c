#include <stdlib.h>

#include <LTEngine/rendering/renderer.h>


ltrenderer_t ltrenderer_new(ltrenderer_module_t *module) {
    ltrenderer_t renderer;
  
    renderer._module = module;

    renderer._cams.size = 8;
    renderer._cams.cams = (ltrenderer_camera_t*)calloc(sizeof(ltrenderer_camera_t), renderer._cams.size);

    renderer._rotation = 0.f;
    renderer._scale = LTVEC2_ONE;

    renderer._pos_offset = LTVEC2_ZERO;
    renderer._scale_offset = LTVEC2_ZERO;
    renderer._rotation_offset = 0.f;

    renderer._z_order = 0;

    return renderer;
}

void ltrenderer_free(ltrenderer_t *renderer) {
    free(renderer->_cams.cams);

    renderer->_module->free(renderer->_module);
}


void ltrenderer_set_scale(ltrenderer_t *renderer, ltvec2_t scale) {
    renderer->_scale = scale;
}

void ltrenderer_set_rotation(ltrenderer_t *renderer, float rotation) {
    renderer->_rotation = rotation;
}


void ltrenderer_set_position_offset(ltrenderer_t *renderer, ltvec2_t offset) {
    renderer->_pos_offset = offset;
}

void ltrenderer_set_scale_offset(ltrenderer_t *renderer, ltvec2_t offset) {
    renderer->_scale_offset = offset;
}

void ltrenderer_set_rotation_offset(ltrenderer_t *renderer, float offset) {
    renderer->_rotation_offset = offset;
}


void ltrenderer_set_z_order(ltrenderer_t *renderer, u16 z) {
    renderer->_z_order = z;
}


void ltrenderer_set_iris(ltrenderer_t *renderer) {
    if (renderer->_module->set_iris_mode == NULL) {
        return;
    }
    renderer->_module->set_iris_mode(renderer->_module);
}

void ltrenderer_clear_iris_mode(ltrenderer_t *renderer, ltcolora_t color) {
    if (renderer->_module->clear_iris_mode == NULL) {
        return;
    }
    renderer->_module->clear_iris_mode(renderer->_module, color);
}


ltresult_u32_t ltrenderer_create_camera(ltrenderer_t *renderer, ltvec2_t position, ltvec2_t zoom) {
    ltrenderer_camera_t *camera = NULL;
    u32 id = 0;

    for (u32 i = 0; i < renderer->_cams.size; i++) {
        if (!renderer->_cams.cams[i].in_use) {
            id = i;
            camera = &renderer->_cams.cams[i];
            break;
        }
    }

    if (camera == NULL) {
        ltrenderer_camera_t *new_cams = realloc(renderer->_cams.cams, renderer->_cams.size * sizeof(ltrenderer_camera_t) * 2);

        if (new_cams == NULL) {
            return ltresult_u32_new(LTRESULT_FATAL_ERR_MEMORY, 0);
        }

        id = renderer->_cams.size;
        camera = &renderer->_cams.cams[id];

        renderer->_cams.cams = new_cams;
        renderer->_cams.size *= 2;
    }

    camera->x = position.x;
    camera->y = position.y;
    camera->zoom = zoom;
    camera->exclude = false;
    camera->in_use = true;

    return ltresult_u32_new(LTRESULT_SUCCESS, id);
}

void ltrenderer_destroy_camera(ltrenderer_t *renderer, u32 index) {
    if (renderer->_cams.size < index) {
        return;
    }

    renderer->_cams.cams[index].in_use = false;
}

void ltrenderer_set_camera_position(ltrenderer_t *renderer, u32 index, ltvec2_t position) {
    if (renderer->_cams.size < index) {
        return;
    }
    renderer->_cams.cams[index].x = position.x;
    renderer->_cams.cams[index].y = position.y;
}

void ltrenderer_set_camera_zoom(ltrenderer_t *renderer, u32 id, ltvec2_t zoom) {
    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].zoom = zoom;
}

void ltrenderer_exclude_camera(ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].exclude = true;
}

void ltrenderer_include_camera(ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].exclude = false;
}

void ltrenderer_include_cameras(ltrenderer_t *renderer) {
    for (u32 i = 0; i < renderer->_cams.size; i++) {
        if (!renderer->_cams.cams[i].in_use) continue;
        ltrenderer_include_camera(renderer, i);
    }
}

ltvec2i_t ltrenderer_get_camera_position(const ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return LTVEC2I_ZERO;
    }
    return (ltvec2i_t){renderer->_cams.cams[id].x, renderer->_cams.cams[id].y};
}

ltvec2_t ltrenderer_get_camera_zoom(const ltrenderer_t *renderer, u32 id) {
    if (renderer->_cams.size < id) {
        return LTVEC2_ZERO;
    }
    return renderer->_cams.cams[id].zoom;
}


void ltrenderer_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color) {
    if (renderer->_module->set_pixela == NULL) {
        return;
    }
    renderer->_module->set_pixela(renderer->_module, position, color);
}

ltcolor_t ltrenderer_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position) {
    if (renderer->_module->get_pixel == NULL) {
        return LTCOLOR_BLACK;
    }
    return renderer->_module->get_pixel(renderer->_module, position);
}


void ltrenderer_clear(ltrenderer_t *renderer, ltcolora_t color) {
    if (renderer->_module->clear == NULL) {
        return;
    }
    renderer->_module->clear(renderer->_module, color);
}


void ltrenderer_draw_rect(ltrenderer_t *renderer, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color) {
    if (renderer->_module->draw_rect == NULL) {
        return;
    }
    renderer->_module->draw_rect(renderer->_module, rect, flags, color);
}

void ltrenderer_draw_circle(ltrenderer_t *renderer, ltvec2_t position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color) {
    if (renderer->_module->draw_circle == NULL) {
        return;
    }
    renderer->_module->draw_circle(renderer->_module, position, radius, flags, color);
}

void ltrenderer_draw_triangle(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, ltvec2_t c, ltrenderer_flags_t flags, ltcolora_t color) {
    ltvec2_t points[3] = {a, b, c};
    ltrenderer_draw_points(renderer, points, 3, flags, 1, color);
}


void ltrenderer_draw_line(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color) {
    if (renderer->_module->draw_line == NULL) {
        return;
    }
    renderer->_module->draw_line(renderer->_module, a, b, thickness, flags, color);
}

void ltrenderer_draw_points(ltrenderer_t *renderer, ltvec2_t *points, u32 count, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color) {
    if (renderer->_module->draw_line == NULL) {
        return;
    }

    if (count < 1) {
        return;
    }

    if (flags & LTRENDERER_FLAG_FILL && renderer->_module->fill_points != NULL) {
        renderer->_module->fill_points(renderer->_module, points, count, flags, color);
    }

    for (u32 i = 0; i < count; i++) {
        renderer->_module->draw_line(renderer->_module, points[i], points[(i + 1) % count], thickness, flags, color);
    }
}
