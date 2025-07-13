#ifndef _LTENGINE_PHYSICS_ENGINE_HPP_
#define _LTENGINE_PHYSICS_ENGINE_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/2d/circle.hpp>
#include <LTEngine/shapes/2d/polygon.hpp>
#include <LTEngine/shapes/2d/rect.hpp>
#include <LTEngine/shapes/2d/triangle.hpp>

#include <LTEngine/event.hpp>


namespace LTEngine::Physics {
	class LTENGINE_API PhysicsEngine2D {
		// It actually quite hard to create a base class for all physics engines
	public:
		virtual ~PhysicsEngine2D() = default;

		Event<u32, u32> on_body_collision;

		enum class BodyType { BODY_TYPE_STATIC = 0, BODY_TYPE_KINEMATIC = 1, BODY_TYPE_DYNAMIC = 2 };

		virtual void update(f32 time_step) = 0;

		virtual void set_gravity(const Math::Vec2 &gravity) = 0;
		virtual Math::Vec2 get_gravity() const = 0;

		virtual u32 add_body(Shapes::Rect rect, BodyType body_type) = 0;
		virtual u32 add_body(Shapes::Circle circle, BodyType body_type) = 0;
		virtual u32 add_body(Shapes::Polygon polygon, BodyType body_type) = 0;
		virtual u32 add_body(Shapes::Triangle triangle, BodyType body_type) = 0;

		virtual u32 add_joint(u32 body_id_a, u32 body_id_b, Math::Vec2 anchor_a, Math::Vec2 anchor_b) = 0;

		virtual void add_force(u32 id, Math::Vec2 force) = 0;

		virtual void set_joint_length(u32 id, f32 length) = 0;
		virtual void set_joint_spring(u32 id, bool spring) = 0;

		virtual void disable_body(u32 id) = 0;
		virtual void enable_body(u32 id) = 0;

		virtual void remove_joint(u32 id) = 0;
		virtual void remove_body(u32 id) = 0;

		virtual void set_body_position(u32 id, Math::Vec2 position) = 0;
		virtual void set_body_rotation(u32 id, f32 rotation) = 0;

		virtual Math::Vec2 get_joint_anchor_a(u32 id) = 0;
		virtual Math::Vec2 get_joint_anchor_b(u32 id) = 0;

		virtual Math::Vec2 get_body_position(u32 id) = 0;
		virtual f32 get_body_rotation(u32 id) = 0;
	};
} // namespace LTEngine::Physics

#endif
