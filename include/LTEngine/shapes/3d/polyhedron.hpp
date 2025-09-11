#ifndef _LTENGINE_SHAPE_POLYHEDRON_HPP_
#define _LTENGINE_SHAPE_POLYHEDRON_HPP_

#include <vector>

#include <LTEngine/math/vec3.hpp>

#include <LTEngine/shapes/3d/shape.hpp>

namespace LTEngine::Shapes {
    struct Polyhedron : public Shape {
        std::vector<Math::Vec3> vertices;
		std::vector<u32> indices;

		void add_point(Math::Vec3 point) {
			auto it = std::find(vertices.begin(), vertices.end(), point);
			if (it == vertices.end()) {
				vertices.push_back(point);
				indices.push_back(vertices.size() - 1);
			} else {
				indices.push_back(std::distance(vertices.begin(), it));
			}
		}

		void remove_point(Math::Vec3 point) {
			auto vertex_it = std::find(vertices.begin(), vertices.end(), point);
			if (vertex_it == vertices.end()) {
				return;
			}

			u32 vertex_index = std::distance(vertices.begin(), vertex_it);
			auto index_it = std::find(indices.begin(), indices.end(), vertex_index);
			if (index_it == indices.end()) {
				return;
			}
			indices.erase(index_it);

			if (std::find(indices.begin(), indices.end(), vertex_index) == indices.end()) {
				vertices.erase(vertex_it);
			}
		}

		std::vector<Math::Vec3> get_points() const {
			std::vector<Math::Vec3> points;
			for (u32 index : indices) {
				points.push_back(vertices[index]);
			}
			return points;
		}
    };
}

#endif // _LTENGINE_SHAPE_POLYHEDRON_HPP_
