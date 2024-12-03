#ifndef _LTENGINE_IMAGE_HPP_
#define _LTENGINE_IMAGE_HPP_

#include <vector>

#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/rendering/color.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Rendering {
	class LTENGINE_API Image {
	public:
		Image(u32 width, u32 height);
		Image(const Color *buffer, u32 width, u32 height);
		Image(const ColorA *buffer, u32 width, u32 height);
		~Image() = default;

		void setSize(u32 width, u32 height);
		Math::Vec2u getSize() const;

		void setPixel(ColorA color, u32 x, u32 y);
		ColorA getPixel(u32 x, u32 y) const;

		void flipH(), flipV();

		void load(const char *filename);
		void load(u8 *buffer, u32 size);

		const ColorA *getMemBuffer() const { return m_data.data(); }
		ColorA *getMemBuffer() { return m_data.data(); }

		void savePNG(const char *filename) const;
		void saveBMP(const char *filename) const;
		void saveJPG(const char *filename) const;
		std::vector<u8> savePNG() const;
		std::vector<u8> saveBMP() const;
		std::vector<u8> saveJPG() const;

	private:
		u32 m_width, m_height;

		std::vector<ColorA> m_data;
	};
} // namespace LTEngine::Rendering

#endif
