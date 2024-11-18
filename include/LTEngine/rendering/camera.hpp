#ifndef _LTENGINE_RENDERING_CAMERA_HPP_
#define _LTENGINE_RENDERING_CAMERA_HPP_

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
	struct Camera {
		Math::Vec2 position = Math::Vec2::Zero;
		Math::Vec2 zoom = Math::Vec2::One;
		f32 rotation = 0.f;

		bool exclude : 1;

		u32 id;
	};
} // namespace LTEngine::Rendering

#endif
