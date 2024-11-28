#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

#define LTENGINE_GLOBAL_BASIC_TYPES

#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/physics/physics_engine.hpp>


namespace PhysicsSimulation {
	class Square : public LTEngine::Object::ObjectStructure::Object {
	public:
		Square(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Rendering::ColorA color, f32 x, f32 y);
		~Square();

		void update(f32 delta) override;
		void render(LTEngine::Rendering::Renderer *renderer) override;

		std::unique_ptr<LTEngine::Object::ObjectStructure::Object> clone() const override;

		void setPosition(LTEngine::Math::Vec2 position) override;
		void setRotation(f32 rotation) override;

	private:
		const u32 BOX_WIDTH = 5;
		const u32 BOX_HEIGHT = 5;

		LTEngine::Physics::PhysicsEngine *m_physicsEngine;
		u32 m_physicsBody;

		LTEngine::Rendering::ColorA m_color;
	};
} // namespace PhysicsSimulation

#endif
