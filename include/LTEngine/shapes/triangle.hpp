#ifndef _LTENGINE_SHAPES_TRIANGLE_HPP_
#define _LTENGINE_SHAPES_TRIANGLE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
	struct LTENGINE_API Triangle : public Shape {
		Math::Vec2 p1;
		Math::Vec2 p2;
		Math::Vec2 p3;
	};
} // namespace LTEngine::Shapes

#endif
