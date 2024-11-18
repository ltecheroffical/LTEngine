#ifndef _LTENGINE_RENDERING_FONT_HPP_
#define _LTENGINE_RENDERING_FONT_HPP_

#include <vector>

#include <stb_truetype.h>

#include <LTEngine/shapes/rect.hpp>

#include <LTEngine/rendering/image.hpp>


namespace LTEngine::Rendering {
	class Font {
	public:
		Font(std::string fontPath);
		Font(const u8 *fontData, u32 fontDataSize);
		~Font() = default;

		struct FontAtlas {
			Image atlas;
			std::vector<Shapes::Recti> charPositions;
		};

		void loadFont(std::string fontPath);
		void loadFont(const u8 *fontData, u32 fontDataSize);

		u32 getFontCount() { return m_fontCount; }

		FontAtlas getAtlas(f32 fontSize, char codePointBegin = ' ', char codePoints = 95);


	private:
		i32 m_fontCount = 0;

		std::vector<u8> m_fontData;
	};
} // namespace LTEngine::Rendering

#endif
