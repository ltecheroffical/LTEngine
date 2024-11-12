#include "snake.hpp"


Snake::Snake(LTEngine::Math::Vec2 position) : m_currentDirection(Direction::Down) {
    this->position = position;
}


void Snake::update(f32 delta) {
    LTEngine::Math::Vec2 direction = LTEngine::Math::Vec2::ZERO;

    switch (m_currentDirection) {
        case Direction::Up:
            direction.y -= delta;
            break;
        case Direction::Down:
            direction.y += delta;
            break;
        case Direction::Left:
            direction.x -= delta;
            break;
        case Direction::Right:
            direction.x += delta;
            break;
    }

    // Make tail follow
    if (m_tail.size() > 0) {
        m_tail.erase(m_tail.begin());
        m_tail.push_back(position);
    }

    position += direction;

    for (u32 i = 0; i < m_tail.size(); i++) {
        const f32 eilpision = 0.1f;
        if (fabs(m_tail[i].x - position.x) < eilpision && fabs(m_tail[i].y - position.y) < eilpision) {
            // Snake bit it's tail off
            m_tail.erase(m_tail.begin() + i);
            break;
        }
    }
}

void Snake::render(LTEngine::Rendering::Renderer *renderer) {
    renderer->drawRect({0, 0, 1, 1}, LTEngine::Rendering::ColorA::BLUE, 0);
    renderer->clearOffsetsApplied();
    for (LTEngine::Math::Vec2 tail : m_tail) {
        renderer->drawRect({tail.x, tail.y, 1, 1}, LTEngine::Rendering::ColorA::GREEN, 0);
    }
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Snake::clone() const {
    return std::make_unique<Snake>(position);
}


void Snake::grow() {
    m_tail.push_back(position);
}

void Snake::setDirection(Direction direction) {
    m_currentDirection = direction;
}
