#include <stdlib.h>
#include <string.h>

#include <LTEngine/rendering/renderers/software_renderer.h>


void ltrenderer_software_free(ltrenderer_t *renderer);

void ltrenderer_software_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color);
ltcolor_t ltrenderer_software_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position);

void ltrenderer_software_clear(ltrenderer_t *renderer, ltcolora_t color);

void ltrenderer_software_draw_rect(ltrenderer_t *renderer, ltrecti_t rect, ltrenderer_flags_t flags, ltcolora_t color);
void ltrenderer_software_draw_circle(ltrenderer_t *renderer, ltvec2i_t center_position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color);

void ltrenderer_software_draw_line(ltrenderer_t *renderer, ltvec2i_t a, ltvec2i_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color);
void ltrenderer_software_draw_points(ltrenderer_t *renderer, const ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color);

void ltrenderer_software_draw_camera(ltrenderer_t *renderer, u32 id, ltvec2i_t position, ltrecti_t crop);




ltrenderer_software_t ltrenderer_software_new(u32 width, u32 height) {
    ltrenderer_software_t renderer;

    renderer._width = width;
    renderer._height = height;

    renderer._buffer.data = NULL;

    renderer._screen = (ltcolor_t*)calloc(sizeof(ltcolor_t), width * height);
    renderer._z_buffer = (u16*)calloc(sizeof(u16), width * height);

    renderer.renderer.functions.free = ltrenderer_software_free;

    renderer.renderer.functions.set_pixela = ltrenderer_software_set_pixela;
    renderer.renderer.functions.get_pixel = ltrenderer_software_get_pixel;

    renderer.renderer.functions.clear = ltrenderer_software_clear;

    renderer.renderer.functions.draw_rect = ltrenderer_software_draw_rect;
    renderer.renderer.functions.draw_circle = ltrenderer_software_draw_circle;

    renderer.renderer.functions.draw_line = ltrenderer_software_draw_line;
    renderer.renderer.functions.draw_points = ltrenderer_software_draw_points;

    renderer.renderer.functions.draw_camera = ltrenderer_software_draw_camera;

    return renderer;
}


u32 ltrenderer_software_get_pixels(const ltrenderer_software_t *renderer, ltcolor_t *screen) {
    if (screen != NULL) {
        memcpy(screen, renderer->_screen, sizeof(ltcolor_t) * renderer->_width * renderer->_height);
    }

    return renderer->_width * renderer->_height * sizeof(ltcolor_t);
}




static void ltrenderer_software_prepare_buffer(ltrenderer_software_t *renderer, u32 width, u32 height) {
    if (renderer->_buffer.data == NULL) {
        renderer->_buffer.data = (ltcolora_t*)calloc(sizeof(ltcolora_t), width * height);

        renderer->_buffer.width = width;
        renderer->_buffer.height = height;
    }

    u32 current_size = renderer->_buffer.width * renderer->_buffer.height * sizeof(ltcolora_t);
    u32 required_size = width * height * sizeof(ltcolora_t);

    if (required_size < current_size) {
        free(renderer->_buffer.data);
        renderer->_buffer.data = (ltcolora_t*)calloc(sizeof(ltcolora_t), width * height);

        renderer->_buffer.width = width;
        renderer->_buffer.height = height;
    }
}

static void ltrenderer_software_buffer_set_pixel(ltrenderer_software_t *renderer, u32 x, u32 y, ltcolora_t color) {
    renderer->_buffer.data[y * renderer->_buffer.width + x] = color;
}

static void ltrenderer_software_buffer_transfer_to_screen(ltrenderer_software_t *renderer, u32 pos_x, u32 pos_y) {
    for (u32 y = 0; y < renderer->_buffer.height; y++) {
        for (u32 x = 0; x < renderer->_buffer.width; x++) {
            if (pos_x + x < 0 || pos_x + x >= renderer->_width || pos_y + y < 0 || pos_y + y >= renderer->_height) {
                // Do not draw outside the screen
                continue;
            }

            ltcolor_t bg = renderer->_screen[(pos_y + y) * renderer->_width + (pos_x + x)];
            f32 A_n = renderer->_buffer.data[y * renderer->_buffer.width + x].a / 255.f;

            renderer->_screen[(pos_y + y) * renderer->_width + (pos_x + x)] = ltcolor_add(
                ltcolor_mulf(ltcolor_fromA(renderer->_buffer.data[y * renderer->_buffer.width + x]), A_n),
                ltcolor_mulf(bg, 1.f - A_n)
            );
        }
    }
}




void ltrenderer_software_free(ltrenderer_t *renderer) {
    ltrenderer_software_t *renderer_software = (ltrenderer_software_t*)renderer;

    free(renderer_software->_screen);
    free(renderer_software->_z_buffer);
}


void ltrenderer_software_set_pixela(ltrenderer_t *renderer, ltvec2i_t position, ltcolora_t color) {
    // TODO
}

ltcolor_t ltrenderer_software_get_pixel(const ltrenderer_t *renderer, ltvec2i_t position) {
    // TODO
    return LTCOLOR_BLACK;
}


void ltrenderer_software_clear(ltrenderer_t *renderer, ltcolora_t color) {
    // TODO
}


void ltrenderer_software_draw_rect(ltrenderer_t *renderer, ltrecti_t rect, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_software_prepare_buffer((ltrenderer_software_t*)renderer, rect.w, rect.h);

    for (u32 y = 0; y < rect.h; y++) {
        for (u32 x = 0; x < rect.w; x++) {
            ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, x, y, color);
        }
    }

    ltrenderer_software_buffer_transfer_to_screen((ltrenderer_software_t*)renderer, rect.x, rect.y);
}

void ltrenderer_software_draw_circle(ltrenderer_t *renderer, ltvec2i_t center_position, u32 radius, ltrenderer_flags_t flags, ltcolora_t color) {
    ltrenderer_software_prepare_buffer((ltrenderer_software_t*)renderer, 2 * radius + 1, 2 * radius + 1);

    u32 center_x = radius;
    u32 center_y = radius;

    s32 x = radius;
    s32 y = 0;
    s32 p = 1 - radius;

    while (x >= y) {
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x + x, center_y + y, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x + x, center_y - y, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x - x, center_y + y, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x - x, center_y - y, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x + y, center_y + x, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x + y, center_y - x, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x - y, center_y + x, color);
        ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, center_x - y, center_y - x, color);

        if (p <= 0) {
            p += 2 * ++y + 1;
        } else {
            p += 2 * (++y - --x) + 1;
        }
    }


    if (flags & LTRENDERER_FLAG_FILL) {
        for (u32 y = 0; y < 2 * radius + 1; y++) {
            for (u32 x = 0; x < 2 * radius + 1; x++) {
                // Do not draw outside the circle
                s32 dx = x - radius;
                s32 dy = y - radius;

                if (dx * dx + dy * dy > radius * radius) {
                    continue;
                }
                ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, x, y, color);
            }
        }
    }


    ltrenderer_software_buffer_transfer_to_screen((ltrenderer_software_t*)renderer, center_position.x - radius - 1, center_position.y - radius - 1);
}


void ltrenderer_software_draw_line(ltrenderer_t *renderer, ltvec2i_t a, ltvec2i_t b, u16 thickness, ltrenderer_flags_t flags, ltcolora_t color) {
    u32 width = abs(b.x - a.x) + 1;
    u32 height = abs(b.y - a.y) + 1;

    ltrenderer_software_prepare_buffer((ltrenderer_software_t*)renderer, width, height);

    s32 position_x = (a.x < b.x) ? a.x : b.x;
    s32 position_y = (a.y < b.y) ? a.y : b.y;

    a.x -= position_x;
    a.y -= position_y;
    b.x -= position_x;
    b.y -= position_y;

    s32 dx = abs(b.x - a.x);
    s32 dy = abs(b.y - a.y);
    s32 sx = (a.x < b.x) ? 1 : -1;
    s32 sy = (a.y < b.y) ? 1 : -1;
    s32 err = dx - dy;

    while (true) {
        for (s32 dx = -thickness; dx <= thickness / 2; dx++) {
            for (s32 dy = -thickness; dy <= thickness / 2; dy++) {
                if (a.x + dx < 0 || a.x + dx >= width || a.y + dy < 0 || a.y + dy >= height) {
                    continue;
                }
                ltrenderer_software_buffer_set_pixel((ltrenderer_software_t*)renderer, a.x + dx, a.y + dy, color);
            }
        }
        
        if (a.x == b.x && a.y == b.y) {
            break;
        }

        s32 e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            a.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            a.y += sy;
        }
    }

    ltrenderer_software_buffer_transfer_to_screen((ltrenderer_software_t*)renderer, position_x, position_y);
}

void ltrenderer_software_draw_points(ltrenderer_t *renderer, const ltvec2_t *points, u32 count, ltrenderer_flags_t flags, ltcolora_t color) {
    // TODO
}


void ltrenderer_software_draw_camera(ltrenderer_t *renderer, u32 id, ltvec2i_t position, ltrecti_t crop) {
    // TODO
}
