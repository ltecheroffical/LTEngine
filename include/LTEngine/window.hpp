#ifndef _LTENGINE_WINDOW_HPP_
#define _LTENGINE_WINDOW_HPP_

#include <LTEngine/event.hpp>

#include <LTEngine/rendering/color.hpp>


namespace LTEngine {
	enum class LTENGINE_API WindowKey {
		Unknown = 0,

		Escape,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		Exclamation,
		At,
		Pound,
		Dollar,
		Percent,
		Caret,
		AmperSAND,
		AsterISK,
		LeftParenthesis,
		RightParenthesis,
		Hyphen,
		Plus,
		Equal,
		RightBracket,
		LeftBracket,
		Backslash,
		Pipe,
		Semicolon,

		Colon,
		Quote,
		Backquote,
		Comma,
		Period,
		Slash,
		Backspace,
		Tab,
		Space,
		Return,
		Enter,
		LeftShift,
		LeftControl,
		LeftAlt,
		LeftSuper,
		RightShift,
		RightControl,
		RightAlt,
		RightSuper,

		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,

		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		Up,
		Down,
		Left,
		Right,

		Count
	};

	enum class WindowMouseButton { MouseLeft, MouseRight, MouseMiddle };

	/**
	 * @brief The window interface for all windows.
	 *
	 * @details
	 * All window implementations for LTEngine must implement this interface. This is a type that can be created without anything
	 * else.
	 */
	class LTENGINE_API Window {
	public:
		virtual ~Window() = default;

		Event<> onWindowClose;

		Event<> onWindowFocus;
		Event<> onWindowUnfocus;

		// The event signature is (u32 width, u32 height)
		Event<u32, u32> onWindowResize;
		Event<> onWindowMinimize;
		Event<> onWindowRestore;

		// The event signature is (u32 x, u32 y)
		Event<u32, u32> onWindowMove;

		Event<WindowKey> onWindowKeyPress;
		Event<WindowKey> onWindowKeyRelease;

		Event<WindowMouseButton> onWindowMousePress;
		Event<WindowMouseButton> onWindowMouseRelease;


		virtual void setSize(u32 width, u32 height) = 0;
		virtual void setPosition(u32 x, u32 y) = 0;
		virtual void setTitle(const char *title) = 0;
		virtual void setResizable(bool resizable) = 0;
		virtual void setFullscreen(bool fullscreen) = 0;
		virtual void setMinimized(bool minimized) = 0;

		virtual void show() = 0;
		virtual void hide() = 0;

		virtual u32 getWidth() = 0, getHeight() = 0;
		virtual u32 getX() = 0, getY() = 0;
		virtual const char *getTitle() = 0;
		virtual bool isResizable() = 0;
		virtual bool isFullscreen() = 0;
		virtual bool isMinimized() = 0;
		virtual bool isHidden() = 0;
		virtual bool isFocused() = 0;

		virtual void pollEvents() = 0;

		virtual bool shouldClose() = 0;

		virtual bool isKeyPressed(WindowKey key) = 0;
		virtual bool isKeyReleased(WindowKey key) = 0;

		virtual f64 getMouseX() = 0;
		virtual f64 getMouseY() = 0;
		virtual bool isMousePressed(WindowMouseButton button) = 0;
		virtual bool isMouseReleased(WindowMouseButton button) = 0;

		/**
		 * @brief Displays an image on the window.
		 *
		 * @param screen The image to display in RGB24 format, no padding
		 * @param width The width of the image.
		 * @param height The height of the image.
		 *
		 * @details
		 * The image must be in RGB24 format, no padding.
		 * The image size is calculated automatiically by the width and height.
		 *
		 *  WARNING: THIS MAY THROW AN ERROR ON ALL WINDOW TYPES BECAUSE IT IS NOT NEEDED TO BE IMPLEMENTED
		 */
		virtual void display(Rendering::Color *screen, u32 width, u32 height) = 0;
		/**
		 * @brief Displays an image on the window.
		 *
		 * @param screen The image to display in RGBA32 format, no padding.
		 * @param width The width of the image.
		 * @param height The height of the image.
		 *
		 *  WARNING: THIS MAY THROW AN ERROR ON ALL WINDOW TYPES BECAUSE IT IS NOT NEEDED TO BE IMPLEMENTED

		 */
		virtual void display(Rendering::ColorA *screen, u32 width, u32 height) = 0;
	};
} // namespace LTEngine

#endif
