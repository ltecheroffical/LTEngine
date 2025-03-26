#include <SDL3/SDL_vulkan.h>

#include <LTEngine/engine.hpp>
#include <LTEngine/logger.hpp>
#include <LTEngine/sdl_window.hpp>

#include <LTEngine/rendering/vulkan_renderer.hpp>


int main(int argc, char *argv[]) {
    LTEngine::SDLWindow window = LTEngine::SDLWindow("LTEngine Pong", 500, 400, LTEngine::SDLWindow::WindowGraphicsAPI::Vulkan);
    LTEngine::Logger logger;
    logger.setLogOutput(LTEngine::Logger::LogOutput::Stdout);

    window.setResizable(true);

    std::vector<const char *> extensions;
    LTEngine::u32 extension_count = 0;
    auto extension_names = SDL_Vulkan_GetInstanceExtensions(&extension_count);
    for (LTEngine::u32 i = 0; i < extension_count; i++) {
        extensions.push_back(extension_names[i]);
    }

    LTEngine::Rendering::VulkanRenderer renderer([&window, &logger](VkInstance instance) {
        VkSurfaceKHR surface;
        if (!SDL_Vulkan_CreateSurface(window.getWindow(), instance, nullptr, &surface)) {
            logger.fatal(SDL_GetError());
        }
        return surface;
    }, extensions);

    while (!window.shouldClose()) {
        window.pollEvents();
    }
    return 0;
}