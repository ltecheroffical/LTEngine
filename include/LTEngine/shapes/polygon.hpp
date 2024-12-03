#ifndef _LTENGINE_POLYGON_HPP_
#define _LTENGINE_POLYGON_HPP_

#include <vector>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/shape.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Shapes {
	struct LTENGINE_API Polygon : public Shape {
		std::vector<Math::Vec2> points;
	};
} // namespace LTEngine::Shapes

#endif
