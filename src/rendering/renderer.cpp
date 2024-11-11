#include <LTEngine/rendering/renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


void Renderer::setScale(Math::Vec2 scale) {
    m_scaleFactor[0] = scale;
    recalculateTransform();
}


void Renderer::setZOrder(u16 z) {
    m_zOrder = z;
}


void Renderer::setRotationOffset(f32 offset) {
    m_realRotationOffset = offset;
    recalculateTransform();
}

void Renderer::setScaleFactor(Math::Vec2 scale) {
    m_scaleFactor[1] = scale;
    recalculateTransform();
}

void Renderer::setPositionOffset(Math::Vec2 offset) {
    m_realPositionOffset = offset;
    recalculateTransform();
}


void Renderer::resetTransform() {
    m_positionOffset = Math::Vec2::ZERO;
    m_realRotationOffset = 0.f;
    m_scaleFactor[0] = Math::Vec2::ONE;

    m_scaleFactor[1] = Math::Vec2::ONE;

    recalculateTransform();
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
    camera.exclude = false;
    camera.id = m_nextCameraId++;

    m_cameras.push_back(camera);
    cameraCreated(camera.id);
    return camera.id;
}

void Renderer::deleteCamera(u32 id) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    m_cameras.erase(it);
    cameraDestroyed(id);
}

void Renderer::setCameraPosition(u32 id, Math::Vec2 position) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    it->position = position;
}

void Renderer::setCameraRotation(u32 id, f32 rotation) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    it->rotation = rotation;
}

void Renderer::setCameraZoom(u32 id, Math::Vec2 zoom) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    it->zoom = zoom;
}

void Renderer::setCameraInclude(u32 id) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    it->exclude = false;
}

void Renderer::setCameraExclude(u32 id) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    it->exclude = true;
}

void Renderer::setCurrentCamera(u32 id) {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });

    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }

    m_currentCamera = id;
    m_currentCameraActive = true;
    
    recalculateTransform();
    cameraSelected(id);
}

void Renderer::clearCurrentCamera() {
    m_currentCameraActive = false;
    recalculateTransform();
    cameraDeselected();
}

Math::Vec2 Renderer::getCameraPosition(u32 id) const {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    return it->position;
}

Math::Vec2 Renderer::getCameraZoom(u32 id) const {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    return it->zoom;
}

f32 Renderer::getCameraRotation(u32 id) const {
    auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) {
        return camera.id == id;
    });
    if (it == m_cameras.end()) {
        throw std::runtime_error("Camera not found");
    }
    return it->rotation;
}


void Renderer::drawTriangle(Shapes::Triangle triangle, ColorA color, RendererFlags flags) {
    if (flags & FLAG_FILL) {
        drawPoints({
            .points = {
                triangle.p1,
                triangle.p2,
                triangle.p3
            }
        }, color, flags);
    }

    drawLine(triangle.p1, triangle.p2, 1, color, flags);
    drawLine(triangle.p2, triangle.p3, 1, color, flags);
    drawLine(triangle.p3, triangle.p1, 1, color, flags);
}


void Renderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, ColorA color, RendererFlags flags) {
    drawImage(image, position, rotation, Shapes::Recti(Math::Vec2i::ZERO, image->getSize()), color, flags);
}


void Renderer::recalculateTransform() {
    auto camera_it = std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) {
        return camera.id == m_currentCamera;
    });

    Math::Vec2 cam_position = Math::Vec2::ZERO;
    Math::Vec2 cam_zoom = Math::Vec2::ONE;
    f32 cam_rotation = 0.f;

    if (m_currentCameraActive && camera_it != m_cameras.end()) {
        cam_position = camera_it->position;
        cam_zoom = camera_it->zoom;
        cam_rotation = camera_it->rotation;
    }

    m_positionOffset = m_realPositionOffset + cam_position;
    m_rotationOffset = m_realRotationOffset + cam_rotation;
    m_scale = m_scaleFactor[0] * m_scaleFactor[1] * cam_zoom;
}
