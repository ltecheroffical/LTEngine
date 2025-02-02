#include <LTEngine/c_api/math/vec2.h>

#include <LTEngine/math/vec2.hpp>


LTEngine_HVec2 LTEngine_Vec2_init(LTEngine_f32 x, LTEngine_f32 y) {
	return new LTEngine::Math::Vec2(x, y);
}

void LTENGINE_API LTEngine_Vec2_free(LTEngine_HVec2 handle) {
	delete (LTEngine::Math::Vec2 *)handle;
}


LTEngine_f32 LTEngine_Vec2_x(const LTEngine_HVec2 handle) {
	return ((LTEngine::Math::Vec2 *)handle)->x;
}

LTEngine_f32 LTEngine_Vec2_y(const LTEngine_HVec2 handle) {
	return ((LTEngine::Math::Vec2 *)handle)->y;
}


void LTEngine_Vec2_setX(LTEngine_HVec2 handle, LTEngine_f32 x) {
	((LTEngine::Math::Vec2 *)handle)->x = x;
}

void LTEngine_Vec2_setY(LTEngine_HVec2 handle, LTEngine_f32 y) {
	((LTEngine::Math::Vec2 *)handle)->y = y;
}


LTEngine_HVec2 LTEngine_Vec2_normalize(LTEngine_HVec2 handle) {
	auto vec2 = new LTEngine::Math::Vec2();
	*vec2 = ((LTEngine::Math::Vec2 *)handle)->normalize();
	return vec2;
}

LTEngine_f32 LTEngine_Vec2_distance(LTEngine_HVec2 handle1, LTEngine_HVec2 handle2) {
	return ((LTEngine::Math::Vec2 *)handle1)->distance(*(LTEngine::Math::Vec2 *)handle2);
}


LTEngine_HVec2i LTEngine_Vec2i_init(LTEngine_i32 x, LTEngine_i32 y) {
	return new LTEngine::Math::Vec2i(x, y);
}

void LTENGINE_API LTEngine_Vec2i_free(LTEngine_HVec2i handle) {
	delete (LTEngine::Math::Vec2i *)handle;
}


LTEngine_i32 LTEngine_Vec2i_x(const LTEngine_HVec2i handle) {
	return ((LTEngine::Math::Vec2i *)handle)->x;
}

LTEngine_i32 LTEngine_Vec2i_y(const LTEngine_HVec2i handle) {
	return ((LTEngine::Math::Vec2i *)handle)->x;
}


void LTEngine_Vec2i_setX(LTEngine_HVec2i handle, LTEngine_i32 x) {
	((LTEngine::Math::Vec2i *)handle)->x = x;
}

void LTEngine_Vec2i_setY(LTEngine_HVec2i handle, LTEngine_i32 y) {
	((LTEngine::Math::Vec2i *)handle)->y = y;
}


LTEngine_HVec2i LTEngine_Vec2i_normalize(LTEngine_HVec2i handle) {
	auto vec2 = new LTEngine::Math::Vec2i();
	*vec2 = ((LTEngine::Math::Vec2i *)handle)->normalize();
	return vec2;
}

LTEngine_f32 LTEngine_Vec2i_distance(LTEngine_HVec2i handle1, LTEngine_HVec2i handle2) {
	return ((LTEngine::Math::Vec2i *)handle1)->distance(*(LTEngine::Math::Vec2i *)handle2);
}


LTEngine_HVec2u LTEngine_Vec2u_init(LTEngine_u32 x, LTEngine_u32 y) {
	return new LTEngine::Math::Vec2u(x, y);
}

void LTENGINE_API LTEngine_Vec2u_free(LTEngine_HVec2u handle) {
	delete (LTEngine::Math::Vec2u *)handle;
}


LTEngine_u32 LTEngine_Vec2u_x(const LTEngine_HVec2u handle) {
	return ((LTEngine::Math::Vec2u *)handle)->x;
}

LTEngine_u32 LTEngine_Vec2u_y(const LTEngine_HVec2u handle) {
	return ((LTEngine::Math::Vec2u *)handle)->x;
}


void LTEngine_Vec2u_setX(LTEngine_HVec2u handle, LTEngine_u32 x) {
	((LTEngine::Math::Vec2u *)handle)->x = x;
}

void LTEngine_Vec2u_setY(LTEngine_HVec2u handle, LTEngine_u32 y) {
	((LTEngine::Math::Vec2u *)handle)->y = y;
}
