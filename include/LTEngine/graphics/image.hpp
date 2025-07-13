#ifndef _LTENGINE_IMAGE_HPP_
#define _LTENGINE_IMAGE_HPP_

#include <vector>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/graphics/color.hpp>


namespace LTEngine::Graphics {
	class LTENGINE_API Image {
	public:
		Image(u32 width, u32 height);
		Image(const Color *buffer, u32 width, u32 height);
		Image(const ColorA *buffer, u32 width, u32 height);
		~Image() = default;

		void set_size(u32 width, u32 height);
		Math::Vec2u get_size() const;

		void set_pixel(ColorA color, u32 x, u32 y);
		ColorA get_pixel(u32 x, u32 y) const;

		void flip_h(), flip_v();

		void load(const char *filename);
		void load(u8 *buffer, size_t size);

		const ColorA *get_mem_buffer() const {
			return _data.data();
		}
		ColorA *get_mem_buffer() {
			return _data.data();
		}

		void save_png(const char *filename) const;
		void save_bmp(const char *filename) const;
		void save_jpg(const char *filename) const;
		std::vector<u8> save_png() const;
		std::vector<u8> save_bmp() const;
		std::vector<u8> save_jpg() const;

	private:
		u32 _width, _height;

		std::vector<ColorA> _data;
	};
} // namespace LTEngine::Rendering

#endif
