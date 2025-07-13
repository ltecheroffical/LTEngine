#include <LTEngine/graphics/3d/renderer.hpp>
#include <LTEngine/exceptions/exc_corrupt_data.hpp>

using namespace LTEngine;
using namespace LTEngine::Graphics;

void Renderer::clear(Color color) {
	clear({color.r, color.g, color.b, 255});
}

void Renderer::set_pixel(Color color, Math::Vec2 position) {
	set_pixel({color.r, color.g, color.b, 255}, position);
}
