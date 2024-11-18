#include <chrono>
#include <iostream>
#include <thread>

#include <LTEngine/engine.hpp>
#include <LTEngine/rendering/opengl_renderer.hpp>
#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/glfw_window.hpp>

#include "ball.hpp"
#include "paddle.hpp"
#include "player_controller.hpp"


#define SCREEN_WIDTH ((u32)500)
#define SCREEN_HEIGHT ((u32)400)

#define PADDLE_OFFSET ((u32)20)


using namespace Pong;


int main(int argc, char *argv[]) {
	LTEngine::GLFWWindow window((char *)"Pong", SCREEN_WIDTH, SCREEN_HEIGHT,
	                            {{GLFW_CONTEXT_VERSION_MAJOR, 3},
	                             {GLFW_CONTEXT_VERSION_MINOR, 3},
	                             {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
	                             {GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE}});

	window.setResizable(false);

	window.makeContextCurrent();

	LTEngine::Engine engine(std::make_unique<LTEngine::Object::ObjectStructure>());

	LTEngine::Rendering::OpenGLRenderer::loadOpenGL((GLADloadproc)glfwGetProcAddress);
	LTEngine::Rendering::OpenGLRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, [&window]() { window.makeContextCurrent(); });
	window.setCleanupGLFW(true);

	const u32 mainCamera = renderer.createCamera(LTEngine::Math::Vec2::Zero, LTEngine::Math::Vec2::One);
	renderer.setCurrentCamera(mainCamera);

	LTEngine::Object::ObjectStructure *structure = dynamic_cast<LTEngine::Object::ObjectStructure *>(engine.getObjectStructure());

	if (structure == nullptr) { return -1; }

	PlayerController playerController(&window);

	const u32 playerPaddle =
	    structure->addObject(std::make_unique<Paddle>(&playerController),
	                         LTEngine::Math::Vec2(PADDLE_OFFSET, SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));
	const u32 enemyPaddle = structure->addObject(std::make_unique<Paddle>(nullptr),
	                                             LTEngine::Math::Vec2(SCREEN_WIDTH - PADDLE_OFFSET - Paddle::PADDLE_WIDTH,
	                                                                  SCREEN_HEIGHT / 2.f - Paddle::PADDLE_HEIGHT / 2.f));

	const u32 ball =
	    structure->addObject(std::make_unique<Ball>(), LTEngine::Math::Vec2(SCREEN_WIDTH / 2.f - (f32)Ball::BALL_RADIUS / 2.f,
	                                                                        SCREEN_HEIGHT / 2.f - (f32)Ball::BALL_RADIUS / 2.f));

	structure->setClearColor(LTEngine::Rendering::Color::Black);

	engine.initDisplay(&renderer);

	f32 deltaSeconds = 0.0f;
	while (!window.shouldClose()) {
		u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		window.pollEvents();

		Paddle *player = dynamic_cast<Paddle *>(structure->getObject(playerPaddle));
		Paddle *enemy = dynamic_cast<Paddle *>(structure->getObject(enemyPaddle));

		if (player != nullptr && enemy != nullptr) {
			player->setPosition(
			    {player->getPosition().x, std::clamp(player->getPosition().y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT)});
			enemy->setPosition(
			    {enemy->getPosition().x, std::clamp(enemy->getPosition().y, 0.f, (f32)SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT)});
		};

		engine.update(deltaSeconds);
		if (!window.isMinimized() && !window.isHidden()) { engine.render(); }

		renderer.flush();
		window.swapBuffers();

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
