#include <LTEngine/engine.hpp>
#include <LTEngine/sdl_window.hpp>


int main(int argc, char *argv[]) {
    LTEngine::SDLWindow window = LTEngine::SDLWindow("LTEngine Pong", 500, 400);

    window.setResizable(true);

    while (!window.shouldClose()) {
        window.pollEvents();
    }
    return 0;
}