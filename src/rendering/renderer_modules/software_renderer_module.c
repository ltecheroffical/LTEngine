#include <stdlib.h>
#include <string.h>

#include <LTEngine/rendering/renderer_modules/software_renderer_module.h>


void ltrenderer_software_free(ltrenderer_module_t *module);

void ltrenderer_software_set_scale(ltrenderer_module_t *module, ltvec2_t scale);
void ltrenderer_software_set_rotation(ltrenderer_module_t *module, f32 rotation);

void ltrenderer_software_set_z(ltrenderer_module_t *module, u16 z);

void ltrenderer_software_set_active_camera(ltrenderer_module_t *module, u32 id);
void ltrenderer_software_clear_active_camera(ltrenderer_module_t *module);

void ltrenderer_software_set_iris_mode(ltrenderer_module_t *module);
void ltrenderer_software_clear_iris_mode(ltrenderer_module_t *module, ltcolora_t color);

void ltrenderer_software_set_pixela(ltrenderer_module_t *module, ltvec2i_t position, ltcolora_t color);
ltcolor_t ltrenderer_software_get_pixel(const ltrenderer_module_t *module, ltvec2i_t position);

void ltrenderer_software_clear(ltrenderer_module_t *module, ltcolora_t color);

void ltrenderer_software_draw_rect(ltrenderer_module_t *module, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color);
void ltrenderer_software_draw_circle(ltrenderer_module_t *module, ltvec2_t center_position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color);

void ltrenderer_software_draw_line(ltrenderer_module_t *module, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color);
void ltrenderer_software_fill_points(ltrenderer_module_t *module, ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color);

void ltrenderer_software_draw_camera(ltrenderer_module_t *module, u32 id, ltvec2_t position, ltrect_t crop);




ltrenderer_software_module_t ltrenderer_software_module_new(u32 width, u32 height) {
    ltrenderer_software_module_t module;

    module._width = width;
    module._height = height;

    module._buffer.data = NULL;

    module._screen = (ltcolor_t*)calloc(sizeof(ltcolor_t), width * height);
    module._z_buffer = (u16*)calloc(sizeof(u16), width * height);

    module._z_order = 0;

    module.module.free = ltrenderer_software_free;

    module.module.set_scale = ltrenderer_software_set_scale;
    module.module.set_rotation = ltrenderer_software_set_rotation;

    module.module.set_z = ltrenderer_software_set_z;

    module.module.set_active_camera = ltrenderer_software_set_active_camera;
    module.module.clear_active_camera = ltrenderer_software_clear_active_camera;

    module.module.set_iris_mode = ltrenderer_software_set_iris_mode;
    module.module.clear_iris_mode = ltrenderer_software_clear_iris_mode;

    module.module.set_pixela = ltrenderer_software_set_pixela;
    module.module.get_pixel = ltrenderer_software_get_pixel;

    module.module.clear = ltrenderer_software_clear;

    module.module.draw_rect = ltrenderer_software_draw_rect;
    module.module.draw_circle = ltrenderer_software_draw_circle;

    module.module.draw_line = ltrenderer_software_draw_line;
    module.module.fill_points = ltrenderer_software_fill_points;

    module.module.draw_camera = ltrenderer_software_draw_camera;

    return module;
}


u32 ltrenderer_software_module_get_pixels(const ltrenderer_software_module_t *module, ltcolor_t *screen) {
    if (screen != NULL) {
        memcpy(screen, module->_screen, sizeof(ltcolor_t) * module->_width * module->_height);
    }

    return module->_width * module->_height * sizeof(ltcolor_t);
}




static void ltrenderer_software_prepare_buffer(ltrenderer_software_module_t *module, u32 width, u32 height) {
    if (module->_buffer.data == NULL) {
        module->_buffer.data = (ltcolora_t*)calloc(sizeof(ltcolora_t), width * height);

        module->_buffer.width = width;
        module->_buffer.height = height;
    }

    u32 current_size = module->_buffer.width * module->_buffer.height * sizeof(ltcolora_t);
    u32 required_size = width * height * sizeof(ltcolora_t);

    if (required_size < current_size) {
        free(module->_buffer.data);
        module->_buffer.data = (ltcolora_t*)calloc(sizeof(ltcolora_t), width * height);

        module->_buffer.width = width;
        module->_buffer.height = height;
    }
}

static void ltrenderer_software_buffer_set_pixel(ltrenderer_software_module_t *module, u32 x, u32 y, ltcolora_t color) {
    module->_buffer.data[y * module->_buffer.width + x] = color;
}

static void ltrenderer_software_buffer_transfer_to_screen(ltrenderer_software_module_t *module, u32 pos_x, u32 pos_y) {
    for (u32 y = 0; y < module->_buffer.height; y++) {
        for (u32 x = 0; x < module->_buffer.width; x++) {
            if (pos_x + x < 0 || pos_x + x >= module->_width || pos_y + y < 0 || pos_y + y >= module->_height) {
                // Do not draw outside the screen
                continue;
            }

            ltcolor_t bg = module->_screen[(pos_y + y) * module->_width + (pos_x + x)];
            f32 A_n = module->_buffer.data[y * module->_buffer.width + x].a / 255.f;

            module->_screen[(pos_y + y) * module->_width + (pos_x + x)] = ltcolor_add(
                ltcolor_mulf(ltcolor_fromA(module->_buffer.data[y * module->_buffer.width + x]), A_n),
                ltcolor_mulf(bg, 1.f - A_n)
            );
        }
    }
}




void ltrenderer_software_free(ltrenderer_module_t *module) {
    ltrenderer_software_module_t *module_software = (ltrenderer_software_module_t*)module;

    free(module_software->_screen);
    free(module_software->_z_buffer);
}


void ltrenderer_software_set_scale(ltrenderer_module_t *module, ltvec2_t scale) {
    // TODO
}

void ltrenderer_software_set_rotation(ltrenderer_module_t *module, f32 rotation) {
    // TODO
}


void ltrenderer_software_set_z(ltrenderer_module_t *module, u16 z) {
    ltrenderer_software_module_t *module_software = (ltrenderer_software_module_t*)module;
    module_software->_z_order = z;
}


void ltrenderer_software_set_active_camera(ltrenderer_module_t *module, u32 id) {
    // TODO
}

void ltrenderer_software_clear_active_camera(ltrenderer_module_t *module) {
    // TODO
}


void ltrenderer_software_set_iris_mode(ltrenderer_module_t *module) {
    // TODO
}

void ltrenderer_software_clear_iris_mode(ltrenderer_module_t *module, ltcolora_t color) {
    // TODO
}


void ltrenderer_software_set_pixela(ltrenderer_module_t *module, ltvec2i_t position, ltcolora_t color) {
    // TODO
}

ltcolor_t ltrenderer_software_get_pixel(const ltrenderer_module_t *module, ltvec2i_t position) {
    // TODO
    return LTCOLOR_BLACK;
}


void ltrenderer_software_clear(ltrenderer_module_t *module, ltcolora_t color) {
    // TODO
}


void ltrenderer_software_draw_rect(ltrenderer_module_t *module, ltrect_t rect, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_software_prepare_buffer((ltrenderer_software_module_t*)module, rect.w, rect.h);

    for (u32 y = 0; y < rect.h; y++) {
        for (u32 x = 0; x < rect.w; x++) {
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, x, y, color);
        }
    }

    ltrenderer_software_buffer_transfer_to_screen((ltrenderer_software_module_t*)module, rect.x, rect.y);
}

void ltrenderer_software_draw_circle(ltrenderer_module_t *module, ltvec2_t center_position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_software_prepare_buffer((ltrenderer_software_module_t*)module, 2 * radius + 1, 2 * radius + 1);

    const i8 small_radius_patterns[4][32][2] = {
        // Radius 1
        { {0, 0}, {1, 0}, {0, 1}, {1, 1}, {-1, -1} },
        // Radius 2
        { {1, 0}, {2, 0}, {0, 1}, {0, 2}, {3, 1}, {3, 2}, {1, 3}, {2, 3}, {-1, -1} },
        // Radius 3
        { {1, 1}, {2, 0}, {3, 0}, {4, 1}, {0, 2}, {0, 3}, {5, 2}, {5, 3}, {1, 4}, {2, 5}, {3, 5}, {4, 4}, {-1, -1} },
        // Radius 4
        { {0, 3}, {0, 2}, {1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 1}, {7, 2}, {7, 3}, {0, 4}, {0, 5}, {1, 6}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 6}, {7, 5}, {7, 4}, {-1, -1} }
    };
    
    const i8 small_radius_patterns_fill[4][8][4] = {
        // Radius 1
        { {-1, -1} },
        // Radius 2
        { {1, 1, 1, 1}, {-1, -1} },
        // Radius 3
        { {2, 1, 1, 3}, {1, 2, 3, 1}, {-1, -1} },
        // Radius 4
        { {2, 1, 3, 5}, {1, 2, 5, 3}, {-1, -1} },
    }
;
    u32 center_x = radius;
    u32 center_y = radius;


    if (radius <= 4) {
        for (u32 i = 0;; i++) {
            i8 dx = small_radius_patterns[(u8)radius - 1][i][0];
            i8 dy = small_radius_patterns[(u8)radius - 1][i][1];

            if (dx == -1 && dy == -1) {
                break;
            }
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, dx, dy, color);
        }
    } else {
        s32 x = radius;
        s32 y = 0;
        s32 p = 1 - radius;

        while (x >= y) {
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x + x, center_y + y, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x + x, center_y - y, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x - x, center_y + y, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x - x, center_y - y, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x + y, center_y + x, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x + y, center_y - x, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x - y, center_y + x, color);
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, center_x - y, center_y - x, color);

            if (p <= 0) {
                p += 2 * ++y + 1;
            } else {
                p += 2 * (++y - x--) + 1;
            }
        }
    }


    if (flags & LTRENDERER_FLAG_FILL) {
        if (radius <= 4) {
            for (u32 i = 0;; i++) {
                i8 from_x = small_radius_patterns_fill[(u8)radius - 1][i][0];
                i8 from_y = small_radius_patterns_fill[(u8)radius - 1][i][1];
                
                i8 to_x = small_radius_patterns_fill[(u8)radius - 1][i][2] + from_x;
                i8 to_y = small_radius_patterns_fill[(u8)radius - 1][i][3] + from_y;
                
                if (from_x == -1 && from_y == -1) {
                    break;
                }

                for (u32 y = from_y; y <= to_y; y++) {
                    for (u32 x = from_x; x <= to_x; x++) {
                        ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, x, y, color);
                    }
                }
            }
        } else {
            for (u32 y = 0; y < 2 * radius + 1; y++) {
                for (u32 x = 0; x < 2 * radius + 1; x++) {
                    // Do not draw outside the circle
                    s32 dx = x - radius;
                    s32 dy = y - radius;

                    if (dx * dx + dy * dy > radius * radius) {
                        continue;
                    }
                    ltrenderer_software_buffer_set_pixel((ltrenderer_software_module_t*)module, x, y, color);
                }
            }
        }
    }


    ltrenderer_software_buffer_transfer_to_screen((ltrenderer_software_module_t*)module, center_position.x - radius, center_position.y - radius);
}


void ltrenderer_software_draw_line(ltrenderer_module_t *module, ltvec2_t a, ltvec2_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color) {
    // TODO
}

void ltrenderer_software_fill_points(ltrenderer_module_t *module, ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color) {
    // TODO
}


void ltrenderer_software_draw_camera(ltrenderer_module_t *module, u32 id, ltvec2_t position, ltrect_t crop) {
    // TODO
}
