#include <LTEngine/graphics/3d/3d_model.hpp>


using namespace LTEngine;
using namespace LTEngine::Graphics;


void Model3D::addVertex(Vertex vertex) {
    auto vertex_it = std::find(m_vertices.begin(), m_vertices.end(), vertex);
    if (vertex_it != m_vertices.end()) {
        m_indices.push_back(std::distance(m_vertices.begin(), vertex_it));
        return;
    }
    m_vertices.push_back(vertex);
    m_indices.push_back(m_vertices.size() - 1);
}

void Model3D::removeVertex(Vertex vertex) {
    auto vertex_it = std::find(m_vertices.begin(), m_vertices.end(), vertex);
    if (vertex_it == m_vertices.end()) {
        return;
    }
    u32 vertex_index = std::distance(m_vertices.begin(), vertex_it);

    auto index_it = std::find(m_indices.begin(), m_indices.end(), vertex_index);
    if (index_it == m_indices.end()) {
        return;
    }
    m_indices.erase(index_it);
    if (std::find(m_indices.begin(), m_indices.end(), vertex_index) == m_indices.end()) {
        m_vertices.erase(vertex_it);
    }
}


Model3D::Vertex Model3D::getVertex(u32 index) {
    return m_vertices[index];
}

std::vector<Model3D::Vertex> Model3D::getVertices() {
    std::vector<Vertex> vertices;
    for (u32 index : m_indices) {
        vertices.push_back(m_vertices[index]);
    }
    return vertices;
}

std::vector<Model3D::Face> Model3D::getFaces() {
    std::vector<Face> faces;
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        faces.push_back(Face{
            m_indices[i + 0],
            m_indices[i + 1],
            m_indices[i + 2]
        });
    }
    return faces;
}