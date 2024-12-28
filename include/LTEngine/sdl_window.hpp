#ifndef _LTENGINE_SDL_WINDOW_HPP_
#define _LTENGINE_SDL_WINDOW_HPP_
#ifdef LTENGINE_SDL_ENABLE

#include <SDL2/SDL.h>

#include <LTEngine/window.hpp>


namespace LTEngine {
	class LTENGINE_API SDLWindow : public Window {
	public:
		SDLWindow(const char *title, u32 width, u32 height);
		~SDLWindow() override;

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
		bool isFocused() override;

		void pollEvents() override;
		void clear(Rendering::ColorA color);
		void present();

		bool shouldClose() override;

		bool isKeyPressed(WindowKey key) override;
		bool isKeyReleased(WindowKey key) override;

		f64 getMouseX() override;
		f64 getMouseY() override;
		bool isMousePressed(WindowMouseButton button) override;
		bool isMouseReleased(WindowMouseButton button) override;

		void display(Rendering::Color *screen, u32 width, u32 height) override;
		void display(Rendering::ColorA *screen, u32 width, u32 height) override;

		SDL_Window *getWindow() {
			return m_window;
		}
		SDL_Renderer *getRenderer() {
			return m_renderer;
		}

		void showMessageBox(SDL_MessageBoxFlags flags, const char *title, const char *message);

	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;

		SDL_Texture *m_rgbTexture;
		u32 m_rgbTextureWidth;
		u32 m_rgbTextureHeight;

		SDL_Texture *m_rgbaTexture;
		u32 m_rgbaTextureWidth;
		u32 m_rgbaTextureHeight;

		bool m_shouldClose = false;
	};
} // namespace LTEngine

#endif
#endif
