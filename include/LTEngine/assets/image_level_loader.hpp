#ifndef _LTENGINE_IMAGE_LEVEL_LOADER_HPP_
#define _LTENGINE_IMAGE_LEVEL_LOADER_HPP_

#include <functional>
#include <map>

#include <LTEngine/rendering/image.hpp>


namespace LTEngine {
	class LTENGINE_API ImageLevelLoader {
	public:
		ImageLevelLoader() = default;

		const static u32 TILE_NONE = std::numeric_limits<u32>().max();

		void loadLevel(const Rendering::Image *image);
		// Calls the specified function on every non transparent pixel
		void buildLevel(std::function<void(u32 x, u32 y, u32 tile)> addObjCallback);

		void addMapping(Rendering::Color color, u32 tile);
		void removeMapping(Rendering::Color color);
		void clearMappings();

		// Gets the tile specified, it is the user's job to associate tile ids with objects
		u32 getTile(u32 x, u32 y);

	private:
		const Rendering::Image *m_image = nullptr;

		std::map<Rendering::Color, u32> m_tileMap;
	};
} // namespace LTEngine

#endif
