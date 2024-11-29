#include "floor.hpp"


using namespace PhysicsSimulation;


Floor::Floor(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Shapes::Rect rect)
    : m_size(rect.w, rect.h), m_physicsEngine(physics) {
	m_physicsBody = physics->addBody(rect, LTEngine::Physics::PhysicsEngine::BodyType::BODY_TYPE_STATIC);
}

Floor::~Floor() {
	m_physicsEngine->removeBody(m_physicsBody);
}


void Floor::setPosition(LTEngine::Math::Vec2 position) {
	m_physicsEngine->setBodyPosition(m_physicsBody, position);
	position.x = m_physicsEngine->getBodyPosition(m_physicsBody).x;
	position.y = m_physicsEngine->getBodyPosition(m_physicsBody).y;
}


void Floor::update(f32 delta) {
	position.x = m_physicsEngine->getBodyPosition(m_physicsBody).x;
	position.y = m_physicsEngine->getBodyPosition(m_physicsBody).y;
}

void Floor::render(LTEngine::Rendering::Renderer *renderer) {
	renderer->setZOrder(1);
	renderer->drawRect({0, 0, (u32)m_size.x, (u32)m_size.y}, LTEngine::Rendering::ColorA(30, 30, 30, 255));
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Floor::clone() const {
	return std::make_unique<Floor>(m_physicsEngine, (LTEngine::Shapes::Rect){position.x, position.y, (u32)m_size.x, (u32)m_size.y});
}
