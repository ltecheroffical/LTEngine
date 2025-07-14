#include <SDL3/SDL.h>

#include "sdl_utils.hpp"

void LTEngine::SDL::throwSDLError() {
	throw std::runtime_error("SDL: " + std::string(SDL_GetError()));
}
