#include <chrono>

#include <LTEngine/engine.hpp>
#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/sdl_window.hpp>
#include <LTEngine/rendering/sdl_renderer.hpp>

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
    LTEngine::Rendering::SDLRenderer renderer(window.getRenderer());

    const u32 mainCamera = renderer.createCamera(LTEngine::Math::Vec2::ZERO, LTEngine::Math::Vec2::ONE);
    renderer.setCurrentCamera(mainCamera);

    LTEngine::Object::ObjectStructure *structure = dynamic_cast<LTEngine::Object::ObjectStructure*>(engine.getObjectStructure());

    if (structure == nullptr) {
        return -1;
    }

    PlayerController playerController(&window);

    const u32 playerPaddle = structure->addObject(std::make_unique<Paddle>(&playerController), LTEngine::Math::Vec2(PADDLE_OFFSET, SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));
    const u32 enemyPaddle = structure->addObject(std::make_unique<Paddle>(nullptr), LTEngine::Math::Vec2(SCREEN_WIDTH - PADDLE_OFFSET - Paddle::PADDLE_WIDTH, SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));

    structure->setClearColor(LTEngine::Rendering::Color::BLACK);

    engine.initDisplay(&renderer);

    f32 delta = 0.0f;
    u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    while (!window.shouldClose()) {
        window.pollEvents();

        Paddle *player = dynamic_cast<Paddle*>(structure->getObject(playerPaddle));
        Paddle *enemy = dynamic_cast<Paddle*>(structure->getObject(enemyPaddle));

        if (player != nullptr && enemy != nullptr) {
            player->position.y = std::clamp(player->position.y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT);
            enemy->position.y = std::clamp(enemy->position.y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT);
        }

        engine.update(delta);
        engine.render();
        
        window.present();

        u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        delta = (f32)(end - start) / 10000000000.f;
        start = end;
    }

    return 0;
}
