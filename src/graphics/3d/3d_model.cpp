#include <LTEngine/graphics/3d/3d_model.hpp>


using namespace LTEngine;
using namespace LTEngine::Graphics;


void Model3D::add_vertex(Vertex vertex) {
    auto vertex_it = std::find(_vertices.begin(), _vertices.end(), vertex);
    if (vertex_it != _vertices.end()) {
        _indices.push_back(std::distance(_vertices.begin(), vertex_it));
        return;
    }
    _vertices.push_back(vertex);
    _indices.push_back(_vertices.size() - 1);
}

void Model3D::remove_vertex(Vertex vertex) {
    auto vertex_it = std::find(_vertices.begin(), _vertices.end(), vertex);
    if (vertex_it == _vertices.end()) {
        return;
    }
    u32 vertex_index = std::distance(_vertices.begin(), vertex_it);

    auto index_it = std::find(_indices.begin(), _indices.end(), vertex_index);
    if (index_it == _indices.end()) {
        return;
    }
    _indices.erase(index_it);
    if (std::find(_indices.begin(), _indices.end(), vertex_index) == _indices.end()) {
        _vertices.erase(vertex_it);
    }
}


Model3D::Vertex Model3D::get_vertex(u32 index) {
    return _vertices[index];
}

std::vector<Model3D::Vertex> Model3D::get_vertices() {
    std::vector<Vertex> vertices;
    for (u32 index : _indices) {
        vertices.push_back(_vertices[index]);
    }
    return vertices;
}

std::vector<Model3D::Face> Model3D::get_faces() {
    std::vector<Face> faces;
    for (size_t i = 0; i < _indices.size(); i += 3) {
        faces.push_back(Face{
            _indices[i + 0],
            _indices[i + 1],
            _indices[i + 2]
        });
    }
    return faces;
}