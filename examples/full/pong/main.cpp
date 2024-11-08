#include <chrono>

#include <LTEngine/engine.hpp>
#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/sdl_window.hpp>
#include <LTEngine/rendering/software_renderer.hpp>

#include "player_controller.hpp"
#include "paddle.hpp"


#define SCREEN_WIDTH ((u32)500)
#define SCREEN_HEIGHT ((u32)400)

#define PADDLE_OFFSET ((u32)20)


using namespace Pong;


int main(int argc, char *argv[]) {
    LTEngine::SDLWindow window((char*)"Pong", SCREEN_WIDTH, SCREEN_HEIGHT);

    window.setResizable(false);

    LTEngine::Engine engine(std::make_unique<LTEngine::Object::ObjectStructure>());
    LTEngine::Rendering::SoftwareRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);


    LTEngine::Object::ObjectStructure *structure = dynamic_cast<LTEngine::Object::ObjectStructure*>(engine.getObjectStructure());

    if (structure == nullptr) {
        return -1;
    }

    PlayerController playerController(&window);

    structure->addObject(std::make_unique<Paddle>(&playerController), LTEngine::Math::Vec2(PADDLE_OFFSET, SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));
    structure->addObject(std::make_unique<Paddle>(nullptr), LTEngine::Math::Vec2(SCREEN_WIDTH - PADDLE_OFFSET - Paddle::PADDLE_WIDTH, SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));

    structure->setClearColor(LTEngine::Rendering::Color::BLACK);

    std::vector<LTEngine::Rendering::Color> screen(renderer.getScreenData(nullptr));

    engine.initDisplay(&renderer);

    f32 delta = 0.0f;
    u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    while (!window.shouldClose()) {
        window.pollEvents();
        window.clear(LTEngine::Rendering::ColorA(180, 180, 180, 255));

        engine.update(delta);
        engine.render();
        
        renderer.getScreenData(screen.data());
        window.display(screen.data(), SCREEN_WIDTH, SCREEN_HEIGHT);
        window.present();

        u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta = (f32)(end - start) / 10000000000.f;
        start = end;
    }

    return 0;
}
