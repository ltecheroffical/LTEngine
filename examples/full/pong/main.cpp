#include <iostream>
#include <thread>
#include <chrono>

#include <LTEngine/engine.hpp>
#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/sdl_window.hpp>
#include <LTEngine/rendering/sdl_renderer.hpp>

#include "player_controller.hpp"
#include "paddle.hpp"
#include "ball.hpp"


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

    const u32 ball = structure->addObject(std::make_unique<Ball>(), LTEngine::Math::Vec2(SCREEN_WIDTH / 2.f - (f32)Ball::BALL_RADIUS / 2.f, SCREEN_HEIGHT / 2.f - (f32)Ball::BALL_RADIUS / 2.f));

    structure->setClearColor(LTEngine::Rendering::Color::BLACK);

    engine.initDisplay(&renderer);

    f32 deltaSeconds = 0.0f;
    while (!window.shouldClose()) {
        u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        window.pollEvents();

        Paddle *player = dynamic_cast<Paddle*>(structure->getObject(playerPaddle));
        Paddle *enemy = dynamic_cast<Paddle*>(structure->getObject(enemyPaddle));

        if (player != nullptr && enemy != nullptr) {
            player->position.y = std::clamp(player->position.y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT);
            enemy->position.y = std::clamp(enemy->position.y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT);
        }

        engine.update(deltaSeconds);
        if (!window.isMinimized() && !window.isHidden()) {
            engine.render();
            window.present();
        }

        do {
            u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            deltaSeconds = (end - start) / 1000000000.f;

            auto sleepDuration = std::chrono::duration<f32>(1.0f / 60.0f - deltaSeconds);
            std::this_thread::sleep_for(sleepDuration);
        } while (deltaSeconds < 1.0f / 60.0f);

        std::cout << "FPS: " << 1.0f / deltaSeconds << std::endl;
    }

    return 0;
}
