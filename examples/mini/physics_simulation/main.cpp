#define LTENGINE_GLOBAL_BASIC_TYPES

#include <chrono>
#include <iostream>
#include <thread>

#include <LTEngine/timer.hpp>

#include <LTEngine/engine.hpp>
#include <LTEngine/rendering/opengl_renderer.hpp>
#include <LTEngine/structure/object_structure.hpp>

#include <LTEngine/physics/box2d.hpp>

#include <LTEngine/glfw_window.hpp>

#include "floor.hpp"
#include "mouse.hpp"
#include "object_spawner.hpp"


using namespace PhysicsSimulation;


#define SCREEN_WIDTH ((u32)500)
#define SCREEN_HEIGHT ((u32)400)

#define BOX_HEIGHT ((u32)5)


int main(int argc, char *argv[]) {
	LTEngine::GLFWWindow window((char *)"Pong", SCREEN_WIDTH, SCREEN_HEIGHT,
	                            {{GLFW_CONTEXT_VERSION_MAJOR, 3},
	                             {GLFW_CONTEXT_VERSION_MINOR, 3},
	                             {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
	                             {GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE}});

	window.setResizable(true);

	window.makeContextCurrent();

	LTEngine::GLFWWindow::loadGL();
	LTEngine::Rendering::OpenGLRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, [&window]() { window.makeContextCurrent(); });

	window.setCleanupGLFW(true);

	const u32 mainCamera = renderer.createCamera(LTEngine::Math::Vec2::Zero, LTEngine::Math::Vec2::One);
	renderer.setCurrentCamera(mainCamera);

	LTEngine::Physics::Box2D physicsEngine;
	physicsEngine.setGravity(LTEngine::Math::Vec2(0.f, 10.f));

	LTEngine::Engine engine(std::make_unique<LTEngine::Object::ObjectStructure>());
	LTEngine::Object::ObjectStructure *structure = dynamic_cast<LTEngine::Object::ObjectStructure *>(engine.getObjectStructure());

	if (structure == nullptr) { return -1; }

	structure->setClearColor(LTEngine::Rendering::Color::Cyan);

	const u32 spawner = structure->addObject(std::make_unique<ObjectSpawner>(&physicsEngine));
	ObjectSpawner *objectSpawner = dynamic_cast<ObjectSpawner *>(structure->getObject(spawner)); // Object B spawned by this
	if (objectSpawner != nullptr) { objectSpawner->setSpawnAreaWidth(SCREEN_WIDTH); }

	const u32 floor = structure->addObject(
	    std::make_unique<Floor>(&physicsEngine, (LTEngine::Shapes::Rect){0, SCREEN_HEIGHT - BOX_HEIGHT, SCREEN_WIDTH, BOX_HEIGHT}));
	const u32 mouse = structure->addObject(std::make_unique<PhysicsMouse>(&physicsEngine, &window));

	engine.initDisplay(&renderer);

	f32 deltaSeconds = 0.0f;
	while (!window.shouldClose()) {
		u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		window.pollEvents();

		physicsEngine.update(deltaSeconds);
		engine.update(deltaSeconds);


		if (!window.isMinimized() && !window.isHidden() && window.isFocused()) {
			renderer.resize(window.getWidth(), window.getHeight());

			engine.render();
			renderer.flush();
			window.swapBuffers();
		}

		LTEngine::Rendering::OpenGLRenderer::OpenGLMessage message;
		while (renderer.getMessage(&message)) {
			std::cout << "OpenGL Message:" << std::endl;
			std::cout << "\tId: " << message.id << std::endl;
			std::cout << "\tSource: " << message.stringSource << std::endl;
			std::cout << "\tType: " << message.stringType << std::endl;
			std::cout << "\tSeverity: " << message.stringSeverity << std::endl;
			std::cout << "\tMessage: " << message.msg << std::endl;
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
