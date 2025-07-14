#if !_LTENGINE_SDL_WINDOW_HPP_ && LTENGINE_COMPONENT_SDL
#define _LTENGINE_SDL_WINDOW_HPP_

#include <SDL3/SDL.h>

#include <LTEngine/window.hpp>

namespace LTEngine {
class LTENGINE_API SDLWindow : public Window, IWindowControllerInput, IWindowClipboard {
  public:
	SDLWindow(const char *title, Math::Vec2 size, SDL_WindowFlags flags);
	~SDLWindow();

	void setBounds(Shapes::Recti region) override;
	void setTitle(const char *title) override;
	void setResizable(bool resizable) override;
	void setFullscreen(bool fullscreen) override;
	void setMinimized(bool minimized) override;

	Shapes::Recti getBounds() override;
	std::string getTitle() override;
	bool isResizable() override;
	bool isFullscreen() override;
	bool isMinimized() override;
	bool isHidden() override;
	bool isFocused() override;

	void show() override;
	void hide() override;

	void update() override;

	bool shouldClose() override;


	bool isKeyDown(ScanCode code) override;
	bool isKeyUp(ScanCode code) override;

	Math::Vec2 getMousePosition() override;
	bool isMouseButtonDown(MouseButton button) override;
	bool isMouseButtonUp(MouseButton button) override;


	std::vector<u32> getControllers() override;

	bool isControllerButtonDown(u32 gamepad, ControllerButton button) override;
	bool isControllerButtonUp(u32 gamepad, ControllerButton button) override;

	Math::Vec2 getControllerAnalog(u32 gamepad, ControllerAnalogStick stick) override;


	std::string getClipboardMimeType() override;

	void copyClipboard(const u8 *data, size_t size, const char *mimeType) override;
	std::vector<u8> pasteBytesClipboard() override;


	SDL_Window *getWindow();

  private:
	bool m_isClosed = false;

	bool m_isScrollingUp = false;
	bool m_isScrollingDown = false;

	SDL_Window *m_window;
};
} // namespace LTEngine

#endif // _LTENGINE_SDL_WINDOW_HPP_
