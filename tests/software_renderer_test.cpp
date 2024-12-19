#define LTENGINE_GLOBAL_BASIC_TYPES

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <acutest.h>

#include <LTEngine/rendering/software_renderer.hpp>


#define RENDER_WIDTH ((u32)20)
#define RENDER_HEIGHT ((u32)20)
#define RENDER_CLEAR_COLOR ((ColorA)ColorA::Black)
#define RENDER_FILL_COLOR ((ColorA)ColorA::Red)
#define RENDER_FILL_COLOR_ALT ((ColorA)ColorA::Blue)


using namespace LTEngine;
using namespace LTEngine::Math;
using namespace LTEngine::Rendering;


void outputToImage(const char *filename, const Color *screen, u32 width, u32 height) {
	Image image = Image(screen, width, height);
	image.savePNG(filename);
}


void test_renderer_clear() {
	SoftwareRenderer softwareRenderer = SoftwareRenderer(RENDER_WIDTH, RENDER_HEIGHT);
	std::vector<Color> screen(softwareRenderer.getScreenData(nullptr));

	softwareRenderer.setScreenOnly();
	softwareRenderer.clear(RENDER_CLEAR_COLOR);
	softwareRenderer.processAll();

	softwareRenderer.getScreenData(screen.data());

	for (u32 y = 0; y < RENDER_HEIGHT; y++) {
		for (u32 x = 0; x < RENDER_WIDTH; x++) {
			TEST_CHECK(screen[y * RENDER_WIDTH + x].r == RENDER_CLEAR_COLOR.r);
			TEST_CHECK(screen[y * RENDER_WIDTH + x].g == RENDER_CLEAR_COLOR.g);
			TEST_CHECK(screen[y * RENDER_WIDTH + x].b == RENDER_CLEAR_COLOR.b);
		}
	}
}


void test_renderer_draw_rect() {
	SoftwareRenderer softwareRenderer = SoftwareRenderer(RENDER_WIDTH, RENDER_HEIGHT);
	std::vector<Color> screen(softwareRenderer.getScreenData(nullptr));

	softwareRenderer.setScreenOnly();
	softwareRenderer.clear(RENDER_CLEAR_COLOR);

	softwareRenderer.drawRect({1, 1, RENDER_WIDTH - 1, RENDER_HEIGHT - 1}, RENDER_FILL_COLOR);
	softwareRenderer.processAll();

	softwareRenderer.getScreenData(screen.data());

	for (u32 y = 0; y < RENDER_HEIGHT; y++) {
		for (u32 x = 0; x < RENDER_WIDTH; x++) {
			if (y == 0 || y == RENDER_HEIGHT || x == 0 || x == RENDER_WIDTH) {
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
}

void test_renderer_draw_circle() {
	SoftwareRenderer softwareRenderer = SoftwareRenderer(RENDER_WIDTH, RENDER_HEIGHT);
	std::vector<Color> screen(softwareRenderer.getScreenData(nullptr));

	softwareRenderer.setScreenOnly();
	softwareRenderer.clear(RENDER_CLEAR_COLOR);

	const u8 circleRadius = 2;

	softwareRenderer.drawCircle({{circleRadius + 1, circleRadius + 1}, circleRadius}, RENDER_FILL_COLOR, Renderer::FLAG_FILL);
	softwareRenderer.processAll();

	softwareRenderer.getScreenData(screen.data());

	/*
	    Visualization:
	          . . .
	        . . . . .
	        . . . . .
	        . . . . .
	          . . .

	    The format is 1bpp
	 */
	const u8 circleExpectedData[] = {0b01110111, 0b11111111, 0b11110111, 0b0};

	for (u8 y = 0; y < circleRadius * 2 + 1; y++) {
		for (u8 x = 0; x < circleRadius * 2 + 1; x++) {
			u8 index = y * (circleRadius * 2 + 1) + x;
			bool expected_pixel = (circleExpectedData[index / 8] >> (7 - (index % 8))) & 1;

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
	outputToImage("circle.png", screen.data(), RENDER_WIDTH, RENDER_HEIGHT);
}

void test_renderer_draw_line() {
	SoftwareRenderer softwareRenderer = SoftwareRenderer(RENDER_WIDTH, RENDER_HEIGHT);
	std::vector<Color> screen(softwareRenderer.getScreenData(nullptr));

	softwareRenderer.setScreenOnly();
	softwareRenderer.clear(RENDER_CLEAR_COLOR);

	softwareRenderer.drawLine({0, 0}, {RENDER_WIDTH - 1, RENDER_HEIGHT - 1}, 1, RENDER_FILL_COLOR, 0);
	softwareRenderer.processAll();

	softwareRenderer.getScreenData(screen.data());

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
}


TEST_LIST = {{"test_renderer_clear", test_renderer_clear},

             {"test_renderer_draw_rect", test_renderer_draw_rect},
             {"test_renderer_draw_circle", test_renderer_draw_circle},
             {"test_renderer_draw_line", test_renderer_draw_line},

             {NULL, NULL}};
