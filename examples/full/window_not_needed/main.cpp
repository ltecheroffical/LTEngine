#include <iostream>
#include <thread>

#include <LTEngine/engine.hpp>

#include <LTEngine/rendering/software_renderer.hpp>

#include <LTEngine/structure/object_structure.hpp>

#include "snake.hpp"
#include "apple.hpp"


#define SCREEN_WIDTH ((u32)20)
#define SCREEN_HEIGHT ((u32)20)


Snake::Direction direction = Snake::Direction::Down;
bool isRunning = true;


void inputWorker() {
    while (isRunning) {
        switch (std::cin.get()) {
            case 'w':
                direction = Snake::Direction::Up;
                break;
            case 's':
                direction = Snake::Direction::Down;
                break;
            case 'a':
                direction = Snake::Direction::Left;
                break;
            case 'd':
                direction = Snake::Direction::Right;
                break;
            case 'q':
                isRunning = false;
                break;
        }
    }
}


std::string rgbToANSI(u8 r, u8 g, u8 b) {
    u8 colorCode = 16 + (r / 51) * 36 + (g / 51) * 6 + (b / 51);
    return "\033[38;5;" + std::to_string(colorCode) + "m";
}


int main(int argc, char *argv[]) {
    LTEngine::Engine engine(std::make_unique<LTEngine::Object::ObjectStructure>());
    LTEngine::Rendering::SoftwareRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    engine.initDisplay(&renderer);

    renderer.setScreenOnly();

    LTEngine::Object::ObjectStructure *structure = dynamic_cast<LTEngine::Object::ObjectStructure*>(engine.getObjectStructure());
    if (structure == nullptr) {
        return -1;
    }

    structure->setClearColor(LTEngine::Rendering::Color::BLACK);

    const u32 snakeObj = structure->addObject(std::make_unique<Snake>(LTEngine::Math::Vec2((f32)SCREEN_WIDTH / 2, (f32)SCREEN_HEIGHT / 2)));
    const u32 appleObj = structure->addObject(std::make_unique<Apple>(snakeObj, LTEngine::Math::Vec2u(SCREEN_WIDTH, SCREEN_HEIGHT)));

    Snake *snake = dynamic_cast<Snake*>(structure->getObject(snakeObj));
    if (snake == nullptr) {
        return -1;
    }

    std::vector<LTEngine::Rendering::Color> screen(renderer.getScreenData(nullptr));

    std::thread inputThread(inputWorker);

    inputThread.detach();

    f32 deltaSeconds = 0.0f;
    while (isRunning) {
        u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        engine.update(deltaSeconds);
        engine.render();

        // Render the output
        renderer.getScreenData(screen.data());

        std::cout << "\033[H\033[2J\033[3J";

        for (u32 y = 0; y < SCREEN_HEIGHT; y++) {
            std::cout << "\n";
            for (u32 x = 0; x < SCREEN_WIDTH; x++) {
                u32 i = x + y * SCREEN_WIDTH;
                if (screen[i].r != 0 || screen[i].g != 0 || screen[i].b != 0) {
                    std::cout << rgbToANSI(screen[i].r, screen[i].g, screen[i].b) << "[]";
                } else {
                    std::cout << "  ";
                }
            }
        }

        std::cout << "\033[0m";
        std::cout.flush();

        snake->setDirection(direction);

        do {
            u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            deltaSeconds = (end - start) / 1000000000.f;

            auto sleepDuration = std::chrono::duration<f32>(1.0f / 60.0f - deltaSeconds);
            std::this_thread::sleep_for(sleepDuration);
        } while (deltaSeconds < 1.f / 1.f);
    }
    return 0;
}
