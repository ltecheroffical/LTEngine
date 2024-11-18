#include <LTEngine/engine.hpp>


using namespace LTEngine;


Engine::Engine(std::unique_ptr<Object::EngineStructure> structure) {
	m_objectStructure = std::move(structure);
}

Engine::Engine(std::function<void(f32 delta)> update, std::function<void(Rendering::Renderer *renderer)> render) {
	m_updateFunc = update;
	m_renderFunc = render;
}

Engine::Engine(std::function<void(f32 delta)> update, std::function<void(Rendering::Renderer *renderer)> render,
               std::unique_ptr<Object::EngineStructure> structure) {
	m_updateFunc = update;
	m_renderFunc = render;
	m_objectStructure = std::move(structure);
}


void Engine::initDisplay(Rendering::Renderer *renderer) {
	m_renderer = renderer;
	m_displayInitialized = true;
}


void Engine::clearObjects() {
	m_objectStructure->clear();
}


u32 Engine::captureScene() {
	u32 index = m_scenes.size();
	m_scenes.push_back(m_objectStructure->clone());
	return index;
}

void Engine::loadScene(u32 id) {
	m_objectStructure = m_scenes.at(id)->clone();
}

void Engine::deleteScene(u32 id) {
	m_scenes.erase(m_scenes.begin() + id);
}


void Engine::update(f32 delta) {
	if (m_updateFunc != nullptr) { m_updateFunc(delta); }
	if (m_objectStructure != nullptr) { m_objectStructure->update(delta); }
}

void Engine::render() {
	if (!m_displayInitialized) { return; }

	if (m_renderFunc != nullptr) { m_renderFunc(m_renderer); }
	if (m_objectStructure != nullptr) {
		m_renderer->clear(m_objectStructure->getClearColor());
		m_objectStructure->render(m_renderer);
	}
}
