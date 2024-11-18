#pragma once

#include <LTEngine/structure/object_structure.hpp>


namespace Pong {
	class Ball : public LTEngine::Object::ObjectStructure::Object {
	public:
		Ball() = default;

		void update(f32 delta) override;
		void render(LTEngine::Rendering::Renderer *renderer) override;

		std::unique_ptr<LTEngine::Object::ObjectStructure::Object> clone() const override;

		void setVelocity(f32 x, f32 y);
		LTEngine::Math::Vec2 getVelocity() const;

		static const u32 BALL_RADIUS = 8;

	private:
		LTEngine::Math::Vec2 m_velocity = LTEngine::Math::Vec2::Zero;
	};
} // namespace Pong
