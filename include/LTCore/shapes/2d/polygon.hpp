#ifndef _LTCORE_SHAPE_2D_POLYGON_HPP_
#define _LTCORE_SHAPE_2D_POLYGON_HPP_

#include <vector>

#include <LTCore/shapes/2d/shape.hpp>


namespace LTCore::Shapes {
	struct Polygon : public Shape2D {
		std::vector<Math::Vec2> points;

		void addPoint(Math::Vec2 point) {
			points.push_back(point);
		}

		void removePoint(Math::Vec2 point) {
			points.erase(std::remove(points.begin(), points.end(), point), points.end());
		}
	};
} // namespace LTCore::Shapes

#endif
