#ifndef _LTENGINE_WINDOW_HPP_
#define _LTENGINE_WINDOW_HPP_

#include <LTEngine/event.hpp>

#include <LTEngine/input.hpp>

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/shapes/2d/rect.hpp>

namespace LTEngine {
class Window {
  public:
	virtual ~Window() = default;

	Event<> onWindowClose;

	Event<> onWindowFocus;
	Event<> onWindowUnfocus;

	Event<Math::Vec2i /* size */> onWindowResize;
	Event<> onWindowMinimize;
	Event<> onWindowRestore;

	Event<Math::Vec2i /* position */> onWindowMove;


	virtual void setBounds(Shapes::Recti region) = 0;
	virtual void setTitle(const char *title) = 0;
	virtual void setResizable(bool resizable) = 0;
	virtual void setFullscreen(bool fullscreen) = 0;
	virtual void setMinimized(bool minimized) = 0;

	virtual Shapes::Recti getBounds() = 0;
	virtual std::string getTitle() = 0;
	virtual bool isResizable() = 0;
	virtual bool isFullscreen() = 0;
	virtual bool isMinimized() = 0;
	virtual bool isHidden() = 0;
	virtual bool isFocused() = 0;

	virtual void show() = 0;
	virtual void hide() = 0;

	virtual void update() = 0;

	virtual bool shouldClose() = 0;

	Event<MouseButton /* button */> onWindowMouseButtonDown;
	Event<MouseButton /* button */> onWindowMouseButtonUp;

	Event<ScanCode /* key */> onWindowKeyDown;
	Event<ScanCode /* key */> onWindowKeyUp;

	virtual bool isKeyDown(ScanCode code) = 0;
	virtual bool isKeyUp(ScanCode code) = 0;

	virtual Math::Vec2 getMousePosition() = 0;
	virtual bool isMouseButtonDown(MouseButton button) = 0;
	virtual bool isMouseButtonUp(MouseButton button) = 0;
};

class IWindowClipboard {
  public:
	~IWindowClipboard() = default;

	virtual std::string getClipboardMimeType() = 0;

	virtual void copyClipboard(const u8 *data, size_t size, const char *mimeType) = 0;
	virtual std::vector<u8> pasteBytesClipboard() = 0;
};

class IWindowControllerInput {
  public:
	~IWindowControllerInput() = default;

	virtual std::vector<u32> getControllers() = 0;

	virtual bool isControllerButtonDown(u32 gamepad, ControllerButton button) = 0;
	virtual bool isControllerButtonUp(u32 gamepad, ControllerButton button) = 0;

	virtual Math::Vec2 getControllerAnalog(u32 gamepad, ControllerAnalogStick stick) = 0;
};
} // namespace LTEngine

#endif // _LTENGINE_WINDOW_HPP_
