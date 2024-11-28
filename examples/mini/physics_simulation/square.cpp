#include "square.hpp"


using namespace PhysicsSimulation;


Square::Square(LTEngine::Physics::PhysicsEngine *physics, LTEngine::Rendering::ColorA color, f32 x, f32 y)
    : m_physicsEngine(physics), m_color(color) {
	m_physicsBody = physics->addBody({x, y, BOX_WIDTH, BOX_HEIGHT}, LTEngine::Physics::PhysicsEngine::BodyType::BODY_TYPE_DYNAMIC);
}

Square::~Square() {
	m_physicsEngine->removeBody(m_physicsBody);
}


void Square::update(f32 delta) {
	position.x = m_physicsEngine->getBodyPosition(m_physicsBody).x;
	position.y = m_physicsEngine->getBodyPosition(m_physicsBody).y;
	rotation = m_physicsEngine->getBodyRotation(m_physicsBody);
}

void Square::render(LTEngine::Rendering::Renderer *renderer) {
	renderer->drawRect({0, 0, BOX_WIDTH, BOX_HEIGHT}, m_color, 0);
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Square::clone() const {
	return std::make_unique<Square>(m_physicsEngine, m_color, position.x, position.y);
}


void Square::setPosition(LTEngine::Math::Vec2 position) {
	m_physicsEngine->setBodyPosition(m_physicsBody, position);
}

void Square::setRotation(f32 rotation) {
	m_physicsEngine->setBodyRotation(m_physicsBody, rotation);
}
