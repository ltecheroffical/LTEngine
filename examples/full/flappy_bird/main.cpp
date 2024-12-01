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


#define SCALE ((u32)3)

#define SCREEN_WIDTH ((u32)144 * SCALE)
#define SCREEN_HEIGHT ((u32)256 * SCALE)


const u32 pipeMinY = -50;
const u32 pipeMaxY = 100;
const u32 pipeOffset = 300;
const u32 pipeDistance = 140;


const LTEngine::Shapes::Recti bgDayRegion = {0, 0, 144, 256};
const LTEngine::Shapes::Recti groundRegion = {292, 0, 168, 56};
const LTEngine::Shapes::Recti birdRegion = {31, 491, 17, 12};
const LTEngine::Shapes::Recti pipeRegion = {84, 323, 26, 160};


struct GameState {
	u32 mainCamera;
	f32 backgroundX[3];

	f32 startTimer = 3.f;

	LTEngine::Math::Vec2 pipePositions[4];
	u8 lastTeleportedPipe = 3;

	LTEngine::Math::Vec2 birdPosition;
	f32 birdVelocityY;

	bool jumpPressedOnce : 1;
};


void init(GameState *state);
void displayInit(GameState *state, LTEngine::Rendering::Renderer *renderer);
void update(GameState *state, LTEngine::Window *window, f32 delta);
void render(GameState *state, const LTEngine::Rendering::Image *spritesheet, LTEngine::Rendering::Renderer *renderer);


int main(int argc, char *argv[]) {
	LTEngine::GLFWWindow window((char *)"Flappy Bird", SCREEN_WIDTH, SCREEN_HEIGHT,
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

	LTEngine::Rendering::Image spritesheet = LTEngine::Rendering::Image(0, 0);
	spritesheet.load(SPRITESHEET_FILE);

	GameState state;

	LTEngine::Engine engine(nullptr);
	init(&state);

	engine.initDisplay(&renderer);
	displayInit(&state, &renderer);

	engine.onUpdate += std::bind(update, &state, &window, std::placeholders::_1);
	engine.onRender += std::bind(render, &state, &spritesheet, std::placeholders::_1);

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


void init(GameState *state) {
	srand(time(nullptr));

	state->birdPosition = {(f32)SCREEN_WIDTH / 2, (f32)SCREEN_HEIGHT / 2};

	state->pipePositions[0] = {SCREEN_WIDTH + 0, (f32)(rand() % (pipeMaxY - pipeMinY) + pipeMinY)};
	state->pipePositions[1] = {SCREEN_WIDTH + pipeDistance, (f32)(rand() % (pipeMaxY - pipeMinY) + pipeMinY)};
	state->pipePositions[2] = {SCREEN_WIDTH + pipeDistance * 2, (f32)(rand() % (pipeMaxY - pipeMinY) + pipeMinY)};
	state->pipePositions[3] = {SCREEN_WIDTH + pipeDistance * 3, (f32)(rand() % (pipeMaxY - pipeMinY) + pipeMinY)};
}

void displayInit(GameState *state, LTEngine::Rendering::Renderer *renderer) {
	state->mainCamera = renderer->createCamera(LTEngine::Math::Vec2::Zero, LTEngine::Math::Vec2::One);

	state->backgroundX[0] = 0;
	state->backgroundX[1] = bgDayRegion.w * SCALE;
	state->backgroundX[2] = bgDayRegion.w * SCALE * 2;
}

void update(GameState *state, LTEngine::Window *window, f32 delta) {
	if (state->startTimer > 0.f) {
		state->startTimer -= delta;
		return;
	}

	const f32 birdSpeed = 100.f;
	const f32 flapForce = 100.f;

	state->birdVelocityY += delta * 250.f;

	state->birdPosition.x += delta * birdSpeed;
	state->birdPosition.y += delta * state->birdVelocityY;

	for (u32 i = 0; i < 4; i++) {
		if (LTEngine::Physics::testCollision(
		        {state->birdPosition.x, state->birdPosition.y, birdRegion.w, birdRegion.h},
		        {state->pipePositions[i].x, -(i32)pipeOffset + state->pipePositions[i].y, pipeRegion.w, pipeRegion.h}) ||
		    LTEngine::Physics::testCollision(
		        {state->birdPosition.x, state->birdPosition.y, birdRegion.w, birdRegion.h},
		        {state->pipePositions[i].x, pipeOffset + state->pipePositions[i].y, pipeRegion.w, pipeRegion.h})) {
			// TODO: Add real ending
			*((volatile u8 *)NULL) = 0;
		}
	}

	if (window->isKeyPressed(LTEngine::WindowKey::KEY_SPACE)) {
		if (!state->jumpPressedOnce) {
			state->birdVelocityY = -flapForce;
			state->jumpPressedOnce = true;
		}
	} else {
		state->jumpPressedOnce = false;
	}
}

void render(GameState *state, const LTEngine::Rendering::Image *spritesheet, LTEngine::Rendering::Renderer *renderer) {
	renderer->clear(LTEngine::Rendering::Color::Cyan);
	renderer->setScale({SCALE, SCALE});

	renderer->setCameraPosition(state->mainCamera, {state->birdPosition.x - (f32)SCREEN_WIDTH / 2 + (f32)birdRegion.w / 2, 0});
	renderer->setCurrentCamera(state->mainCamera);

	LTEngine::Rendering::OpenGLRenderer *glRenderer = dynamic_cast<LTEngine::Rendering::OpenGLRenderer *>(renderer);
	if (glRenderer != nullptr) { glRenderer->setNearestFilter(); }

	for (u32 i = 0; i < 3; i++) {
		if (renderer->worldToScreenPosition(LTEngine::Math::Vec2{state->backgroundX[i], 0}).x + bgDayRegion.w * SCALE < 0) {
			state->backgroundX[i] += bgDayRegion.w * SCALE * 3;
		}

		renderer->drawImage(spritesheet, LTEngine::Math::Vec2{state->backgroundX[i], 0.f}, 0.f, bgDayRegion,
		                    LTEngine::Rendering::ColorA::White);

		renderer->setZOrder(1);
		renderer->drawImage(spritesheet, LTEngine::Math::Vec2{state->backgroundX[i], (f32)(SCREEN_HEIGHT - groundRegion.h * SCALE)},
		                    0.f, groundRegion, LTEngine::Rendering::ColorA::White);
		renderer->setZOrder(0);
	}

	for (u32 i = 0; i < 4; i++) {
		if (renderer->worldToScreenPosition(state->pipePositions[i]).x + pipeRegion.w * SCALE < 0) {
			state->pipePositions[i].x = state->pipePositions[state->lastTeleportedPipe].x + pipeRegion.w * SCALE + pipeDistance;
			state->pipePositions[i].y = (f32)(rand() % (pipeMaxY - pipeMinY) + pipeMinY);
			state->lastTeleportedPipe = i;
		}

		renderer->drawImage(spritesheet,
		                    LTEngine::Math::Vec2{state->pipePositions[i].x, -(i32)pipeOffset + state->pipePositions[i].y}, 0.f,
		                    pipeRegion, LTEngine::Rendering::ColorA::White, LTEngine::Rendering::Renderer::FLAG_FLIP_V);
		renderer->drawImage(spritesheet, LTEngine::Math::Vec2{state->pipePositions[i].x, pipeOffset + state->pipePositions[i].y},
		                    0.f, pipeRegion, LTEngine::Rendering::ColorA::White);
	}

	renderer->drawImage(spritesheet, state->birdPosition, 0.f, birdRegion, LTEngine::Rendering::ColorA::White);
}
