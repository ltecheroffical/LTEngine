#pragma once

#include <LTEngine/timer.hpp>

#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/physics/physics_engine.hpp>


namespace PhysicsSimulation {
    class ObjectSpawner : public LTEngine::Object::ObjectStructure::Object {
    public:
        ObjectSpawner(LTEngine::Physics::PhysicsEngine *physics);
        ~ObjectSpawner();

        void update(f32 delta) override;
        void render(LTEngine::Rendering::Renderer *renderer) override;

        std::unique_ptr<LTEngine::Object::ObjectStructure::Object> clone() const override;

        void setSpawnAreaWidth(u32 width) { m_spawnAreaWidth = width; }

    private:
        const f32 SPAWN_INTERVAL = 0.1f;
        const f32 OBJECT_DESTROY_TIMER = 60.f;

        std::vector<u32> m_objects;
        std::unordered_map<u32, LTEngine::Timer> m_objectTimers;

        LTEngine::Physics::PhysicsEngine *m_physicsEngine;

        LTEngine::Timer m_spawnTimer;
        u32 m_spawnAreaWidth;
    };
}
