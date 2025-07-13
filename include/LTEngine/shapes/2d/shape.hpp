#ifndef _LTENGINE_SHAPE_2D_HPP_
#define _LTENGINE_SHAPE_2D_HPP_

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Shapes {
	struct Shape2D {
		f32 x = 0.f, y = 0.f;
		f32 rotation = 0.f;

		Shape2D() = default;
		Shape2D(f32 x, f32 y) : x(x), y(y) {
		}
		Shape2D(f32 x, f32 y, f32 rotation) : x(x), y(y), rotation(rotation) {
		}
	};

	struct Shape2Di {
		i32 x = 0, y = 0;
		i16 rotation = 0;

		Shape2Di() = default;
		Shape2Di(i32 x, i32 y) : x(x), y(y) {
		}
		Shape2Di(i32 x, i32 y, i16 rotation) : x(x), y(y), rotation(rotation) {
		}
	};
} // namespace LTEngine::Shapes

#endif
