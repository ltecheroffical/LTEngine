
#include <LTEngine/graphics/color.hpp>

namespace LTEngine::Graphics {
	const Color Color::Black = Color(0, 0, 0);
	const Color Color::White = Color(255, 255, 255);
	const Color Color::Red = Color(255, 0, 0);
	const Color Color::Green = Color(0, 255, 0);
	const Color Color::Blue = Color(0, 0, 255);
	const Color Color::Yellow = Color(255, 255, 0);
	const Color Color::Cyan = Color(0, 255, 255);
	
	const ColorA ColorA::Black = ColorA(0, 0, 0, 255);
	const ColorA ColorA::White = ColorA(255, 255, 255, 255);
	const ColorA ColorA::Red = ColorA(255, 0, 0, 255);
	const ColorA ColorA::Green = ColorA(0, 255, 0, 255);
	const ColorA ColorA::Blue = ColorA(0, 0, 255, 255);
	const ColorA ColorA::Yellow = ColorA(255, 255, 0, 255);
	const ColorA ColorA::Cyan = ColorA(0, 255, 255, 255);
	const ColorA ColorA::Clear = ColorA(0, 0, 0, 0);
}