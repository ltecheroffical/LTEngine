#ifdef LTENGINE_COMPONENT_ENGINE_CORE
#include <LTEngine/engine.hpp>


using namespace LTEngine;


Engine::Engine(std::unique_ptr<Object::EngineStructure> structure) {
	m_objectStructure = std::move(structure);
}


void Engine::initDisplay() {
	m_displayInitialized = true;
}


void Engine::clearObjects() {
	m_objectStructure->clear();
}


u32 Engine::captureScene() {
	u32 id = m_nextSceneId++;
	m_scenes[id] = m_objectStructure->save();
	return id;
}

void Engine::loadScene(u32 id) {
	m_objectStructure->load(m_scenes.at(id).get());
}

void Engine::deleteScene(u32 id) {
	m_scenes.erase(id);
}


void Engine::update(f32 delta) {
	onUpdate(delta * timeScale);
	if (m_objectStructure != nullptr) {
		m_objectStructure->update(delta * timeScale);
	}
	onUpdatePost(delta * timeScale);
}

void Engine::render() {
	if (!m_displayInitialized) {
		return;
	}


	onRender();
	if (m_objectStructure != nullptr) {
		m_objectStructure->render();
	}
	onRenderPost();
}

#endif