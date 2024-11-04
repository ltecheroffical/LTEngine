#include <LTEngine/rendering/renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


void Renderer::setScale(Math::Vec2 scale) {
    m_scaleFactor[0] = scale;
    m_scale = scale * m_scaleFactor[1];
}

void Renderer::setRotation(f32 rotation) {
    m_rotationOffset[0] = rotation;
    m_rotation = rotation + m_rotationOffset[1];
}


void Renderer::setZOrder(u16 z) {
    m_zOrder = z;
}


void Renderer::setRotationOffset(f32 offset) {
    m_rotationOffset[1] = offset;
    m_rotation = m_rotationOffset[0] + m_rotationOffset[1];
}

void Renderer::setScaleFactor(Math::Vec2 scale) {
    m_scaleFactor[1] = scale;
    m_scale = m_scaleFactor[0] * m_scaleFactor[1];
}

void Renderer::setPositionOffset(Math::Vec2 offset) {
    m_positionOffset = offset;
}


void Renderer::setIrisMode() {
    m_irisMode = true;
}

void Renderer::clearIrisMode() {
    m_irisMode = false;
}


u32 Renderer::createCamera(Math::Vec2 position, Math::Vec2 zoom) {
    Camera camera;

    camera.position = position;
    camera.zoom = zoom;
    camera.exclude = true;

    u32 index = m_cameras.size();
    m_cameras.push_back(camera);

    return index;
}

void Renderer::deleteCamera(u32 id) {
    m_cameras.erase(m_cameras.begin() + id);
}

void Renderer::setCameraPosition(u32 id, Math::Vec2 position) {
    m_cameras.at(id).position = position;
}

void Renderer::setCameraRotation(u32 id, f32 rotation) {
    m_cameras.at(id).rotation = rotation;
}

void Renderer::setCameraZoom(u32 id, Math::Vec2 zoom) {
    m_cameras.at(id).zoom = zoom;
}

void Renderer::setCameraInclude(u32 id) {
    m_cameras.at(id).exclude = false;
}

void Renderer::setCameraExclude(u32 id) {
    m_cameras.at(id).exclude = true;
}

Math::Vec2 Renderer::getCameraPosition(u32 id) const {
    return m_cameras.at(id).position;
}

Math::Vec2 Renderer::getCameraZoom(u32 id) const {
    return m_cameras.at(id).zoom;
}

f32 Renderer::getCameraRotation(u32 id) const {
    return m_cameras.at(id).rotation;
}


void Renderer::drawTriangle(Math::Vec2 a, Math::Vec2 b, Math::Vec2 c, ColorA color, RendererFlags flags) {
    drawLine(a, b, 1, color, flags);
    drawLine(b, c, 1, color, flags);
    drawLine(c, a, 1, color, flags);
}
