#if !_LTCORE_ENGINE_HPP_ && LTCORE_COMPONENT_ENGINE_CORE
#define _LTCORE_ENGINE_HPP_

#include <LTCore/event.hpp>

#include <LTCore/structure/engine_structure.hpp>


namespace LTCore {
	class LTCORE_API Engine {
	public:
		Engine(std::unique_ptr<Object::EngineStructure> structure);
		~Engine() = default;

		Event<f32> onUpdate;
		Event<f32> onUpdatePost;
		Event<> onRender;
		Event<> onRenderPost;

		f32 timeScale = 1.f;

		/**
		 * @brief Initializes the display with the specified renderer.
		 *
		 * @details
		 * This function is used to initialize the display. Until this is called, there is no rendering, meaning that the
		 * `render()` function will return immediately. The renderer passed in will be used until the Engine is destroyed.
		 */
		void initDisplay();

		void setObjectStructure(std::unique_ptr<Object::EngineStructure> structure) {
			m_objectStructure = std::move(structure);
		}
		Object::EngineStructure *getObjectStructure() {
			return m_objectStructure.get();
		}
		void clearObjects();

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
		u32 captureScene();
		void loadScene(u32 id);
		void deleteScene(u32 id);

		void update(f32 delta);
		void render();

	private:
		bool m_displayInitialized : 1 = false;
		u32 m_nextSceneId = 0;

		std::unique_ptr<Object::EngineStructure> m_objectStructure = nullptr;

		std::unordered_map<u32, std::unique_ptr<Object::EngineStructure::EngineStructureData>> m_scenes;
	};
} // namespace LTCore

#endif
