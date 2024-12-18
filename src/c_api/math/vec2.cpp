#include <LTEngine/math/vec2.hpp>

#include <LTEngine/c_api/math/vec2.h>


LTEngine_HVec2 LTEngine_CreateVec2(LTEngine_f32 x, LTEngine_f32 y) {
	return new LTEngine::Math::Vec2(x, y);
}

void LTEngine_DestroyVec2(LTEngine_HVec2 vec2) {
	delete (LTEngine::Math::Vec2 *)vec2;
}


void LTEngine_SetVec2X(LTEngine_HVec2 vec2, LTEngine_f32 x) {
	((LTEngine::Math::Vec2 *)vec2)->x = x;
}

void LTEngine_SetVec2Y(LTEngine_HVec2 vec2, LTEngine_f32 y) {
	((LTEngine::Math::Vec2 *)vec2)->y = y;
}


LTEngine_f32 LTEngine_GetVec2X(const LTEngine_HVec2 vec2) {
	return ((LTEngine::Math::Vec2 *)vec2)->x;
}

LTEngine_f32 LTEngine_GetVec2Y(const LTEngine_HVec2 vec2) {
	return ((LTEngine::Math::Vec2 *)vec2)->y;
}


LTEngine_HVec2 LTEngine_NormalizeVec2(LTEngine_HVec2 vec2) {
	auto result = new LTEngine::Math::Vec2;
	*result = ((LTEngine::Math::Vec2 *)vec2)->normalize();
	return result;
}

LTEngine_f32 LTEngine_Vec2Distance(const LTEngine_HVec2 a, const LTEngine_HVec2 b) {
	return ((LTEngine::Math::Vec2 *)a)->distance(*(LTEngine::Math::Vec2 *)b);
}


LTEngine_HVec2 LTEngine_AddVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a + *(LTEngine::Math::Vec2 *)b);
}

LTEngine_HVec2 LTEngine_AddiVec2(LTEngine_HVec2 a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a + b);
}

LTEngine_HVec2 LTEngine_AddfVec2(LTEngine_HVec2 a, LTEngine_f32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a + b);
}

LTEngine_HVec2 LTEngine_SubVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a - *(LTEngine::Math::Vec2 *)b);
}

LTEngine_HVec2 LTEngine_SubiVec2(LTEngine_HVec2 a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a - b);
}

LTEngine_HVec2 LTEngine_SubfVec2(LTEngine_HVec2 a, LTEngine_f32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a - b);
}

LTEngine_HVec2 LTEngine_MulVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a * *(LTEngine::Math::Vec2 *)b);
}

LTEngine_HVec2 LTEngine_MuliVec2(LTEngine_HVec2 a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a * b);
}

LTEngine_HVec2 LTEngine_MulfVec2(LTEngine_HVec2 a, LTEngine_f32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a * b);
}

LTEngine_HVec2 LTEngine_DivVec2(LTEngine_HVec2 a, const LTEngine_HVec2 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a / *(LTEngine::Math::Vec2 *)b);
}

LTEngine_HVec2 LTEngine_DiviVec2(LTEngine_HVec2 a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a / b);
}

LTEngine_HVec2 LTEngine_DivfVec2(LTEngine_HVec2 a, LTEngine_f32 b) {
	return new LTEngine::Math::Vec2(*(LTEngine::Math::Vec2 *)a / b);
}


LTEngine_HVec2i LTEngine_CreateVec2i(LTEngine_i32 x, LTEngine_i32 y) {
	return new LTEngine::Math::Vec2i(x, y);
}

void LTEngine_DestroyVec2i(LTEngine_HVec2i vec2) {
	delete (LTEngine::Math::Vec2i *)vec2;
}


void LTEngine_SetVec2iX(LTEngine_HVec2i vec2, LTEngine_i32 x) {
	((LTEngine::Math::Vec2i *)vec2)->x = x;
}

void LTEngine_SetVec2iY(LTEngine_HVec2i vec2, LTEngine_i32 y) {
	((LTEngine::Math::Vec2i *)vec2)->y = y;
}


LTEngine_i32 LTEngine_GetVec2iX(const LTEngine_HVec2i vec2) {
	return ((LTEngine::Math::Vec2i *)vec2)->x;
}

LTEngine_i32 LTEngine_GetVec2iY(const LTEngine_HVec2i vec2) {
	return ((LTEngine::Math::Vec2i *)vec2)->y;
}


LTEngine_HVec2i LTEngine_NormalizeVec2i(LTEngine_HVec2i vec2) {
	return new LTEngine::Math::Vec2i(((LTEngine::Math::Vec2i *)vec2)->normalize());
}

LTEngine_f32 LTEngine_Vec2iDistance(const LTEngine_HVec2i a, const LTEngine_HVec2i b) {
	return ((LTEngine::Math::Vec2i *)a)->distance(*(LTEngine::Math::Vec2i *)b);
}


LTEngine_HVec2i LTEngine_AddVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a + *(LTEngine::Math::Vec2i *)b);
}

LTEngine_HVec2i LTEngine_AddiVec2i(LTEngine_HVec2i a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a + b);
}

LTEngine_HVec2i LTEngine_SubVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a - *(LTEngine::Math::Vec2i *)b);
}

LTEngine_HVec2i LTEngine_SubiVec2i(LTEngine_HVec2i a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a - b);
}

LTEngine_HVec2i LTEngine_MulVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a * *(LTEngine::Math::Vec2i *)b);
}

LTEngine_HVec2i LTEngine_MuliVec2i(LTEngine_HVec2i a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a * b);
}

LTEngine_HVec2i LTEngine_DivVec2i(LTEngine_HVec2i a, const LTEngine_HVec2i b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a / *(LTEngine::Math::Vec2i *)b);
}

LTEngine_HVec2i LTEngine_DiviVec2i(LTEngine_HVec2i a, LTEngine_i32 b) {
	return new LTEngine::Math::Vec2i(*(LTEngine::Math::Vec2i *)a / b);
}


LTEngine_HVec2u LTEngine_CreateVec2u(LTEngine_u32 x, LTEngine_u32 y) {
	return new LTEngine::Math::Vec2u(x, y);
}

void LTEngine_DestroyVec2u(LTEngine_HVec2u vec2) {
	delete (LTEngine::Math::Vec2u *)vec2;
}


void LTEngine_SetVec2uX(LTEngine_HVec2u vec2, LTEngine_u32 x) {
	((LTEngine::Math::Vec2u *)vec2)->x = x;
}

void LTEngine_SetVec2uY(LTEngine_HVec2u vec2, LTEngine_u32 y) {
	((LTEngine::Math::Vec2u *)vec2)->y = y;
}


LTEngine_u32 LTEngine_GetVec2uX(const LTEngine_HVec2u vec2) {
	return ((LTEngine::Math::Vec2u *)vec2)->x;
}

LTEngine_u32 LTEngine_GetVec2uY(const LTEngine_HVec2u vec2) {
	return ((LTEngine::Math::Vec2u *)vec2)->y;
}


LTEngine_HVec2u LTEngine_AddVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a + *(LTEngine::Math::Vec2u *)b);
}

LTEngine_HVec2u LTEngine_AddiVec2u(LTEngine_HVec2u a, LTEngine_u32 b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a + b);
}

LTEngine_HVec2u LTEngine_SubVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a - *(LTEngine::Math::Vec2u *)b);
}

LTEngine_HVec2u LTEngine_SubiVec2u(LTEngine_HVec2u a, LTEngine_u32 b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a - b);
}

LTEngine_HVec2u LTEngine_MulVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a * *(LTEngine::Math::Vec2u *)b);
}

LTEngine_HVec2u LTEngine_MuliVec2u(LTEngine_HVec2u a, LTEngine_u32 b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a * b);
}

LTEngine_HVec2u LTEngine_DivVec2u(LTEngine_HVec2u a, const LTEngine_HVec2u b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a / *(LTEngine::Math::Vec2u *)b);
}

LTEngine_HVec2u LTEngine_DiviVec2u(LTEngine_HVec2u a, LTEngine_u32 b) {
	return new LTEngine::Math::Vec2u(*(LTEngine::Math::Vec2u *)a / b);
}
