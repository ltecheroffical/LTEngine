#ifndef _LTCORE_SHAPE_POLYHEDRON_HPP_
#define _LTCORE_SHAPE_POLYHEDRON_HPP_

#include <vector>

#include <LTCore/math/vec3.hpp>

#include <LTCore/shapes/3d/shape.hpp>

namespace LTCore::Shapes {
    struct Polyhedron : public Shape {
        std::vector<Math::Vec3> points;

		void addPoint(Math::Vec3 point) {
			points.push_back(point);
		}

		void removePoint(Math::Vec3 point) {
			points.erase(std::remove(points.begin(), points.end(), point), points.end());
		}
    };
}

#endif // _LTCORE_SHAPE_POLYHEDRON_HPP_