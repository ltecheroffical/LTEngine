#ifndef _APPLE_HPP_
#define _APPLE_HPP_

#define LTENGINE_GLOBAL_BASIC_TYPES
#include <LTEngine/structure/object_structure.hpp>


class Apple : public LTEngine::Object::ObjectStructure::Object {
public:
	Apple(u32 snake, LTEngine::Math::Vec2u limits);
	~Apple() override = default;

	void update(f32 delta) override;
	void render(LTEngine::Rendering::Renderer *renderer) override;

	std::unique_ptr<Object> clone() const override;

private:
	u32 m_snake;

	u32 m_posLimitX;
	u32 m_posLimitY;
};

#endif
