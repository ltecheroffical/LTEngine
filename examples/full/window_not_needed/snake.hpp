#ifndef _SNAKE_HPP_
#define _SNAKE_HPP_

#define LTENGINE_GLOBAL_BASIC_TYPES
#include <LTEngine/structure/object_structure.hpp>


class Snake : public LTEngine::Object::ObjectStructure::Object {
public:
	enum class Direction { Up, Down, Left, Right };

	Snake(LTEngine::Math::Vec2 position);
	~Snake() override = default;

	void update(f32 delta) override;
	void render(LTEngine::Rendering::Renderer *renderer) override;

	std::unique_ptr<Object> clone() const override;

	void grow();
	void setDirection(Direction direction);


private:
	Direction m_currentDirection;
	std::vector<LTEngine::Math::Vec2> m_tail;
};

#endif
