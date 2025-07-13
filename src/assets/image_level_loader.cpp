#include <LTEngine/assets/image_level_loader.hpp>


using namespace LTEngine;


void ImageLevelLoader::load_level(const Graphics::Image *image) {
	_image = image;
}

void ImageLevelLoader::build_level(std::function<void(u32 x, u32 y, u32 tile)> add_obj_callback) {
	if (_image == nullptr) { throw std::runtime_error("No level loaded!"); }
	for (u32 y = 0; y < _image->get_size().x; y++) {
		for (u32 x = 0; x < _image->get_size().y; x++) {
			if (get_tile(x, y) == TILE_NONE) { continue; }
			add_obj_callback(x, y, get_tile(x, y));
		}
	}
}


void ImageLevelLoader::add_mapping(Graphics::Color color, u32 tile) {
	_tile_map[color] = tile;
}

void ImageLevelLoader::remove_mapping(Graphics::Color color) {
	_tile_map.erase(color);
}

void ImageLevelLoader::clear_mappings() {
	_tile_map.clear();
}


u32 ImageLevelLoader::get_tile(u32 x, u32 y) {
	if (_image == nullptr) { throw std::runtime_error("No level loaded!"); }
	if (_image->get_pixel(x, y).a == 0) { return TILE_NONE; }
	if (!_tile_map.contains(_image->get_pixel(x, y))) { return TILE_NONE; }
	return _tile_map[_image->get_pixel(x, y)];
}
