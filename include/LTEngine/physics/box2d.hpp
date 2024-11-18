#ifndef _LTENGINE_BOX2D_PHYSICS_ENGINE_HPP_
#define _LTENGINE_BOX2D_PHYSICS_ENGINE_HPP_

#include <unordered_map>

#include <box2d/box2d.h>

#include <LTEngine/physics/physics_engine.hpp>


namespace LTEngine::Physics {
	class Box2D : public PhysicsEngine {
	public:
		Box2D();
		~Box2D();

		void update(f32 timeStep) override;

		void setGravity(const Math::Vec2 &gravity) override;
		Math::Vec2 getGravity() const override;

		u32 addBody(Shapes::Rect rect, PhysicsEngine::BodyType bodyType) override;
		u32 addBody(Shapes::Circle circle, PhysicsEngine::BodyType bodyType) override;
		u32 addBody(Shapes::Polygon polygon, PhysicsEngine::BodyType bodyType) override;
		u32 addBody(Shapes::Triangle triangle, PhysicsEngine::BodyType bodyType) override;

		u32 addJoint(u32 bodyIdA, u32 bodyIdB, Math::Vec2 anchorA, Math::Vec2 anchorB) override;

		void addForce(u32 id, Math::Vec2 force) override;

		void setJointLength(u32 id, f32 length) override;
		void setJointSpring(u32 id, bool spring) override;

		void disableBody(u32 id) override;
		void enableBody(u32 id) override;

		void removeJoint(u32 id) override;
		void removeBody(u32 id) override;

		void setBodyPosition(u32 id, Math::Vec2 position) override;
		void setBodyRotation(u32 id, f32 rotation) override;

		Math::Vec2 getJointAnchorA(u32 id) override;
		Math::Vec2 getJointAnchorB(u32 id) override;

		Math::Vec2 getBodyPosition(u32 id) override;
		f32 getBodyRotation(u32 id) override;


	private:
		b2WorldId m_world;

		u32 m_nextId = 0;

		std::unordered_map<u32, b2BodyId> m_bodies;
		std::unordered_map<u32, b2JointId> m_joints;

		std::unordered_map<u32, b2Vec2> m_bodySizes;
	};
} // namespace LTEngine::Physics

#endif
