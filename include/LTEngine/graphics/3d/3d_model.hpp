#ifndef _LTENGINE_3D_MODEL_HPP_
#define _LTENGINE_3D_MODEL_HPP_

#include <vector>

#include <LTEngine/math/vec3.hpp>
#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Graphics {
    class Model3D {
    public:
        Model3D() = default;
        ~Model3D() = default;

        struct Vertex {
            Math::Vec3 position;
            Math::Vec3 normal;
            Math::Vec2 uv;

            bool operator==(Vertex other) {
                return position == other.position && normal == other.normal && uv == other.uv;
            }
        };

        struct Face {
            u32 a, b, c;
        };

        void add_vertex(Vertex vertex);
        void remove_vertex(Vertex vertex);

        Vertex get_vertex(u32 index);
        std::vector<Vertex> get_vertices();
        std::vector<Face> get_faces();

    private:
        std::vector<Vertex> _vertices;
        std::vector<u32> _indices;
    };
}

#endif // _LTENGINE_3D_MODEL_HPP_