#if !_LTENGINE_BOX2D_PHYSICS_ENGINE_HPP_ && LTENGINE_COMPONENT_PHYSICS_BOX2D
#define _LTENGINE_BOX2D_PHYSICS_ENGINE_HPP_

#include <unordered_map>

#include <box2d/box2d.h>

#include <LTEngine/physics/physics_engine_2d.hpp>


namespace LTEngine::Physics {
	class LTENGINE_API Box2D : public PhysicsEngine2D {
	public:
		Box2D();
		~Box2D();

		void update(f32 time_step) override;

		void set_gravity(const Math::Vec2 &gravity) override;
		Math::Vec2 get_gravity() const override;

		u32 add_body(Shapes::Rect rect, PhysicsEngine2D::BodyType body_type) override;
		u32 add_body(Shapes::Circle circle, PhysicsEngine2D::BodyType body_type) override;
		u32 add_body(Shapes::Polygon polygon, PhysicsEngine2D::BodyType body_type) override;
		u32 add_body(Shapes::Triangle triangle, PhysicsEngine2D::BodyType body_type) override;

		u32 add_joint(u32 body_id_a, u32 body_id_b, Math::Vec2 anchor_a, Math::Vec2 anchor_b) override;

		void add_force(u32 id, Math::Vec2 force) override;

		void set_joint_length(u32 id, f32 length) override;
		void set_joint_spring(u32 id, bool spring) override;

		void disable_body(u32 id) override;
		void enable_body(u32 id) override;

		void remove_joint(u32 id) override;
		void remove_body(u32 id) override;

		void set_body_position(u32 id, Math::Vec2 position) override;
		void set_body_rotation(u32 id, f32 rotation) override;

		Math::Vec2 get_joint_anchor_a(u32 id) override;
		Math::Vec2 get_joint_anchor_b(u32 id) override;

		Math::Vec2 get_body_position(u32 id) override;
		f32 get_body_rotation(u32 id) override;


	private:
		b2WorldId _world;

		u32 _next_id = 0;

		std::unordered_map<u32, b2BodyId> _bodies;
		std::unordered_map<u32, b2JointId> _joints;

		std::unordered_map<u32, b2Vec2> _body_sizes;
	};
} // namespace LTEngine::Physics

#endif
