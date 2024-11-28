#ifndef _FLOOR_HPP_
#define _FLOOR_HPP_

#define LTENGINE_GLOBAL_BASIC_TYPES

#include <LTEngine/physics/physics_engine.hpp>

#include <LTEngine/structure/object_structure.hpp>


namespace PhysicsSimulation {
	class Floor : public LTEngine::Object::ObjectStructure::Object {
	public:
		Floor(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Shapes::Rect rect);
		~Floor();

		void setPosition(LTEngine::Math::Vec2 position) override;

		void update(f32 delta) override;
		void render(LTEngine::Rendering::Renderer *renderer) override;

		std::unique_ptr<LTEngine::Object::ObjectStructure::Object> clone() const override;

	private:
		LTEngine::Physics::PhysicsEngine *m_physicsEngine;
		u32 m_physicsBody;

		LTEngine::Math::Vec2 m_size;
	};
} // namespace PhysicsSimulation

#endif
