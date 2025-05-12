#ifndef _LTCORE_IMAGE_LEVEL_LOADER_HPP_
#define _LTCORE_IMAGE_LEVEL_LOADER_HPP_

#include <functional>
#include <map>

#include <LTCore/graphics/image.hpp>


namespace LTCore {
	class LTCORE_API ImageLevelLoader {
	public:
		ImageLevelLoader() = default;

		const static u32 TILE_NONE = std::numeric_limits<u32>().max();

		void loadLevel(const Graphics::Image *image);
		// Calls the specified function on every non transparent pixel
		void buildLevel(std::function<void(u32 x, u32 y, u32 tile)> addObjCallback);

		void addMapping(Graphics::Color color, u32 tile);
		void removeMapping(Graphics::Color color);
		void clearMappings();

		// Gets the tile specified, it is the user's job to associate tile ids with objects
		u32 getTile(u32 x, u32 y);

	private:
		const Graphics::Image *m_image = nullptr;

		std::map<Graphics::Color, u32> m_tileMap;
	};
} // namespace LTCore

#endif
