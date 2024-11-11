#include "paddle.hpp"


using namespace Pong;


Paddle::Paddle(PaddleController *controller) : m_controller(controller) {
}


void Paddle::update(f32 delta) {
    if (m_controller == nullptr) {
        return;
    }

    position.y += m_controller->getDirection() * delta * PADDLE_SPEED;
}

void Paddle::render(LTEngine::Rendering::Renderer *renderer) {
    renderer->drawRect(LTEngine::Shapes::Rect(0, 0, PADDLE_WIDTH, PADDLE_HEIGHT), LTEngine::Rendering::ColorA::WHITE, 0);
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Paddle::clone() const {
    auto paddle = std::make_unique<Paddle>(m_controller);

    paddle->position = position;
    paddle->scale = scale;
    paddle->rotation = rotation;

    return paddle;
}
