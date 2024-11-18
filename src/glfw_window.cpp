#include <stdexcept>

#include <LTEngine/glfw_window.hpp>


using namespace LTEngine;


GLFWWindow::GLFWWindow(const char *title, u32 width, u32 height) {
	glfwInit();

	m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_glfwWindow == nullptr) { throw std::runtime_error("Failed to create GLFW window"); }
	m_cleanupGLFW = true;
}

GLFWWindow::GLFWWindow(const char *title, u32 width, u32 height, const std::unordered_map<int, int> &hints) {
	glfwInit();

	std::for_each(hints.begin(), hints.end(), [](const std::pair<int, int> &hint) { glfwWindowHint(hint.first, hint.second); });

	m_glfwWindow = glfwCreateWindow(width, height, "LTEngine", nullptr, nullptr);
	if (m_glfwWindow == nullptr) { throw std::runtime_error("Failed to create GLFW window"); }
	m_cleanupGLFW = true;
}


GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(m_glfwWindow);

	if (m_cleanupGLFW) { glfwTerminate(); }
}


void GLFWWindow::setSize(u32 width, u32 height) {
	glfwSetWindowSize(m_glfwWindow, width, height);
}

void GLFWWindow::setPosition(u32 x, u32 y) {
	glfwSetWindowPos(m_glfwWindow, x, y);
}

void GLFWWindow::setTitle(const char *title) {
	glfwSetWindowTitle(m_glfwWindow, title);
}

void GLFWWindow::setResizable(bool resizable) {
	glfwSetWindowAttrib(m_glfwWindow, GLFW_RESIZABLE, resizable);
}

void GLFWWindow::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		glfwMaximizeWindow(m_glfwWindow);
	} else {
		glfwRestoreWindow(m_glfwWindow);
	}
}

void GLFWWindow::setMinimized(bool minimized) {
	if (minimized) {
		glfwIconifyWindow(m_glfwWindow);
	} else {
		glfwRestoreWindow(m_glfwWindow);
	}
}


void GLFWWindow::show() {
	glfwShowWindow(m_glfwWindow);
}

void GLFWWindow::hide() {
	glfwHideWindow(m_glfwWindow);
}


u32 GLFWWindow::getWidth() {
	int width, height;
	glfwGetWindowSize(m_glfwWindow, &width, &height);
	return width;
}

u32 GLFWWindow::getHeight() {
	int width, height;
	glfwGetWindowSize(m_glfwWindow, &width, &height);
	return height;
}

u32 GLFWWindow::getX() {
	int x, y;
	glfwGetWindowPos(m_glfwWindow, &x, &y);
	return x;
}

u32 GLFWWindow::getY() {
	int x, y;
	glfwGetWindowPos(m_glfwWindow, &x, &y);
	return y;
}

const char *GLFWWindow::getTitle() {
	return glfwGetWindowTitle(m_glfwWindow);
}

bool GLFWWindow::isResizable() {
	return glfwGetWindowAttrib(m_glfwWindow, GLFW_RESIZABLE);
}

bool GLFWWindow::isFullscreen() {
	return glfwGetWindowAttrib(m_glfwWindow, GLFW_MAXIMIZED);
}

bool GLFWWindow::isMinimized() {
	return glfwGetWindowAttrib(m_glfwWindow, GLFW_ICONIFIED);
}

bool GLFWWindow::isHidden() {
	return !glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE);
}

bool GLFWWindow::isFocused() {
	return glfwGetWindowAttrib(m_glfwWindow, GLFW_FOCUSED);
}


void GLFWWindow::pollEvents() {
	glfwPollEvents();
}

void GLFWWindow::swapBuffers() {
	glfwSwapBuffers(m_glfwWindow);
}


bool GLFWWindow::shouldClose() {
	return glfwWindowShouldClose(m_glfwWindow);
}


extern const int windowKeyToGLFWKeyLookup[];
extern const int windowMouseButtonToGLFWMouseButtonLookup[];

bool GLFWWindow::isKeyPressed(WindowKey key) {
	return glfwGetKey(m_glfwWindow, windowKeyToGLFWKeyLookup[static_cast<int>(key)]) == GLFW_PRESS;
}

bool GLFWWindow::isKeyReleased(WindowKey key) {
	return glfwGetKey(m_glfwWindow, windowKeyToGLFWKeyLookup[static_cast<int>(key)]) == GLFW_RELEASE;
}


f64 GLFWWindow::getMouseX() {
	f64 x, y;
	glfwGetCursorPos(m_glfwWindow, &x, &y);
	return x;
}

f64 GLFWWindow::getMouseY() {
	f64 x, y;
	glfwGetCursorPos(m_glfwWindow, &x, &y);
	return y;
}

bool GLFWWindow::isMousePressed(WindowMouseButton button) {
	return glfwGetMouseButton(m_glfwWindow, windowMouseButtonToGLFWMouseButtonLookup[static_cast<int>(button)]) == GLFW_PRESS;
}

bool GLFWWindow::isMouseReleased(WindowMouseButton button) {
	return glfwGetMouseButton(m_glfwWindow, windowMouseButtonToGLFWMouseButtonLookup[static_cast<int>(button)]) == GLFW_RELEASE;
}


void GLFWWindow::display(Rendering::Color *screen, u32 width, u32 height) {}

void GLFWWindow::display(Rendering::ColorA *screen, u32 width, u32 height) {}


void GLFWWindow::makeContextCurrent() {
	glfwMakeContextCurrent(m_glfwWindow);
}


GLFWwindow *GLFWWindow::getGLFWWindow() {
	return m_glfwWindow;
}

void GLFWWindow::setCleanupGLFW(bool value) {
	m_cleanupGLFW = value;
}


const int windowKeyToGLFWKeyLookup[] = {GLFW_KEY_UNKNOWN,

                                        GLFW_KEY_ESCAPE,

                                        GLFW_KEY_F1,
                                        GLFW_KEY_F2,
                                        GLFW_KEY_F3,
                                        GLFW_KEY_F4,
                                        GLFW_KEY_F5,
                                        GLFW_KEY_F6,
                                        GLFW_KEY_F7,
                                        GLFW_KEY_F8,
                                        GLFW_KEY_F9,
                                        GLFW_KEY_F10,
                                        GLFW_KEY_F11,
                                        GLFW_KEY_F12,

                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_EQUAL,
                                        GLFW_KEY_RIGHT_BRACKET,
                                        GLFW_KEY_LEFT_BRACKET,
                                        GLFW_KEY_BACKSLASH,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_SEMICOLON,

                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_COMMA,
                                        GLFW_KEY_PERIOD,
                                        GLFW_KEY_SLASH,
                                        GLFW_KEY_BACKSPACE,
                                        GLFW_KEY_TAB,
                                        GLFW_KEY_SPACE,
                                        GLFW_KEY_UNKNOWN,
                                        GLFW_KEY_ENTER,
                                        GLFW_KEY_LEFT_SHIFT,
                                        GLFW_KEY_LEFT_CONTROL,
                                        GLFW_KEY_LEFT_ALT,
                                        GLFW_KEY_LEFT_SUPER,
                                        GLFW_KEY_RIGHT_SHIFT,
                                        GLFW_KEY_RIGHT_CONTROL,
                                        GLFW_KEY_RIGHT_ALT,
                                        GLFW_KEY_RIGHT_SUPER,

                                        GLFW_KEY_1,
                                        GLFW_KEY_2,
                                        GLFW_KEY_3,
                                        GLFW_KEY_4,
                                        GLFW_KEY_5,
                                        GLFW_KEY_6,
                                        GLFW_KEY_7,
                                        GLFW_KEY_8,
                                        GLFW_KEY_9,
                                        GLFW_KEY_0,

                                        GLFW_KEY_A,
                                        GLFW_KEY_B,
                                        GLFW_KEY_C,
                                        GLFW_KEY_D,
                                        GLFW_KEY_E,
                                        GLFW_KEY_F,
                                        GLFW_KEY_G,
                                        GLFW_KEY_H,
                                        GLFW_KEY_I,
                                        GLFW_KEY_J,
                                        GLFW_KEY_K,
                                        GLFW_KEY_L,
                                        GLFW_KEY_M,
                                        GLFW_KEY_N,
                                        GLFW_KEY_O,
                                        GLFW_KEY_P,
                                        GLFW_KEY_Q,
                                        GLFW_KEY_R,
                                        GLFW_KEY_S,
                                        GLFW_KEY_T,
                                        GLFW_KEY_U,
                                        GLFW_KEY_V,
                                        GLFW_KEY_W,
                                        GLFW_KEY_X,
                                        GLFW_KEY_Y,
                                        GLFW_KEY_Z,

                                        GLFW_KEY_UP,
                                        GLFW_KEY_DOWN,
                                        GLFW_KEY_LEFT,
                                        GLFW_KEY_RIGHT};

const int windowMouseButtonToGLFWMouseButtonLookup[] = {GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE};
