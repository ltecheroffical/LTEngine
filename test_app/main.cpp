#include <LTCore/engine.hpp>
#include <LTCore/logger.hpp>

#include <LTCore/rendering/opengl_renderer.hpp>
#include <LTCore/glfw_window.hpp>


int main(int argc, char *argv[]) {
    LTCore::GLFWWindow window = LTCore::GLFWWindow("LTCore Pong", 500, 400, {
        {GLFW_OPENGL_DEBUG_CONTEXT, true}
    });
    LTCore::Logger logger;
    logger.setLogOutput(LTCore::Logger::LogOutput::Stdout);
    
    window.setResizable(true);
    
    window.makeContextCurrent();
    LTCore::GLFWWindow::loadGL();
    
    LTCore::Rendering::OpenGLRenderer renderer(window.getWidth(), window.getHeight(), [&window]() {
        window.makeContextCurrent();
    }, &logger);

    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();

        renderer.clear(LTCore::Rendering::ColorA::Black);
        renderer.drawRect({0, 0, 20, 20}, LTCore::Rendering::ColorA::White, 0);

        renderer.flush();
    }
    return 0;
}