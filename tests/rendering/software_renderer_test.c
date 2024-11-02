#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <acutest.h>

#include <LTEngine/rendering/renderer.h>
#include <LTEngine/rendering/renderers/software_renderer.h>


#define RENDER_WIDTH            ((u32)20)
#define RENDER_HEIGHT           ((u32)20)
#define RENDER_CLEAR_COLOR      ((ltcolora_t)LTCOLORA_BLACK)
#define RENDER_FILL_COLOR       ((ltcolora_t)LTCOLORA_RED)
#define RENDER_FILL_COLOR_ALT   ((ltcolora_t)LTCOLORA_BLUE)


void output_to_image(const char *filename, const ltcolor_t *screen, u32 width, u32 height) {
    ltimage_t image = ltimage_from_buffer(screen, width, height);
    ltimage_save_image_png(&image, filename);
    ltimage_free(&image);
}


void test_renderer_clear() {
    ltrenderer_software_t software_renderer = ltrenderer_software_new(RENDER_WIDTH, RENDER_HEIGHT);

    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_get_pixels(&software_renderer, NULL));
    
    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&software_renderer.renderer, RENDER_CLEAR_COLOR);

    ltrenderer_software_get_pixels(&software_renderer, screen);

    for (u32 y = 0; y < RENDER_HEIGHT; y++) {
        for (u32 x = 0; x < RENDER_WIDTH; x++) {
            TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_CLEAR_COLOR.r);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_CLEAR_COLOR.g);
            TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_CLEAR_COLOR.b);
        }
    }

    ltrenderer_free(&software_renderer.renderer);
    free(screen);
}


void test_renderer_draw_rect() {
    ltrenderer_software_t software_renderer = ltrenderer_software_new(RENDER_WIDTH, RENDER_HEIGHT);
   
    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_get_pixels(&software_renderer, NULL));

    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&software_renderer.renderer, RENDER_CLEAR_COLOR);

    ltrenderer_draw_rect(&software_renderer.renderer, ltrect_new(1, 1, RENDER_WIDTH - 2, RENDER_HEIGHT - 2), 0, RENDER_FILL_COLOR);
    
    ltrenderer_software_get_pixels(&software_renderer, screen);

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

    ltrenderer_free(&software_renderer.renderer);
    free(screen);
}

void test_renderer_draw_circle() {
    ltrenderer_software_t software_renderer = ltrenderer_software_new(RENDER_WIDTH, RENDER_HEIGHT);
   
    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_get_pixels(&software_renderer, NULL));

    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&software_renderer.renderer, RENDER_CLEAR_COLOR);

    const u8 circle_radius = 2;

    ltrenderer_draw_circle(&software_renderer.renderer, ltvec2_new(circle_radius + 1, circle_radius + 1), circle_radius, LTRENDERER_FLAG_FILL, RENDER_FILL_COLOR);
    
    ltrenderer_software_get_pixels(&software_renderer, screen);

    /* 
        Visualization:
              . . .
            . . . . .
            . . . . .
            . . . . .
              . . .

        The format is 1bpp
     */ 
    const u8 circle_expected_data[] = {
        0b01110111,
        0b11111111,
        0b11110111,
        0b0
    };

    for (u8 y = 0; y < circle_radius * 2 + 1; y++) {
        for (u8 x = 0; x < circle_radius * 2 + 1; x++) {
            u8 index = y * (circle_radius * 2 + 1) + x;
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

    ltrenderer_free(&software_renderer.renderer);
    free(screen);
}

void test_renderer_draw_line() {
    ltrenderer_software_t software_renderer = ltrenderer_software_new(RENDER_WIDTH, RENDER_HEIGHT);
   
    ltcolor_t *screen = (ltcolor_t*)malloc(ltrenderer_software_get_pixels(&software_renderer, NULL));

    TEST_ASSERT(screen != NULL);

    ltrenderer_clear(&software_renderer.renderer, RENDER_CLEAR_COLOR);

    ltrenderer_draw_line(&software_renderer.renderer, ltvec2_new(0, 0), ltvec2_new(RENDER_WIDTH - 1, RENDER_HEIGHT - 1), 1, 0, RENDER_FILL_COLOR);
    
    ltrenderer_software_get_pixels(&software_renderer, screen);

    u32 lx = 0;
    u32 ly = 0;


    while ((lx * 2) < RENDER_WIDTH && (ly * 2) < RENDER_HEIGHT) {
        for (u32 x = 0; x < 2; x++) {
            for (u32 y = 0; y < 2; y++) {
                TEST_CHECK(screen[(y + ly) * RENDER_WIDTH + (x + lx)].r == RENDER_FILL_COLOR.r);
                TEST_CHECK(screen[(y + ly) * RENDER_WIDTH + (x + lx)].g == RENDER_FILL_COLOR.g);
                TEST_CHECK(screen[(y + ly) * RENDER_WIDTH + (x + lx)].b == RENDER_FILL_COLOR.b);
            }
        }
        lx++;
        ly++;
    }

    ltrenderer_free(&software_renderer.renderer);
    free(screen);
}


TEST_LIST = {
    {"test_renderer_clear", test_renderer_clear},

    {"test_renderer_draw_rect", test_renderer_draw_rect},
    {"test_renderer_draw_circle", test_renderer_draw_circle},
    {"test_renderer_draw_line", test_renderer_draw_line},

    {NULL, NULL}
};
