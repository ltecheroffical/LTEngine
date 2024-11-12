#include <unordered_map>

#include <box2d/box2d.h>

#include <LTEngine/physics/physics_engine.hpp>


namespace LTEngine::Physics {
    class Box2D : public PhysicsEngine {
    public:
        Box2D();
        ~Box2D();

        void update(f32 timeStep) override;

        void setGravity(const Math::Vec2& gravity) override;
        Math::Vec2 getGravity() const override;

        u32 addBody(Shapes::Rect rect, PhysicsEngine::BodyType bodyType) override;
        u32 addBody(Shapes::Circle circle, PhysicsEngine::BodyType bodyType) override;
        u32 addBody(Shapes::Polygon polygon, PhysicsEngine::BodyType bodyType) override;
        u32 addBody(Shapes::Triangle triangle, PhysicsEngine::BodyType bodyType) override;

        void removeBody(u32 id) override;

        void setBodyPosition(u32 id, const Math::Vec2 &position) override;
        void setBodyRotation(u32 id, f32 rotation) override;

        Math::Vec2 getBodyPosition(u32 id) override;
        f32 getBodyRotation(u32 id) override;


    private:
        b2WorldId m_world;

        u32 m_nextId = 0;

        std::unordered_map<u32, b2BodyId> m_bodies;
        std::unordered_map<u32, b2Vec2> m_bodySizes;
    };
}
