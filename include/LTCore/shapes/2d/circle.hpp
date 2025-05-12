#ifndef _LTCORE_SHAPE_2D_CIRCLE_HPP_
#define _LTCORE_SHAPE_2D_CIRCLE_HPP_

#include <LTCore/math/vec2.hpp>

#include <LTCore/shapes/2d/shape.hpp>


namespace LTCore::Shapes {
	struct Circle : public Shape2D {
		f32 radius;
	};
} // namespace LTCore::Shapes

#endif
