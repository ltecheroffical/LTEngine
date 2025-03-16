#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>


#include <LTEngine/c_api/shapes/shape.h>
#include <LTEngine/c_api/shapes/rect.h>

#include <LTEngine/c_api/random/platform_random.h>


void test_rect_storage(void **state) {
	(void)state;

	LTEngine_HPlatformRandom random = LTEngine_PlatformRandom(LTEngine_PlatformRandom_RandomSettings_createDefault());

	LTEngine_f32 rect_position[2] = {LTEngine_Random_next_f32(random) * 100.f, LTEngine_Random_next_f32(random) * 100.f};
	LTEngine_u32 rect_size[2] = {LTEngine_Random_next_u32(random), LTEngine_Random_next_u32(random)};

	LTEngine_HRect rect = LTEngine_Rect(rect_position[0], rect_position[1], rect_size[0], rect_size[1]);

	assert_true(LTEngine_Shape_x(rect) == rect_position[0]);
	assert_true(LTEngine_Shape_y(rect) == rect_position[1]);
	assert_true(LTEngine_Rect_w(rect) == rect_size[0]);
	assert_true(LTEngine_Rect_h(rect) == rect_size[1]);

	rect_position[0] = LTEngine_Random_next_f32(random) * 100.f;
	rect_position[1] = LTEngine_Random_next_f32(random) * 100.f;
	rect_size[0] = LTEngine_Random_next_u32(random);
	rect_size[1] = LTEngine_Random_next_u32(random);

	LTEngine_Shape_setX(rect, rect_position[0]);
	LTEngine_Shape_setY(rect, rect_position[1]);
	LTEngine_Rect_setW(rect, rect_size[0]);
	LTEngine_Rect_setH(rect, rect_size[1]);

	assert_true(LTEngine_Shape_x(rect) == rect_position[0]);
	assert_true(LTEngine_Shape_y(rect) == rect_position[1]);
	assert_true(LTEngine_Rect_w(rect) == rect_size[0]);
	assert_true(LTEngine_Rect_h(rect) == rect_size[1]);

	LTEngine_Rect_free(rect);
}

void test_recti_storage(void **state) {
	(void)state;

	LTEngine_HPlatformRandom random = LTEngine_PlatformRandom(LTEngine_PlatformRandom_RandomSettings_createDefault());

	LTEngine_i32 rect_position[2] = {LTEngine_Random_next_i32(random), LTEngine_Random_next_i32(random)};
	LTEngine_u32 rect_size[2] = {LTEngine_Random_next_u32(random), LTEngine_Random_next_u32(random)};

	LTEngine_HRecti rect = LTEngine_Recti(rect_position[0], rect_position[1], rect_size[0], rect_size[1]);

	assert_true(LTEngine_Shapei_x(rect) == rect_position[0]);
	assert_true(LTEngine_Shapei_y(rect) == rect_position[1]);
	assert_true(LTEngine_Recti_w(rect) == rect_size[0]);
	assert_true(LTEngine_Recti_h(rect) == rect_size[1]);

	rect_position[0] = LTEngine_Random_next_i32(random);
	rect_position[1] = LTEngine_Random_next_i32(random);
	rect_size[0] = LTEngine_Random_next_u32(random);
	rect_size[1] = LTEngine_Random_next_u32(random);

	LTEngine_Shapei_setX(rect, rect_position[0]);
	LTEngine_Shapei_setY(rect, rect_position[1]);
	LTEngine_Recti_setW(rect, rect_size[0]);
	LTEngine_Recti_setH(rect, rect_size[1]);

	assert_true(LTEngine_Shapei_x(rect) == rect_position[0]);
	assert_true(LTEngine_Shapei_y(rect) == rect_position[1]);
	assert_true(LTEngine_Recti_w(rect) == rect_size[0]);
	assert_true(LTEngine_Recti_h(rect) == rect_size[1]);

	LTEngine_Recti_free(rect);
}


int main(void) {
	const struct CMUnitTest tests[] = {
	    cmocka_unit_test(test_rect_storage),
	    cmocka_unit_test(test_recti_storage),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
