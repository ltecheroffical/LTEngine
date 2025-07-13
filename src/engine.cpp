#ifdef LTENGINE_COMPONENT_ENGINE_CORE
#include <LTEngine/engine.hpp>


using namespace LTEngine;


Engine::Engine(std::unique_ptr<Object::EngineStructure> structure) {
	_object_structure = std::move(structure);
}


void Engine::init_display() {
	_display_initialized = true;
}


void Engine::clear_objects() {
	_object_structure->clear();
}


u32 Engine::capture_scene() {
	u32 id = _next_scene_id++;
	_scenes[id] = _object_structure->save();
	return id;
}

void Engine::load_scene(u32 id) {
	_object_structure->load(_scenes.at(id).get());
}

void Engine::delete_scene(u32 id) {
	_scenes.erase(id);
}


void Engine::update(f32 delta) {
	on_update(delta * time_scale);
	if (_object_structure != nullptr) {
		_object_structure->update(delta * time_scale);
	}
	on_update_post(delta * time_scale);
}

void Engine::render() {
	if (!_display_initialized) {
		return;
	}


	on_render();
	if (_object_structure != nullptr) {
		_object_structure->render();
	}
	on_render_post();
}

#endif