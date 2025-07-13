#include <LTEngine/graphics/3d/renderer.hpp>
#include <LTEngine/exceptions/exc_corrupt_data.hpp>

using namespace LTEngine;
using namespace LTEngine::Graphics;

void Renderer::clear(Color color) {
	clear({color.r, color.g, color.b, 255});
}

void Renderer::setPixel(Color color, Math::Vec2 position) {
	setPixel({color.r, color.g, color.b, 255}, position);
}
