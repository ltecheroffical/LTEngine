#include <LTEngine/engine.hpp>
#include <LTEngine/logger.hpp>

#include <LTEngine/rendering/opengl_renderer.hpp>
#include <LTEngine/glfw_window.hpp>


int main(int argc, char *argv[]) {
    LTEngine::GLFWWindow window = LTEngine::GLFWWindow("LTEngine Pong", 500, 400, {
        {GLFW_OPENGL_DEBUG_CONTEXT, true}
    });
    LTEngine::Logger logger;
    logger.setLogOutput(LTEngine::Logger::LogOutput::Stdout);
    
    window.setResizable(true);
    
    window.makeContextCurrent();
    LTEngine::GLFWWindow::loadGL();
    
    LTEngine::Rendering::OpenGLRenderer renderer(window.getWidth(), window.getHeight(), [&window]() {
        window.makeContextCurrent();
    }, &logger);

    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();

        renderer.clear(LTEngine::Rendering::ColorA::Black);
        renderer.drawRect({0, 0, 20, 20}, LTEngine::Rendering::ColorA::White, 0);

        renderer.flush();
    }
    return 0;
}