#include <fstream>

#include <LTEngine/rendering/font.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


Font::Font(std::string fontPath) {
	loadFont(fontPath);
}

Font::Font(const u8 *fontData, u32 fontDataSize) {
	loadFont(fontData, fontDataSize);
}


void Font::loadFont(std::string fontPath) {
	std::ifstream fontFile(fontPath, std::ios::binary);

	fontFile.seekg(0, std::ios::end);
	u32 fileSize = fontFile.tellg();
	fontFile.seekg(0, std::ios::beg);

	std::vector<u8> fontData(fileSize);
	fontFile.read(reinterpret_cast<char *>(fontData.data()), fileSize);
	fontFile.close();

	loadFont(fontData.data(), fileSize);
}

void Font::loadFont(const u8 *fontData, u32 fontDataSize) {
	m_fontCount = stbtt_GetNumberOfFonts(fontData);
	if (m_fontCount == -1) { throw std::runtime_error("Failed to load font: Invalid font data"); }

	m_fontData.resize(fontDataSize);
	std::memcpy(m_fontData.data(), fontData, fontDataSize);
}


Font::FontAtlas Font::getAtlas(f32 fontSize, char codePointBegin, char codePoints) {
	stbtt_packedchar packedChars[codePoints];
	stbtt_aligned_quad alignedQuads[codePoints];

	stbtt_pack_context ctx;

	const u32 fontAtlasWidth = 1024;
	const u32 fontAtlasHeight = 1024;

	std::vector<u8> atlasData(fontAtlasWidth * fontAtlasHeight);

	stbtt_PackBegin(&ctx, atlasData.data(), fontAtlasWidth, fontAtlasHeight, 0, 1, nullptr);

	stbtt_PackFontRange(&ctx, m_fontData.data(), 0, fontSize, codePointBegin, codePoints, packedChars);

	stbtt_PackEnd(&ctx);

	Image fontAtlasImage(fontAtlasWidth, fontAtlasHeight);
	FontAtlas atlas = {fontAtlasImage};

	atlas.charPositions.resize(codePointBegin + codePoints, {0, 0, 0, 0});

	for (u32 i = 0; i < codePoints; i++) {
		float unusedX, unusedY;

		stbtt_GetPackedQuad(packedChars, fontAtlasWidth, fontAtlasHeight, i, &unusedX, &unusedY, &alignedQuads[i], 0);

		Shapes::Recti charPosition{0, 0, 0, 0};

		charPosition.x = packedChars[i].xoff * fontSize;
		charPosition.y = (packedChars[i].yoff + packedChars[i].y1 - packedChars[i].y0) * fontSize;

		charPosition.w = (packedChars[i].x1 - packedChars[i].x0) * fontSize;
		charPosition.h = (packedChars[i].y1 - packedChars[i].y0) * fontSize;

		charPosition.y -= charPosition.h;

		atlas.charPositions[codePointBegin + i] = charPosition;
	}

	for (u32 y = 0; y < fontAtlasHeight; y++) {
		for (u32 x = 0; x < fontAtlasWidth; x++) {
			fontAtlasImage.setPixel(ColorA(atlasData[y * fontAtlasWidth + x], atlasData[y * fontAtlasWidth + x],
			                               atlasData[y * fontAtlasWidth + x], 255),
			                        x, y);
		}
	}

	return atlas;
}
