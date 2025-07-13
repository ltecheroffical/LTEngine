#if !_LTENGINE_ENGINE_HPP_ && LTENGINE_COMPONENT_ENGINE_CORE
#define _LTENGINE_ENGINE_HPP_

#include <LTEngine/event.hpp>

#include <LTEngine/structure/engine_structure.hpp>


namespace LTEngine {
	class LTENGINE_API Engine {
	public:
		Engine(std::unique_ptr<Object::EngineStructure> structure);
		~Engine() = default;

		Event<f32> on_update;
		Event<f32> on_update_post;
		Event<> on_render;
		Event<> on_render_post;

		f32 time_scale = 1.f;

		/**
		 * @brief Initializes the display with the specified renderer.
		 *
		 * @details
		 * This function is used to initialize the display. Until this is called, there is no rendering, meaning that the
		 * `render()` function will return immediately. The renderer passed in will be used until the Engine is destroyed.
		 */
		void init_display();

		void set_object_structure(std::unique_ptr<Object::EngineStructure> structure) {
			_object_structure = std::move(structure);
		}
		Object::EngineStructure *get_object_structure() {
			return _object_structure.get();
		}
		void clear_objects();

		/**
		 * @brief Captures the current scene and returns its ID to load it later.
		 *
		 * @details
		 * This function captures the current scene and returns its ID to load it later.
		 * This is the same as scene management in other engines. This method is more powerful however because
		 * a scene is just an `EngineStructure` meaning for example, in one scene you can use ECS, in another you can use Objects,
		 * and in another you can use a custom `EngineStructure` for that scene (e.g Menu).
		 *
		 * Whats powering the scene capturing? It's the clone function specified by the engine structure.
		 */
		u32 capture_scene();
		void load_scene(u32 id);
		void delete_scene(u32 id);

		void update(f32 delta);
		void render();

	private:
		bool _display_initialized : 1 = false;
		u32 _next_scene_id = 0;

		std::unique_ptr<Object::EngineStructure> _object_structure = nullptr;

		std::unordered_map<u32, std::unique_ptr<Object::EngineStructure::EngineStructureData>> _scenes;
	};
} // namespace LTEngine

#endif
