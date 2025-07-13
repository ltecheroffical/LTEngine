#ifndef _LTENGINE_IMAGE_LEVEL_LOADER_HPP_
#define _LTENGINE_IMAGE_LEVEL_LOADER_HPP_

#include <functional>
#include <map>

#include <LTEngine/graphics/image.hpp>


namespace LTEngine {
	class LTENGINE_API ImageLevelLoader {
	public:
		ImageLevelLoader() = default;

		const static u32 TILE_NONE = std::numeric_limits<u32>().max();

		void load_level(const Graphics::Image *image);
		// Calls the specified function on every non transparent pixel
		void build_level(std::function<void(u32 x, u32 y, u32 tile)> add_obj_callback);

		void add_mapping(Graphics::Color color, u32 tile);
		void remove_mapping(Graphics::Color color);
		void clear_mappings();

		// Gets the tile specified, it is the user's job to associate tile ids with objects
		u32 get_tile(u32 x, u32 y);

	private:
		const Graphics::Image *_image = nullptr;

		std::map<Graphics::Color, u32> _tile_map;
	};
} // namespace LTEngine

#endif
