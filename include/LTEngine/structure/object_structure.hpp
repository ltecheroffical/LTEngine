#pragma once

#include <LTEngine/structure/engine_structure.hpp>


namespace LTEngine::Object {
    class ObjectStructure : public EngineStructure {
    public:
        ObjectStructure();
        ~ObjectStructure() override = default;
        
        class Object {
        public:
            virtual ~Object() = default;

            Math::Vec2 position = Math::Vec2::ZERO;
            Math::Vec2 scale = Math::Vec2::ONE;
            f32 rotation = 0.f;

            virtual void update(f32 delta) = 0;
            virtual void render(LTEngine::Rendering::Renderer *renderer) = 0;

            virtual std::unique_ptr<Object> clone() const = 0;
            std::unique_ptr<Object> clone(u32 id) const;

            bool isActive() const;
            bool isVisible() const;

            void setActive(bool active);
            void setVisible(bool visible);

            u32 getId() const;
            void setId(u32 id);

        private:
            bool m_active = true;
            bool m_visible = true;

            u32 m_id = 0;
            bool m_idSet = false;
        };

        void update(f32 delta) override;
        void render(LTEngine::Rendering::Renderer *renderer) override;

        std::unique_ptr<EngineStructure> clone() const override;
        void clear() override;

        void setClearColor(Rendering::Color color);

        u32 addObject(std::unique_ptr<Object> object);
        u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position);
        u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation);
        u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, Math::Vec2 scale);
        u32 addObject(std::unique_ptr<Object> object, Math::Vec2 position, f32 rotation, Math::Vec2 scale);
        void removeObject(u32 id);
        Object *getObject(u32 id); 

    private:
        std::vector<std::unique_ptr<Object>> m_objects;

        u32 m_nextId;
    };
}
