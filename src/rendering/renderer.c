#include <stdlib.h>

#include <LTEngine/rendering/renderer.h>


static void ltrenderer_init(ltrenderer_t *renderer) {
    if (renderer->is_initialized) {
        return;
    }
    renderer->is_initialized = true;

    renderer->_scale = ltvec2_new(1, 1);
    renderer->_rotation = 0.f;

    renderer->_pos_offset = ltvec2_new(0, 0);
    renderer->_scale_offset = ltvec2_new(0, 0);
    renderer->_rotation_offset = 0.f;

    renderer->_z_order = 0.f;

    renderer->_iris_mode = false;

    renderer->_cams.size = 8;
    renderer->_cams.cams = calloc(sizeof(ltrenderer_camera_t), renderer->_cams.size);
}


void ltrenderer_free(ltrenderer_t *renderer) {
    renderer->functions.free(renderer);
}


void ltrenderer_set_scale(ltrenderer_t *renderer, ltvec2_t scale) {
    ltrenderer_init(renderer);
    renderer->_scale = scale;
}

void ltrenderer_set_rotation(ltrenderer_t *renderer, float rotation) {
    ltrenderer_init(renderer);
    renderer->_rotation = rotation;
}


void ltrenderer_set_position_offset(ltrenderer_t *renderer, ltvec2_t offset) {
    ltrenderer_init(renderer);
    renderer->_pos_offset = offset;
}

void ltrenderer_set_scale_offset(ltrenderer_t *renderer, ltvec2_t offset) {
    ltrenderer_init(renderer);
    renderer->_scale_offset = offset;
}

void ltrenderer_set_rotation_offset(ltrenderer_t *renderer, float offset) {
    ltrenderer_init(renderer);
    renderer->_rotation_offset = offset;
}


void ltrenderer_set_z_order(ltrenderer_t *renderer, u16 z) {
    ltrenderer_init(renderer);
    renderer->_z_order = z;
}


void ltrenderer_set_iris(ltrenderer_t *renderer) {
    ltrenderer_init(renderer);
    renderer->_iris_mode = true;
}

void ltrenderer_clear_iris_mode(ltrenderer_t *renderer, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->_iris_mode = false;
}


ltresult_u32_t ltrenderer_create_camera(ltrenderer_t *renderer, ltvec2_t position, ltvec2_t zoom) {
    ltrenderer_init(renderer);

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
    ltrenderer_init(renderer);

    if (renderer->_cams.size < index) {
        return;
    }

    renderer->_cams.cams[index].in_use = false;
}

void ltrenderer_set_camera_position(ltrenderer_t *renderer, u32 index, ltvec2_t position) {
    ltrenderer_init(renderer);

    if (renderer->_cams.size < index) {
        return;
    }
    renderer->_cams.cams[index].x = position.x;
    renderer->_cams.cams[index].y = position.y;
}

void ltrenderer_set_camera_zoom(ltrenderer_t *renderer, u32 id, ltvec2_t zoom) {
    ltrenderer_init(renderer);

    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].zoom = zoom;
}

void ltrenderer_exclude_camera(ltrenderer_t *renderer, u32 id) {
    ltrenderer_init(renderer);

    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].exclude = true;
}

void ltrenderer_include_camera(ltrenderer_t *renderer, u32 id) {
    ltrenderer_init(renderer);

    if (renderer->_cams.size < id) {
        return;
    }
    renderer->_cams.cams[id].exclude = false;
}

void ltrenderer_include_cameras(ltrenderer_t *renderer) {
    ltrenderer_init(renderer);

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
    ltrenderer_init(renderer);
    renderer->functions.set_pixela(renderer, position, color);
}

ltcolor_t ltrenderer_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position) {
    return renderer->functions.get_pixel(renderer, position);
}


void ltrenderer_clear(ltrenderer_t *renderer, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->functions.clear(renderer, color);
}


void ltrenderer_draw_rect(ltrenderer_t *renderer, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->functions.draw_rect(renderer, ltrecti_new(rect.x, rect.y, rect.w, rect.h), flags, color);
}

void ltrenderer_draw_circle(ltrenderer_t *renderer, ltvec2_t position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->functions.draw_circle(renderer, ltvec2i_new(position.x, position.y), radius, flags, color);
}

void ltrenderer_draw_triangle(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, ltvec2_t c, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_init(renderer);

    ltvec2_t points[3] = {a, b, c};
    ltrenderer_draw_points(renderer, points, 3, flags, color);
}


void ltrenderer_draw_line(ltrenderer_t *renderer, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->functions.draw_line(renderer, ltvec2i_new(a.x, a.y), ltvec2i_new(b.x, b.y), thickness, flags, color);
}

void ltrenderer_draw_points(ltrenderer_t *renderer, const ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_init(renderer);
    renderer->functions.draw_points(renderer, points, count, flags, color);
}
