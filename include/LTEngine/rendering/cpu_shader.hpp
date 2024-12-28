#ifndef _LTENGINE_RENDERING_CPU_SHADER_HPP_
#define _LTENGINE_RENDERING_CPU_SHADER_HPP_

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/rendering/color.hpp>


namespace LTEngine::Rendering {
	struct LTENGINE_API CPUShaderIO {
		Math::Vec2i position;
		ColorA color;

		const Color *screen;
		const Math::Vec2u screenSize;

		const ColorA *texture;
		const u32 textureWidth;
		const u32 textureHeight;
		const u32 textureX;
		const u32 textureY;

		const f32 time;


		Color getScreenColor(u32 x, u32 y) const {
			if (x < 0 || x >= screenSize.x || y < 0 || y >= screenSize.y) {
				return Color::Black;
			}
			return screen[y * screenSize.x + x];
		}

		ColorA getTextureColor(u32 x, u32 y) const {
			if (x < 0 || x >= textureWidth || y < 0 || y >= textureHeight) {
				return ColorA::Clear;
			}
			return texture[y * textureWidth + x];
		}
	};

	class LTENGINE_API CPUShader {
	public:
		virtual ~CPUShader() = 0;

		virtual void fragment(CPUShaderIO *io) = 0;
	};
} // namespace LTEngine::Rendering

#endif
