#ifndef _LTENGINE_SHAPE_2D_RECT_HPP_
#define _LTENGINE_SHAPE_2D_RECT_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/2d/shape.hpp>


namespace LTEngine::Shapes {
	struct Rect : public Shape2D {
		f32 w, h;

		Rect(f32 x, f32 y, f32 w, f32 h) : Shape2D(x, y), w(w), h(h) {
		}
		Rect(Math::Vec2 pos, Math::Vec2 size) : Shape2D(pos.x, pos.y), w(size.x), h(size.y) {
		}
	};

	struct Recti : public Shape2Di {
		u32 w, h;

		Recti(i32 x, i32 y, u32 w, u32 h) : Shape2Di(x, y), w(w), h(h) {
		}
		Recti(Math::Vec2i pos, Math::Vec2u size) : Shape2Di(pos.x, pos.y), w(size.x), h(size.y) {
		}
	};
} // namespace LTEngine::Shapes

#endif
