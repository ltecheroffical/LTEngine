#ifndef _LTENGINE_PHYSICS_ENGINE_HPP_
#define _LTENGINE_PHYSICS_ENGINE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/circle.hpp>
#include <LTEngine/shapes/polygon.hpp>
#include <LTEngine/shapes/rect.hpp>
#include <LTEngine/shapes/triangle.hpp>

#include <LTEngine/event.hpp>


namespace LTEngine::Physics {
	class LTENGINE_API PhysicsEngine {
		// It actually quite hard to create a base class for all physics engines
	public:
		virtual ~PhysicsEngine() = default;

		Event<u32, u32> onBodyCollision;

		enum class BodyType { BODY_TYPE_STATIC = 0, BODY_TYPE_KINEMATIC = 1, BODY_TYPE_DYNAMIC = 2 };

		virtual void update(f32 timeStep) = 0;

		virtual void setGravity(const Math::Vec2 &gravity) = 0;
		virtual Math::Vec2 getGravity() const = 0;

		virtual u32 addBody(Shapes::Rect rect, BodyType bodyType) = 0;
		virtual u32 addBody(Shapes::Circle circle, BodyType bodyType) = 0;
		virtual u32 addBody(Shapes::Polygon polygon, BodyType bodyType) = 0;
		virtual u32 addBody(Shapes::Triangle triangle, BodyType bodyType) = 0;

		virtual u32 addJoint(u32 bodyIdA, u32 bodyIdB, Math::Vec2 anchorA, Math::Vec2 anchorB) = 0;

		virtual void addForce(u32 id, Math::Vec2 force) = 0;

		virtual void setJointLength(u32 id, f32 length) = 0;
		virtual void setJointSpring(u32 id, bool spring) = 0;

		virtual void disableBody(u32 id) = 0;
		virtual void enableBody(u32 id) = 0;

		virtual void removeJoint(u32 id) = 0;
		virtual void removeBody(u32 id) = 0;

		virtual void setBodyPosition(u32 id, Math::Vec2 position) = 0;
		virtual void setBodyRotation(u32 id, f32 rotation) = 0;

		virtual Math::Vec2 getJointAnchorA(u32 id) = 0;
		virtual Math::Vec2 getJointAnchorB(u32 id) = 0;

		virtual Math::Vec2 getBodyPosition(u32 id) = 0;
		virtual f32 getBodyRotation(u32 id) = 0;
	};
} // namespace LTEngine::Physics

#endif
