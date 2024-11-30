#include <LTEngine/engine.hpp>


using namespace LTEngine;


Engine::Engine(std::unique_ptr<Object::EngineStructure> structure) {
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
	u32 id = m_nextSceneId++;
	m_scenes[id] = m_objectStructure->clone();
	return id;
}

void Engine::loadScene(u32 id) {
	m_objectStructure = m_scenes.at(id)->clone();
}

void Engine::deleteScene(u32 id) {
	m_scenes.erase(id);
}


void Engine::update(f32 delta) {
	onUpdate(delta);
	if (m_objectStructure != nullptr) { m_objectStructure->update(delta); }
}

void Engine::render() {
	if (!m_displayInitialized) { return; }


	m_renderer->resetTransform();
	m_renderer->setZOrder(0);
	m_renderer->clearIrisMode();
	m_renderer->setOffsetsApplied();

	onRender(m_renderer);
	if (m_objectStructure != nullptr) {
		m_renderer->clear(m_objectStructure->getClearColor());
		m_objectStructure->render(m_renderer);
	}
}
