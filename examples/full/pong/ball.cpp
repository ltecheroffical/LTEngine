#include "ball.hpp"


using namespace Pong;


void Ball::update(f32 delta) {
	position.x += m_velocity.x;
	position.y += m_velocity.y;
}

void Ball::render(LTEngine::Rendering::Renderer *renderer) {
	renderer->drawCircle({LTEngine::Shapes::Shape(0, 0), BALL_RADIUS}, LTEngine::Rendering::ColorA::White,
	                     LTEngine::Rendering::Renderer::FLAG_FILL);
}

std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Ball::clone() const {
	auto ball = std::make_unique<Ball>();

	ball->position = position;
	ball->scale = scale;
	ball->rotation = rotation;

	ball->setVelocity(m_velocity.x, m_velocity.y);

	return ball;
}


void Ball::setVelocity(f32 x, f32 y) {
	m_velocity.x = x;
	m_velocity.y = y;
}

LTEngine::Math::Vec2 Ball::getVelocity() const {
	return m_velocity;
}
