#ifndef _LTCORE_SHAPE_2D_TRIANGLE_HPP_
#define _LTCORE_SHAPE_2D_TRIANGLE_HPP_

#include <LTCore/math/vec2.hpp>

#include <LTCore/shapes/2d/shape.hpp>


namespace LTCore::Shapes {
	struct Triangle : public Shape2D {
		Math::Vec2 p1;
		Math::Vec2 p2;
		Math::Vec2 p3;
	};
} // namespace LTCore::Shapes

#endif
