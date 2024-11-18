#ifndef _LTENGINE_IMAGE_LEVEL_LOADER_HPP_
#define _LTENGINE_IMAGE_LEVEL_LOADER_HPP_

#include <map>

#include <LTEngine/rendering/image.hpp>


namespace LTEngine {
	class ImageLevelLoader {
	public:
		ImageLevelLoader() = default;

		const static u32 TILE_NONE = 0;

		void loadLevel(const Rendering::Image *image);
		void buildLevel(void (*addObjCallback)(u32 x, u32 y, u32 tile));

		void addMapping(Rendering::Color color, u32 tile);
		void removeMapping(Rendering::Color color);
		void clearMappings();

		u32 getTile(u32 x, u32 y);

	private:
		const Rendering::Image *m_image = nullptr;

		std::map<Rendering::Color, u32> m_tileMap;
	};
} // namespace LTEngine

#endif
