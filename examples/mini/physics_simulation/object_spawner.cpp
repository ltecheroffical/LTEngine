#include "object_spawner.hpp"

#include "square.hpp"


using namespace PhysicsSimulation;


ObjectSpawner::ObjectSpawner(LTEngine::Physics::PhysicsEngine *physics) : m_physicsEngine(physics) {
    srand(time(nullptr));
    m_spawnTimer.start(SPAWN_INTERVAL);
    m_spawnTimer.setRepeat(true);
    m_spawnTimer.setCallback([this]() {
        LTEngine::Rendering::ColorA randomColor = LTEngine::Rendering::ColorA(
            rand() % 256,
            rand() % 256,
            rand() % 256, 255);
        i32 spawnPositionX = rand() % (i32)(m_spawnAreaWidth + 1 - position.x) + (i32)position.x;

        const u32 object = getObjectStructure()->addObject(
            std::make_unique<Square>(
                m_physicsEngine,
                randomColor,
                spawnPositionX,
                position.y
            )
        );
        m_objects.push_back(object); 
        m_objectTimers[object].setCallback([this, object]() {
            getObjectStructure()->removeObject(object);
            
            auto it = std::find(m_objects.begin(), m_objects.end(), object);
            if (it != m_objects.end()) {
                m_objects.erase(it);
            }
            m_objectTimers.erase(object);
        });
        m_objectTimers[object].start(OBJECT_DESTROY_TIMER);
    });
}

ObjectSpawner::~ObjectSpawner() {
    m_spawnTimer.stop();
    for (u32 object : m_objects) {
        getObjectStructure()->removeObject(object);
    }
    m_objects.clear();
    m_objectTimers.clear();
}


void ObjectSpawner::update(f32 delta) {
    for (u32 i = 0; i < m_objects.size(); i++) {
        if (getObjectStructure()->getObject(m_objects[i]) == nullptr) {
            // Object doesn't exist anymore
            m_objects.erase(m_objects.begin() + i);
            m_objectTimers[i].stop();
            m_objectTimers.erase(i);
            continue;
        }

        m_objectTimers[m_objects[i]].step(delta); // Could destroy some objects
    }
    m_spawnTimer.step(delta);
}

void ObjectSpawner::render(LTEngine::Rendering::Renderer *renderer) {}

std::unique_ptr<LTEngine::Object::ObjectStructure::Object> ObjectSpawner::clone() const {
    return std::make_unique<ObjectSpawner>(m_physicsEngine);
}
