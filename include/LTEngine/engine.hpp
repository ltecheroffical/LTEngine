#pragma once

#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine {
    class Engine {
    public:
        Engine(const Object::ObjectStructure *structure);
        ~Engine() = default;

        void initDisplay(Rendering::Renderer *renderer);

        void clearObjects();

        u32 captureScene();
        void loadScene(u32 id);
        void deleteScene(u32 id);

        void update(f32 delta);
        void render();

    private:
        bool m_displayInitialized:1;

        Rendering::Renderer *m_renderer;
        
        std::unique_ptr<Object::ObjectStructure> m_objectStructure;
        std::vector<std::unique_ptr<Object::ObjectStructure>> m_scenes;
    };
}
