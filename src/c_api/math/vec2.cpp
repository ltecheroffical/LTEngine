#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/math/vec2.h>

#include <LTEngine/math/vec2.hpp>


LTEngine_HVec2 lt_engine_vec2(LTEngine_f32 x, LTEngine_f32 y) {
	return {{new LTEngine::Math::Vec2(x, y)}};
}

void lt_engine_vec2_free(LTEngine_HVec2 handle) {
	delete (LTEngine::Math::Vec2 *)handle.handle.ptr;
}


LTEngine_f32 lt_engine_vec2_x(const LTEngine_HVec2 handle) {
	return ((LTEngine::Math::Vec2 *)handle.handle.ptr)->x;
}

LTEngine_f32 lt_engine_vec2_y(const LTEngine_HVec2 handle) {
	return ((LTEngine::Math::Vec2 *)handle.handle.ptr)->y;
}


void lt_engine_vec2_set_x(LTEngine_HVec2 handle, LTEngine_f32 x) {
	((LTEngine::Math::Vec2 *)handle.handle.ptr)->x = x;
}

void lt_engine_vec2_set_y(LTEngine_HVec2 handle, LTEngine_f32 y) {
	((LTEngine::Math::Vec2 *)handle.handle.ptr)->y = y;
}


LTEngine_HVec2 lt_engine_vec2_normalize(const LTEngine_HVec2 handle) {
	auto vec2 = new LTEngine::Math::Vec2();
	*vec2 = ((LTEngine::Math::Vec2 *)handle.handle.ptr)->normalize();
	return {{vec2}};
}

LTEngine_f32 lt_engine_vec2_distance(const LTEngine_HVec2 handle1, const LTEngine_HVec2 handle2) {
	return ((LTEngine::Math::Vec2 *)handle1.handle.ptr)->distance(*(LTEngine::Math::Vec2 *)handle2.handle.ptr);
}


LTEngine_HVec2i lt_engine_vec2i(LTEngine_i32 x, LTEngine_i32 y) {
	return {{new LTEngine::Math::Vec2i(x, y)}};
}

void lt_engine_vec2i_free(LTEngine_HVec2i handle) {
	delete (LTEngine::Math::Vec2i *)handle.handle.ptr;
}


LTEngine_i32 lt_engine_vec2i_x(const LTEngine_HVec2i handle) {
	return ((LTEngine::Math::Vec2i *)handle.handle.ptr)->x;
}

LTEngine_i32 lt_engine_vec2i_y(const LTEngine_HVec2i handle) {
	return ((LTEngine::Math::Vec2i *)handle.handle.ptr)->x;
}


void lt_engine_vec2i_set_x(LTEngine_HVec2i handle, LTEngine_i32 x) {
	((LTEngine::Math::Vec2i *)handle.handle.ptr)->x = x;
}

void lt_engine_vec2i_set_y(LTEngine_HVec2i handle, LTEngine_i32 y) {
	((LTEngine::Math::Vec2i *)handle.handle.ptr)->y = y;
}


LTEngine_HVec2i lt_engine_vec2i_normalize(const LTEngine_HVec2i handle) {
	auto vec2 = new LTEngine::Math::Vec2i();
	*vec2 = ((LTEngine::Math::Vec2i *)handle.handle.ptr)->normalize();
	return {{vec2}};
}

LTEngine_f32 lt_engine_vec2i_distance(const LTEngine_HVec2i handle1, const LTEngine_HVec2i handle2) {
	return ((LTEngine::Math::Vec2i *)handle1.handle.ptr)->distance(*(LTEngine::Math::Vec2i *)handle2.handle.ptr);
}


LTEngine_HVec2u lt_engine_vec2u(LTEngine_u32 x, LTEngine_u32 y) {
	return {{new LTEngine::Math::Vec2u(x, y)}};
}

void lt_engine_vec2u_free(LTEngine_HVec2u handle) {
	delete (LTEngine::Math::Vec2u *)handle.handle.ptr;
}


LTEngine_u32 lt_engine_vec2u_x(const LTEngine_HVec2u handle) {
	return ((LTEngine::Math::Vec2u *)handle.handle.ptr)->x;
}

LTEngine_u32 lt_engine_vec2u_y(const LTEngine_HVec2u handle) {
	return ((LTEngine::Math::Vec2u *)handle.handle.ptr)->x;
}


void lt_engine_vec2u_set_x(LTEngine_HVec2u handle, LTEngine_u32 x) {
	((LTEngine::Math::Vec2u *)handle.handle.ptr)->x = x;
}

void lt_engine_vec2u_set_y(LTEngine_HVec2u handle, LTEngine_u32 y) {
	((LTEngine::Math::Vec2u *)handle.handle.ptr)->y = y;
}

#endif
