#ifndef _LTENGINE_POLYGON_HPP_
#define _LTENGINE_POLYGON_HPP_

#include <vector>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>


namespace LTEngine::Shapes {
	struct Polygon : public Shape {
		std::vector<Math::Vec2> points;
	};
} // namespace LTEngine::Shapes

#endif
