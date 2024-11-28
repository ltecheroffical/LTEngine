#ifndef _MOUSE_HPP_
#define _MOUSE_HPP_

#define LTENGINE_GLOBAL_BASIC_TYPES


#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/physics/physics_engine.hpp>

#include <LTEngine/window.hpp>


namespace PhysicsSimulation {
	class PhysicsMouse : public LTEngine::Object::ObjectStructure::Object {
	public:
		PhysicsMouse(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Window *window);
		~PhysicsMouse();

		void update(f32 delta) override;
		void render(LTEngine::Rendering::Renderer *renderer) override;

		std::unique_ptr<LTEngine::Object::ObjectStructure::Object> clone() const override;

	private:
		const u32 CIRCLE_RADIUS = 50;

		LTEngine::Physics::PhysicsEngine *m_physicsEngine;

		LTEngine::Window *m_window;
		u32 m_physicsBody;
	};
} // namespace PhysicsSimulation

#endif
