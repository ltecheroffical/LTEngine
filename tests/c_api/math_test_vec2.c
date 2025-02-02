#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>


#include <LTEngine/c_api/math/vec2.h>

#include <LTEngine/c_api/random/platform_random.h>


void test_vec2_storage(void **state) {
	(void)state;

	LTEngine_HPlatformRandom random = LTEngine_PlatformRandom_init(LTEngine_PlatformRandom_RandomSettings_createDefault());

	LTEngine_f32 vec2_contents[2] = {LTEngine_Random_next_f32(random) * 100.f, LTEngine_Random_next_f32(random) * 100.f};
	LTEngine_HVec2 vec2 = LTEngine_Vec2_init(vec2_contents[0], vec2_contents[1]);

	assert_true(LTEngine_Vec2_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2_y(vec2) == vec2_contents[1]);

	vec2_contents[0] = LTEngine_Random_next_f32(random) * 100.f;
	vec2_contents[1] = LTEngine_Random_next_f32(random) * 100.f;

	LTEngine_Vec2_setX(vec2, vec2_contents[0]);
	LTEngine_Vec2_setY(vec2, vec2_contents[1]);

	assert_true(LTEngine_Vec2_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2_y(vec2) == vec2_contents[1]);

	LTEngine_Vec2_free(vec2);
}

void test_vec2i_storage(void **state) {
	(void)state;

	LTEngine_HPlatformRandom random = LTEngine_PlatformRandom_init(LTEngine_PlatformRandom_RandomSettings_createDefault());

	LTEngine_i32 vec2_contents[2] = {LTEngine_Random_next_i32(random), LTEngine_Random_next_i32(random)};
	LTEngine_HVec2i vec2 = LTEngine_Vec2i_init(vec2_contents[0], vec2_contents[1]);

	assert_true(LTEngine_Vec2i_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2i_y(vec2) == vec2_contents[1]);

	vec2_contents[0] = LTEngine_Random_next_i32(random);
	vec2_contents[1] = LTEngine_Random_next_i32(random);

	LTEngine_Vec2i_setX(vec2, vec2_contents[0]);
	LTEngine_Vec2i_setY(vec2, vec2_contents[1]);

	assert_true(LTEngine_Vec2i_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2i_y(vec2) == vec2_contents[1]);

	LTEngine_Vec2i_free(vec2);
}

void test_vec2u_storage(void **state) {
	(void)state;

	LTEngine_HPlatformRandom random = LTEngine_PlatformRandom_init(LTEngine_PlatformRandom_RandomSettings_createDefault());

	LTEngine_u32 vec2_contents[2] = {LTEngine_Random_next_u32(random), LTEngine_Random_next_u32(random)};
	LTEngine_HVec2u vec2 = LTEngine_Vec2u_init(vec2_contents[0], vec2_contents[1]);

	assert_true(LTEngine_Vec2u_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2u_y(vec2) == vec2_contents[1]);

	vec2_contents[0] = LTEngine_Random_next_u32(random);
	vec2_contents[1] = LTEngine_Random_next_u32(random);

	LTEngine_Vec2u_setX(vec2, vec2_contents[0]);
	LTEngine_Vec2u_setY(vec2, vec2_contents[1]);

	assert_true(LTEngine_Vec2u_x(vec2) == vec2_contents[0]);
	assert_true(LTEngine_Vec2u_y(vec2) == vec2_contents[1]);

	LTEngine_Vec2u_free(vec2);
}


int main(void) {
	const struct CMUnitTest tests[] = {
	    cmocka_unit_test(test_vec2_storage),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
