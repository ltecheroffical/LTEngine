#ifndef _LTENGINE_SHAPE_2D_POLYGON_HPP_
#define _LTENGINE_SHAPE_2D_POLYGON_HPP_

#include <vector>

#include <LTEngine/shapes/2d/shape.hpp>


namespace LTEngine::Shapes {
	struct Polygon : public Shape2D {
		std::vector<Math::Vec2> points;

		void add_point(Math::Vec2 point) {
			points.push_back(point);
		}

		void remove_point(Math::Vec2 point) {
			points.erase(std::remove(points.begin(), points.end(), point), points.end());
		}
	};
} // namespace LTEngine::Shapes

#endif
