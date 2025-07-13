#ifndef _LTENGINE_SHAPE_2D_TRIANGLE_HPP_
#define _LTENGINE_SHAPE_2D_TRIANGLE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/2d/shape.hpp>


namespace LTEngine::Shapes {
	struct Triangle : public Shape2D {
		Math::Vec2 p1;
		Math::Vec2 p2;
		Math::Vec2 p3;
	};
} // namespace LTEngine::Shapes

#endif
