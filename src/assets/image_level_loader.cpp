#include <LTEngine/assets/image_level_loader.hpp>


using namespace LTEngine;


void ImageLevelLoader::loadLevel(const Rendering::Image *image) {
    m_image = image;
}

void ImageLevelLoader::buildLevel(void (*addObjCallback)(u32 x, u32 y, u32 tile)) {
    if (m_image == nullptr) {
        throw std::runtime_error("No level loaded!");
    }
    for (u32 y = 0; y < m_image->getSize().x; y++) {
        for (u32 x = 0; x < m_image->getSize().y; x++) {
            if (getTile(x, y) == TILE_NONE) {
                continue;
            }
            addObjCallback(x, y, getTile(x, y));
        }
    }
}


void ImageLevelLoader::addMapping(Rendering::Color color, u32 tile) {
    m_tileMap[color] = tile;
}

void ImageLevelLoader::removeMapping(Rendering::Color color) {
    m_tileMap.erase(color);
}

void ImageLevelLoader::clearMappings() {
    m_tileMap.clear();
}


u32 ImageLevelLoader::getTile(u32 x, u32 y) {
    if (m_image == nullptr) {
        throw std::runtime_error("No level loaded!");
    }
    if (m_image->getPixel(x, y).a == 0) {
        return TILE_NONE;
    }
    if (!m_tileMap.contains(m_image->getPixel(x, y))) {
        return TILE_NONE;
    }
    return m_tileMap[m_image->getPixel(x, y)];
}
