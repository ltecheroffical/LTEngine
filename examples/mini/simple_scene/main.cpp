#include <condition_variable>
#include <iostream>
#include <thread>

#include <LTEngine/rendering/software_renderer.hpp>
#include <LTEngine/sdl_window.hpp>


int main(int argc, char *argv[]) {
	LTEngine::SDLWindow window("Simple Scene", 700, 400);
	LTEngine::Rendering::SoftwareRenderer renderer(700, 400);

	bool running = true;

	std::mutex renderWaitMutex;
	std::condition_variable renderWait;

	std::thread renderThread([&renderer, &running, &renderWait]() {
		while (true) {
			while (running) {
				renderer.processAll();
				renderWait.notify_all();
			}
		}
	});

	std::vector<LTEngine::Rendering::Color> screen(renderer.getScreenData(nullptr));
	LTEngine::f32 delta = 0.f;

	LTEngine::f32 rotation = 0.f;
	while (!window.shouldClose()) {
		LTEngine::u64 start = std::chrono::high_resolution_clock::now().time_since_epoch().count();

		window.pollEvents();

		renderer.setScreenOnly();
		renderer.clear(LTEngine::Rendering::ColorA::White);

		renderer.setRotationOffset(rotation);
		renderer.drawRect({20, 40, 200, 400}, LTEngine::Rendering::ColorA::Red);
		renderer.drawRect({300, 40, 100, 100}, LTEngine::Rendering::ColorA::Blue);


		rotation += delta * 50.f;

		{
			std::unique_lock lock(renderWaitMutex);
			renderWait.wait(lock, [&renderer] {
				return !renderer.hasQueuedTasks();
			});
		}

		window.clear(LTEngine::Rendering::ColorA::Black);
		renderer.getScreenData(screen.data());

		window.display(screen.data(), window.getWidth(), window.getHeight());
		window.present();

		LTEngine::u64 end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		delta = (end - start) / 1000000000.f;

		auto sleepDuration = std::chrono::duration<LTEngine::f32>(1.0f / 60.f - delta);
		std::this_thread::sleep_for(sleepDuration);

		std::cout << "FPS: " << 1.0f / delta << std::endl;
	}

	running = false;
	renderThread.detach();
	return 0;
}
