#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

#include <LTEngine/window.hpp>


namespace LTEngine {
    class GLFWWindow : public Window {
    public:
        GLFWWindow(const char *title, u32 width, u32 height);
        GLFWWindow(const char *title, u32 width, u32 height, const std::unordered_map<int, int> &hints);
        ~GLFWWindow() override;

        void setSize(u32 width, u32 height) override;
        void setPosition(u32 x, u32 y) override;
        void setTitle(const char *title) override;
        void setResizable(bool resizable) override;
        void setFullscreen(bool fullscreen) override;
        void setMinimized(bool minimized) override;

        void show() override;
        void hide() override;

        u32 getWidth() override, getHeight() override;
        u32 getX() override, getY() override;
        const char *getTitle() override;
        bool isResizable() override;
        bool isFullscreen() override;
        bool isMinimized() override;
        bool isHidden() override;

        void pollEvents() override;
        void swapBuffers();

        bool shouldClose() override;

        bool isKeyPressed(WindowKey key) override;
        bool isKeyReleased(WindowKey key) override;
        
        f64 getMouseX() override;
        f64 getMouseY() override;
        bool isMousePressed(WindowMouseButton button) override;
        bool isMouseReleased(WindowMouseButton button) override;

        void display(Rendering::Color *screen, u32 width, u32 height) override;
        void display(Rendering::ColorA *screen, u32 width, u32 height) override;

        void makeContextCurrent();

        GLFWwindow *getGLFWWindow();
        void setCleanupGLFW(bool value);
    
    private:
        GLFWwindow *m_glfwWindow;

        bool m_cleanupGLFW;
    };
}
