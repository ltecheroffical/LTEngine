#ifndef _LTENGINE_SHAPE_HPP_
#define _LTENGINE_SHAPE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Shapes {
	struct LTENGINE_API Shape {
		f32 x = 0.f, y = 0.f;
		f32 rotation = 0.f;

		Shape() = default;
		Shape(f32 x, f32 y) : x(x), y(y) {}
		Shape(f32 x, f32 y, f32 rotation) : x(x), y(y), rotation(rotation) {}
	};

	struct LTENGINE_API Shapei {
		i32 x = 0, y = 0;
		i16 rotation = 0;

		Shapei() = default;
		Shapei(i32 x, i32 y) : x(x), y(y) {}
		Shapei(i32 x, i32 y, i16 rotation) : x(x), y(y), rotation(rotation) {}
	};
} // namespace LTEngine::Shapes

#endif
