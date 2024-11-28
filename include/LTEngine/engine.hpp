#ifndef _LTENGINE_ENGINE_HPP_
#define _LTENGINE_ENGINE_HPP_

#include <LTEngine/event.hpp>

#include <LTEngine/structure/engine_structure.hpp>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine {
	class Engine {
	public:
		Engine(std::unique_ptr<Object::EngineStructure> structure);
		~Engine() = default;

		Event<f32> onUpdate;
		Event<Rendering::Renderer *> onRender;


		void initDisplay(Rendering::Renderer *renderer);
		Rendering::Renderer *getRenderer() { return m_renderer; }

		Object::EngineStructure *getObjectStructure() { return m_objectStructure.get(); }
		void clearObjects();

		u32 captureScene();
		void loadScene(u32 id);
		void deleteScene(u32 id);

		void update(f32 delta);
		void render();

	private:
		bool m_displayInitialized : 1 = false;

		Rendering::Renderer *m_renderer;

		std::unique_ptr<Object::EngineStructure> m_objectStructure = nullptr;

		std::vector<std::unique_ptr<Object::EngineStructure>> m_scenes;
	};
} // namespace LTEngine

#endif
