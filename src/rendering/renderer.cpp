#include <LTEngine/rendering/renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


void Renderer::setScale(Math::Vec2 scale) {
	m_scaleFactor[0] = scale;
}


void Renderer::setZOrder(u16 z) {
	m_zOrder = z;
}


void Renderer::setRotationOffset(f32 offset) {
	m_rotationOffset = offset;
}

void Renderer::setScaleFactor(Math::Vec2 scale) {
	m_scaleFactor[1] = scale;
}

void Renderer::setPositionOffset(Math::Vec2 offset) {
	m_positionOffset = offset;
}


void Renderer::resetTransform() {
	m_positionOffset = Math::Vec2::Zero;
	m_rotationOffset = 0.f;
	m_scaleFactor[0] = Math::Vec2::One;

	m_scaleFactor[1] = Math::Vec2::One;
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
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	m_cameras.erase(it);
	cameraDestroyed(id);
}

void Renderer::setCameraPosition(u32 id, Math::Vec2 position) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	it->position = position;
}

void Renderer::setCameraRotation(u32 id, f32 rotation) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	it->rotation = rotation;
}

void Renderer::setCameraZoom(u32 id, Math::Vec2 zoom) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	it->zoom = zoom;
}

void Renderer::setCameraInclude(u32 id) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	it->exclude = false;
}

void Renderer::setCameraExclude(u32 id) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	it->exclude = true;
}

void Renderer::setCurrentCamera(u32 id) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });

	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }

	m_currentCamera = id;
	m_currentCameraActive = true;
	cameraSelected(id);
}

void Renderer::clearCurrentCamera() {
	m_currentCameraActive = false;
	cameraDeselected();
}

Math::Vec2 Renderer::getCameraPosition(u32 id) const {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	return it->position;
}

Math::Vec2 Renderer::getCameraZoom(u32 id) const {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	return it->zoom;
}

f32 Renderer::getCameraRotation(u32 id) const {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { throw std::runtime_error("Camera not found"); }
	return it->rotation;
}


void Renderer::drawTriangle(Shapes::Triangle triangle, ColorA color, RendererFlags flags) {
	if (flags & FLAG_FILL) { drawPoints({.points = {triangle.p1, triangle.p2, triangle.p3}}, color, flags); }

	drawLine(triangle.p1, triangle.p2, 1, color, flags);
	drawLine(triangle.p2, triangle.p3, 1, color, flags);
	drawLine(triangle.p3, triangle.p1, 1, color, flags);
}


void Renderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, ColorA color, RendererFlags flags) {
	drawImage(image, position, rotation, Shapes::Recti(Math::Vec2i::Zero, image->getSize()), color, flags);
}


Math::Vec2 Renderer::worldToScreenPosition(Math::Vec2 position) const {
	auto camera_it =
	    std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) { return camera.id == m_currentCamera; });

	Math::Vec2 camPosition = Math::Vec2::Zero;

	if (m_currentCameraActive && camera_it != m_cameras.end()) { camPosition = camera_it->position; }

	return position * (m_offsetsApplied ? m_scaleFactor[0] : Math::Vec2::One) +
	       (m_offsetsApplied ? m_positionOffset : Math::Vec2::Zero) - camPosition;
}

Math::Vec2i Renderer::worldToScreenPosition(Math::Vec2i position) const {
	Math::Vec2 screenPosition = worldToScreenPosition(Math::Vec2(position.x, position.y));
	return Math::Vec2i(screenPosition.x, screenPosition.y);
}

void Renderer::worldToScreenPosition(f32 *x, f32 *y) const {
	Math::Vec2 position = worldToScreenPosition(Math::Vec2(*x, *y));
	*x = position.x;
	*y = position.y;
}

void Renderer::worldToScreenPosition(i32 *x, i32 *y) const {
	Math::Vec2 position = worldToScreenPosition(Math::Vec2(*x, *y));
	*x = position.x;
	*y = position.y;
}

f32 Renderer::worldToScreenRotation(f32 rotation) const {
	auto camera_it =
	    std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) { return camera.id == m_currentCamera; });

	f32 camRotation = 0.f;

	if (m_currentCameraActive && camera_it != m_cameras.end()) { camRotation = camera_it->rotation; }

	return rotation + (m_offsetsApplied ? m_rotationOffset : 0.f) - camRotation;
}

void Renderer::worldToScreenRotation(f32 *rotation) const {
	*rotation = worldToScreenRotation(*rotation);
}


Math::Vec2 Renderer::screenToWorldPosition(Math::Vec2 position) const {
	auto camera_it =
	    std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) { return camera.id == m_currentCamera; });

	Math::Vec2 camPosition = Math::Vec2::Zero;

	if (m_currentCameraActive && camera_it != m_cameras.end()) { camPosition = camera_it->position; }

	return position -
	       (m_offsetsApplied ? m_positionOffset : Math::Vec2::Zero) / (m_offsetsApplied ? m_scaleFactor[0] : Math::Vec2::One) +
	       camPosition;
}

void Renderer::screenToWorldPosition(f32 *x, f32 *y) const {
	Math::Vec2 position = screenToWorldPosition(Math::Vec2(*x, *y));
	*x = position.x;
	*y = position.y;
}

f32 Renderer::screenToWorldRotation(f32 rotation) const {
	auto camera_it =
	    std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) { return camera.id == m_currentCamera; });

	f32 camRotation = 0.f;

	if (m_currentCameraActive && camera_it != m_cameras.end()) { camRotation = camera_it->rotation; }

	return rotation - (m_offsetsApplied ? m_rotationOffset : 0.f) + camRotation;
}

void Renderer::screenToWorldRotation(f32 *rotation) const {
	*rotation = screenToWorldRotation(*rotation);
}


Math::Vec2 Renderer::getWorldScale() const {
	auto camera_it =
	    std::find_if(m_cameras.begin(), m_cameras.end(), [this](const Camera &camera) { return camera.id == m_currentCamera; });

	Math::Vec2 camZoom = Math::Vec2::One;

	if (m_currentCameraActive && camera_it != m_cameras.end()) { camZoom = camera_it->zoom; }

	return m_scaleFactor[0] / (m_offsetsApplied ? m_scaleFactor[1] : Math::Vec2::One) / camZoom;
}


Camera *Renderer::getCameraById(u32 id) {
	auto it = std::find_if(m_cameras.begin(), m_cameras.end(), [id](const Camera &camera) { return camera.id == id; });
	if (it == m_cameras.end()) { return nullptr; }
	return &(*it);
}
