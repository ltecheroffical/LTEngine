#include "mouse.hpp"


using namespace PhysicsSimulation;


PhysicsMouse::PhysicsMouse(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Window *window)
    : m_physicsEngine(physics), m_window(window) {
	m_physicsBody = physics->addBody((LTEngine::Shapes::Circle){{0, 0}, (f32)CIRCLE_RADIUS},
	                                 LTEngine::Physics::PhysicsEngine::BodyType::BODY_TYPE_STATIC);
}

PhysicsMouse::~PhysicsMouse() {
	m_physicsEngine->removeBody(m_physicsBody);
}


void PhysicsMouse::update(f32 delta) {
	position.x = m_window->getMouseX();
	position.y = m_window->getMouseY();
	m_physicsEngine->setBodyPosition(m_physicsBody, {(f32)m_window->getMouseX(), (f32)m_window->getMouseY()});
}

void PhysicsMouse::render(LTEngine::Rendering::Renderer *renderer) {
	renderer->drawCircle({{0, 0}, (f32)CIRCLE_RADIUS}, LTEngine::Rendering::ColorA(255, 0, 0, 100));
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> PhysicsMouse::clone() const {
	return std::make_unique<PhysicsMouse>(m_physicsEngine, m_window);
}
