
#include <LTEngine/graphics/color.hpp>

namespace LTEngine::Graphics {
	const Color Color::BLACK = Color(0, 0, 0);
	const Color Color::WHITE = Color(255, 255, 255);
	const Color Color::RED = Color(255, 0, 0);
	const Color Color::GREEN = Color(0, 255, 0);
	const Color Color::BLUE = Color(0, 0, 255);
	const Color Color::YELLOW = Color(255, 255, 0);
	const Color Color::CYAN = Color(0, 255, 255);
	
	const ColorA ColorA::BLACK = ColorA(0, 0, 0, 255);
	const ColorA ColorA::WHITE = ColorA(255, 255, 255, 255);
	const ColorA ColorA::RED = ColorA(255, 0, 0, 255);
	const ColorA ColorA::GREEN = ColorA(0, 255, 0, 255);
	const ColorA ColorA::BLUE = ColorA(0, 0, 255, 255);
	const ColorA ColorA::YELLOW = ColorA(255, 255, 0, 255);
	const ColorA ColorA::CYAN = ColorA(0, 255, 255, 255);
	const ColorA ColorA::CLEAR = ColorA(0, 0, 0, 0);
}