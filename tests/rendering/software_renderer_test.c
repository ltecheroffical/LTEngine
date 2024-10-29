#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <acutest.h>

#include <LTEngine/rendering/renderer.h>
#include <LTEngine/rendering/renderer_modules/software_renderer_module.h>


#define RENDER_WIDTH        ((u32)20)
#define RENDER_HEIGHT       ((u32)20)
#define RENDER_CLEAR_COLOR  ((ltcolora_t)LTCOLORA_BLACK)
#define RENDER_FILL_COLOR   ((ltcolora_t)LTCOLORA_RED)


void output_to_image(const char *filename, const ltcolor_t *screen, u32 width, u32 height) {
    ltimage_t image = ltimage_from_buffer(screen, width, height);
    ltimage_save_image_png(&image, filename);
    ltimage_free(&image);
}


void test_renderer_clear() {
    ltrenderer_software_module_t module = ltrenderer_software_module_new(RENDER_WIDTH, RENDER_HEIGHT);
    ltrenderer_t renderer = ltrenderer_new(&module.module);

    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_module_get_pixels(&module, NULL));
    
    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&renderer, RENDER_CLEAR_COLOR);

    ltrenderer_software_module_get_pixels(&module, screen);

    for (u32 y = 0; y < RENDER_HEIGHT; y++) {
        for (u32 x = 0; x < RENDER_WIDTH; x++) {
            TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_CLEAR_COLOR.r);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_CLEAR_COLOR.g);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_CLEAR_COLOR.b);
        }
    }

    ltrenderer_free(&renderer);
    free(screen);
}


void test_renderer_draw_rect() {
    ltrenderer_software_module_t module = ltrenderer_software_module_new(RENDER_WIDTH, RENDER_HEIGHT);
    ltrenderer_t renderer = ltrenderer_new(&module.module);
   
    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_module_get_pixels(&module, NULL));

    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&renderer, RENDER_CLEAR_COLOR);

    ltrenderer_draw_rect(&renderer, ltrect_new(1, 1, RENDER_WIDTH - 2, RENDER_HEIGHT - 2), 0, RENDER_FILL_COLOR);
    
    ltrenderer_software_module_get_pixels(&module, screen);

    for (u32 y = 0; y < RENDER_HEIGHT; y++) {
        for (u32 x = 0; x < RENDER_WIDTH; x++) {
            if (y == 0 || y == RENDER_HEIGHT - 1 || x == 0 || x == RENDER_WIDTH - 1) {
                TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_CLEAR_COLOR.r);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_CLEAR_COLOR.g);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_CLEAR_COLOR.b);
                continue;
            }
            TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_FILL_COLOR.r);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_FILL_COLOR.g);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_FILL_COLOR.b);
        }
    }

    ltrenderer_free(&renderer);
    free(screen);
}

void test_renderer_draw_circle() {
    ltrenderer_software_module_t module = ltrenderer_software_module_new(RENDER_WIDTH, RENDER_HEIGHT);
    ltrenderer_t renderer = ltrenderer_new(&module.module);
   
    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_module_get_pixels(&module, NULL));

    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&renderer, RENDER_CLEAR_COLOR);

    const u8 circle_radius = 2;

    ltrenderer_draw_circle(&renderer, ltvec2_new(circle_radius, circle_radius), circle_radius, LTRENDERER_FLAG_FILL, RENDER_FILL_COLOR);
    
    ltrenderer_software_module_get_pixels(&module, screen);

    
    const u8 circle_expected_data[] = {
        0b01101111,
        0b11110110
    };

    for (u8 y = 0; y < circle_radius * 2; y++) {
        for (u8 x = 0; x < circle_radius * 2; x++) {
            u8 index = y * circle_radius * 2 + x;
            bool expected_pixel = (circle_expected_data[index / 8] >> (7 - (index % 8))) & 1;
            
            if (expected_pixel) {
                TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_FILL_COLOR.r);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_FILL_COLOR.g);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_FILL_COLOR.b);
            } else {
                TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_CLEAR_COLOR.r);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_CLEAR_COLOR.g);
                TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_CLEAR_COLOR.b);
            }
        }
    }

    ltrenderer_free(&renderer);
    free(screen);
}



TEST_LIST = {
    {"test_renderer_clear", test_renderer_clear},

    {"test_renderer_draw_rect", test_renderer_draw_rect},
    {"test_renderer_draw_circle", test_renderer_draw_circle},

    {NULL, NULL}
};
