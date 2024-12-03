#define LTENGINE_GLOBAL_BASIC_TYPES

#include <chrono>
#include <iostream>
#include <thread>

#include <LTEngine/timer.hpp>

#include <LTEngine/engine.hpp>

#include <LTEngine/rendering/image.hpp>
#include <LTEngine/rendering/opengl_renderer.hpp>

#include <LTEngine/physics/collision.hpp>

#include <LTEngine/glfw_window.hpp>


#define SCREEN_WIDTH ((u32)500)
#define SCREEN_HEIGHT ((u32)400)


struct GameState {
	u32 mainCamera;
};


void init(GameState *state);
void displayInit(GameState *state, LTEngine::Rendering::Renderer *renderer);
void update(GameState *state, LTEngine::Window *window, f32 delta);
void render(GameState *state, LTEngine::Rendering::Renderer *renderer);


int main(int argc, char *argv[]) {
	LTEngine::GLFWWindow window((char *)"Sorting Visualizer", SCREEN_WIDTH, SCREEN_HEIGHT,
	                            {{GLFW_CONTEXT_VERSION_MAJOR, 3},
	                             {GLFW_CONTEXT_VERSION_MINOR, 3},
	                             {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
	                             {GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE}});

	// window.setResizable(false);
	window.setResizable(true);

	window.makeContextCurrent();

	LTEngine::GLFWWindow::loadGL();
	LTEngine::Rendering::OpenGLRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, [&window]() { window.makeContextCurrent(); });

	window.setCleanupGLFW(true);

	const u32 mainCamera = renderer.createCamera(LTEngine::Math::Vec2::Zero, LTEngine::Math::Vec2::One);
	renderer.setCurrentCamera(mainCamera);

	GameState state;

	LTEngine::Engine engine(nullptr);
	init(&state);

	engine.initDisplay(&renderer);
	displayInit(&state, &renderer);

	engine.onUpdate += std::bind(update, &state, &window, std::placeholders::_1);
	engine.onRender += std::bind(render, &state, std::placeholders::_1);

	f32 deltaSeconds = 0.0f;
	while (!window.shouldClose()) {
		u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		window.pollEvents();

		engine.update(deltaSeconds);

		if (!window.isMinimized() && !window.isHidden()) {
			renderer.resize(window.getWidth(), window.getHeight());

			engine.render();
			renderer.flush();
			window.swapBuffers();
		}

		do {
			u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			deltaSeconds = (end - start) / 1000000000.f;

			auto sleepDuration = std::chrono::duration<f32>(1.0f / 60.f - deltaSeconds);
			std::this_thread::sleep_for(sleepDuration);
		} while (deltaSeconds < 1.0f / 60.f);

		std::cout << "FPS: " << 1.0f / deltaSeconds << std::endl;
	}
	return 0;
}


void init(GameState *state) {}

void displayInit(GameState *state, LTEngine::Rendering::Renderer *renderer) {
	state->mainCamera = renderer->createCamera(LTEngine::Math::Vec2::Zero, LTEngine::Math::Vec2::One);
}

void update(GameState *state, LTEngine::Window *window, f32 delta) {}

void render(GameState *state, LTEngine::Rendering::Renderer *renderer) {
	renderer->clear(LTEngine::Rendering::Color::Black);
}
