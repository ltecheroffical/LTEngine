#ifndef _LTENGINE_SHAPES_RECT_HPP_
#define _LTENGINE_SHAPES_RECT_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Shapes {
	struct LTENGINE_API Rect : public Shape {
		u32 w, h;

		Rect(f32 x, f32 y, u32 w, u32 h) : Shape(x, y), w(w), h(h) {}
		Rect(Math::Vec2 pos, Math::Vec2u size) : Shape(pos.x, pos.y), w(size.x), h(size.y) {}
	};

	struct LTENGINE_API Recti : public Shapei {
		u32 w, h;

		Recti(i32 x, i32 y, u32 w, u32 h) : Shapei(x, y), w(w), h(h) {}
		Recti(Math::Vec2i pos, Math::Vec2u size) : Shapei(pos.x, pos.y), w(size.x), h(size.y) {}
	};
} // namespace LTEngine::Shapes

#endif
