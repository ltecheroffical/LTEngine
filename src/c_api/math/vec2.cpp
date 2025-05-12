#ifdef LTCORE_COMPONENT_C_API
#include <LTCore/c_api/math/vec2.h>

#include <LTCore/math/vec2.hpp>


LTCore_HVec2 LTCore_Vec2(LTCore_f32 x, LTCore_f32 y) {
	return {{new LTCore::Math::Vec2(x, y)}};
}

void LTCore_Vec2_free(LTCore_HVec2 handle) {
	delete (LTCore::Math::Vec2 *)handle.handle.ptr;
}


LTCore_f32 LTCore_Vec2_x(const LTCore_HVec2 handle) {
	return ((LTCore::Math::Vec2 *)handle.handle.ptr)->x;
}

LTCore_f32 LTCore_Vec2_y(const LTCore_HVec2 handle) {
	return ((LTCore::Math::Vec2 *)handle.handle.ptr)->y;
}


void LTCore_Vec2_setX(LTCore_HVec2 handle, LTCore_f32 x) {
	((LTCore::Math::Vec2 *)handle.handle.ptr)->x = x;
}

void LTCore_Vec2_setY(LTCore_HVec2 handle, LTCore_f32 y) {
	((LTCore::Math::Vec2 *)handle.handle.ptr)->y = y;
}


LTCore_HVec2 LTCore_Vec2_normalize(const LTCore_HVec2 handle) {
	auto vec2 = new LTCore::Math::Vec2();
	*vec2 = ((LTCore::Math::Vec2 *)handle.handle.ptr)->normalize();
	return {{vec2}};
}

LTCore_f32 LTCore_Vec2_distance(const LTCore_HVec2 handle1, const LTCore_HVec2 handle2) {
	return ((LTCore::Math::Vec2 *)handle1.handle.ptr)->distance(*(LTCore::Math::Vec2 *)handle2.handle.ptr);
}


LTCore_HVec2i LTCore_Vec2i(LTCore_i32 x, LTCore_i32 y) {
	return {{new LTCore::Math::Vec2i(x, y)}};
}

void LTCore_Vec2i_free(LTCore_HVec2i handle) {
	delete (LTCore::Math::Vec2i *)handle.handle.ptr;
}


LTCore_i32 LTCore_Vec2i_x(const LTCore_HVec2i handle) {
	return ((LTCore::Math::Vec2i *)handle.handle.ptr)->x;
}

LTCore_i32 LTCore_Vec2i_y(const LTCore_HVec2i handle) {
	return ((LTCore::Math::Vec2i *)handle.handle.ptr)->x;
}


void LTCore_Vec2i_setX(LTCore_HVec2i handle, LTCore_i32 x) {
	((LTCore::Math::Vec2i *)handle.handle.ptr)->x = x;
}

void LTCore_Vec2i_setY(LTCore_HVec2i handle, LTCore_i32 y) {
	((LTCore::Math::Vec2i *)handle.handle.ptr)->y = y;
}


LTCore_HVec2i LTCore_Vec2i_normalize(const LTCore_HVec2i handle) {
	auto vec2 = new LTCore::Math::Vec2i();
	*vec2 = ((LTCore::Math::Vec2i *)handle.handle.ptr)->normalize();
	return {{vec2}};
}

LTCore_f32 LTCore_Vec2i_distance(const LTCore_HVec2i handle1, const LTCore_HVec2i handle2) {
	return ((LTCore::Math::Vec2i *)handle1.handle.ptr)->distance(*(LTCore::Math::Vec2i *)handle2.handle.ptr);
}


LTCore_HVec2u LTCore_Vec2u(LTCore_u32 x, LTCore_u32 y) {
	return {{new LTCore::Math::Vec2u(x, y)}};
}

void LTCore_Vec2u_free(LTCore_HVec2u handle) {
	delete (LTCore::Math::Vec2u *)handle.handle.ptr;
}


LTCore_u32 LTCore_Vec2u_x(const LTCore_HVec2u handle) {
	return ((LTCore::Math::Vec2u *)handle.handle.ptr)->x;
}

LTCore_u32 LTCore_Vec2u_y(const LTCore_HVec2u handle) {
	return ((LTCore::Math::Vec2u *)handle.handle.ptr)->x;
}


void LTCore_Vec2u_setX(LTCore_HVec2u handle, LTCore_u32 x) {
	((LTCore::Math::Vec2u *)handle.handle.ptr)->x = x;
}

void LTCore_Vec2u_setY(LTCore_HVec2u handle, LTCore_u32 y) {
	((LTCore::Math::Vec2u *)handle.handle.ptr)->y = y;
}

#endif
