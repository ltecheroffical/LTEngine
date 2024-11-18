#include "apple.hpp"
#include "snake.hpp"


Apple::Apple(u32 snake, LTEngine::Math::Vec2u limits) : m_snake(snake), m_posLimitX(limits.x), m_posLimitY(limits.y) {
	position.x = rand() % m_posLimitX;
	position.y = rand() % m_posLimitY;
}


void Apple::update(f32 delta) {
	const f32 eilpision = 0.9999999999999f;
	LTEngine::Math::Vec2 snakePosition = getObjectStructure()->getObject(m_snake)->position;
	if (fabs(snakePosition.x - position.x) < eilpision && fabs(snakePosition.y - position.y) < eilpision) {
		Snake *snake = dynamic_cast<Snake *>(getObjectStructure()->getObject(m_snake));
		if (snake != nullptr) { snake->grow(); }

		position.x = rand() % m_posLimitX;
		position.y = rand() % m_posLimitY;
	}
}

void Apple::render(LTEngine::Rendering::Renderer *renderer) {
	renderer->drawRect({0, 0, 1, 1}, LTEngine::Rendering::ColorA::Red, 0);
}


std::unique_ptr<LTEngine::Object::ObjectStructure::Object> Apple::clone() const {
	return std::make_unique<Apple>(m_snake, (LTEngine::Math::Vec2u){m_posLimitX, m_posLimitY});
}
