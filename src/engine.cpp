#include <LTEngine/engine.hpp>


using namespace LTEngine;


Engine::Engine(const Object::ObjectStructure *structure) {
    m_displayInitialized = false;
    m_objectStructure = structure->clone();
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
    m_scenes.push_back(*m_objectStructure->clone());
    return index;
}

void Engine::loadScene(u32 id) {
    m_objectStructure = m_scenes.at(id).clone();
}

void Engine::deleteScene(u32 id) {
    m_scenes.erase(m_scenes.begin() + id);
}


void Engine::update(f32 delta) {
    if (m_objectStructure.get() == nullptr) {
        return;
    }
    m_objectStructure->update(delta);
}

void Engine::render() {
    if (m_objectStructure.get() == nullptr) {
        return;
    }
    if (!m_displayInitialized) {
        return;
    }
    m_objectStructure->render(m_renderer);
}
