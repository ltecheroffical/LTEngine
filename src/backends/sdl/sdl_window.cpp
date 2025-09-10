#ifdef LTENGINE_COMPONENT_SDL

#include <LTEngine/sdl/sdl_window.hpp>

using namespace LTEngine;

SDLWindow::SDLWindow(const char *title, Math::Vec2 size, SDL_WindowFlags flags) {
	if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
			throw std::runtime_error("Could not properly initalize SDL! " + std::string(SDL_GetError()));
		}
	}

	m_window = SDL_CreateWindow(title, size.x, size.y, flags);
	if (m_window == NULL) {
		throw std::runtime_error("SDL_Window could not be created! " + std::string(SDL_GetError()));
	}
}

SDLWindow::~SDLWindow() {
	SDL_DestroyWindow(m_window);
	m_isClosed = true;
}

void SDLWindow::setBounds(Shapes::Recti region) {
	SDL_SetWindowPosition(m_window, region.x, region.y);
	SDL_SetWindowSize(m_window, region.w, region.h);
}

void SDLWindow::setTitle(const char *title) {
	SDL_SetWindowTitle(m_window, title);
}

void SDLWindow::setResizable(bool resizable) {
	SDL_SetWindowResizable(m_window, resizable);
}

void SDLWindow::setFullscreen(bool fullscreen) {
	SDL_SetWindowFullscreen(m_window, fullscreen);
}

void SDLWindow::setMinimized(bool minimized) {
	if (minimized) {
		SDL_MinimizeWindow(m_window);
	} else if (!minimized && SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) {
		SDL_RestoreWindow(m_window);
	}
}

Shapes::Recti SDLWindow::getBounds() {
	Shapes::Recti rect = {0, 0, 0, 0};
	SDL_GetWindowPosition(m_window, (int *)&rect.x, (int *)&rect.y);
	SDL_GetWindowSize(m_window, (int *)&rect.w, (int *)&rect.h);
	return rect;
}

std::string SDLWindow::getTitle() {
	return SDL_GetWindowTitle(m_window);
}

bool SDLWindow::isResizable() {
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_RESIZABLE;
}

bool SDLWindow::isFullscreen() {
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_FULLSCREEN;
}

bool SDLWindow::isMinimized() {
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED;
}

bool SDLWindow::isHidden() {
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_HIDDEN;
}

bool SDLWindow::isFocused() {
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_MOUSE_FOCUS;
}

void SDLWindow::show() {
	SDL_ShowWindow(m_window);
}

void SDLWindow::hide() {
	SDL_HideWindow(m_window);
}

void SDLWindow::update() {
	m_isScrollingUp = false;
	m_isScrollingDown = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED: {
				m_isClosed = true;
				onWindowClose();
				break;
			}

			case SDL_EVENT_MOUSE_WHEEL: {
				i32 y = event.wheel.y;

				if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
					y = -y;
				}

				m_isScrollingUp = y > 0;
				m_isScrollingDown = y < 0;
			}

			case SDL_EVENT_WINDOW_FOCUS_GAINED: {
				onWindowFocus();
				break;
			}
			case SDL_EVENT_WINDOW_FOCUS_LOST: {
				onWindowUnfocus();
			}

			case SDL_EVENT_WINDOW_RESIZED: {
				onWindowResize(Math::Vec2i{event.window.data1, event.window.data2});
				break;
			}
			case SDL_EVENT_WINDOW_MINIMIZED: {
				onWindowMinimize();
			}
			case SDL_EVENT_WINDOW_RESTORED: {
				onWindowRestore();
			}

			case SDL_EVENT_WINDOW_MOVED: {
				onWindowMove(Math::Vec2i{event.window.data1, event.window.data2});
				break;
			}
		}
	}
}

bool SDLWindow::shouldClose() {
	return m_isClosed;
}

bool SDLWindow::isKeyDown(ScanCode code) {
	return SDL_GetKeyboardState(nullptr)[(u32)code];
}

bool SDLWindow::isKeyUp(ScanCode code) {
	return !isKeyDown(code);
}

Math::Vec2 SDLWindow::getMousePosition() {
	Math::Vec2 position;
	SDL_GetMouseState(&position.x, &position.y);
	return position;
}

bool SDLWindow::isMouseButtonDown(MouseButton button) {
	u32 mask = 0;

	switch (button) {
		case MouseButton::Left: mask = SDL_BUTTON_LMASK; break;
		case MouseButton::Right: mask = SDL_BUTTON_RMASK; break;
		case MouseButton::Middle: mask = SDL_BUTTON_MMASK; break;
		case MouseButton::MiddleDown: return m_isScrollingDown;
		case MouseButton::MiddleUp: return m_isScrollingUp;
		default: return false;
	}

	return SDL_GetMouseState(nullptr, nullptr) & mask;
}

bool SDLWindow::isMouseButtonUp(MouseButton button) {
	return !isMouseButtonDown(button);
}

std::vector<u32> SDLWindow::getControllers() {
	i32 count = 0;
	SDL_JoystickID *joysticks = SDL_GetJoysticks(&count);

	if (joysticks == NULL || count < 0) {
		throw std::runtime_error("Failed to get controllers! " + std::string(SDL_GetError()));
	}

	std::vector<u32> controllers(count);
	memcpy(controllers.data(), joysticks, controllers.size());

	SDL_free(joysticks);
	return controllers;
}

bool SDLWindow::isControllerButtonDown(u32 gamepad, ControllerButton button) {
	SDL_Gamepad *controller = SDL_OpenGamepad(gamepad);
	LTENGINE_RETURN_VALUE_NULL(controller, false);

	bool result = false;
	switch (button) {
		case ControllerButton::A: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_SOUTH); break;
		case ControllerButton::B: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_EAST); break;
		case ControllerButton::X: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_WEST); break;
		case ControllerButton::Y: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_NORTH); break;

		case ControllerButton::DPadUp: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_DPAD_UP); break;
		case ControllerButton::DPadDown: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_DPAD_DOWN); break;
		case ControllerButton::DPadLeft: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_DPAD_LEFT); break;
		case ControllerButton::DPadRight: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_DPAD_RIGHT); break;

		case ControllerButton::LeftBumper: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER); break;
		case ControllerButton::RightBumper: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER); break;
		case ControllerButton::LeftTrigger: result = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) > 16000; break;
		case ControllerButton::RightTrigger: result = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > 16000; break;

		case ControllerButton::LeftStick: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_LEFT_STICK); break;
		case ControllerButton::RightStick: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_RIGHT_STICK); break;

		case ControllerButton::Start: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_START); break;
		case ControllerButton::Back: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_BACK); break;

		case ControllerButton::Home: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_GUIDE); break;

		case ControllerButton::Touchpad: result = SDL_GetGamepadButton(controller, SDL_GAMEPAD_BUTTON_TOUCHPAD); break;
	}
	SDL_CloseGamepad(controller);
	return result;
}

bool SDLWindow::isControllerButtonUp(u32 gamepad, ControllerButton button) {
	return !isControllerButtonDown(gamepad, button);
}

Math::Vec2 SDLWindow::getControllerAnalog(u32 gamepad, ControllerAnalogStick stick) {
	SDL_Gamepad *controller = SDL_OpenGamepad(gamepad);
	LTENGINE_RETURN_VALUE_NULL(controller, Math::Vec2::Zero);

	i16 x = 0, y = 0;
	switch (stick) {
		case ControllerAnalogStick::Left:
			x = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_LEFTX);
			y = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_LEFTY);
		case ControllerAnalogStick::Right:
			x = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_RIGHTX);
			y = SDL_GetGamepadAxis(controller, SDL_GAMEPAD_AXIS_RIGHTY);
	}

	SDL_CloseGamepad(controller);
	return Math::Vec2{
	    (f32)x / std::numeric_limits<i16>::max(),
	    (f32)y / std::numeric_limits<i16>::max()};
}

std::string SDLWindow::getClipboardMimeType() {
	size_t mime_type_count = 0;
	char **mime_types = SDL_GetClipboardMimeTypes(&mime_type_count);
	LTENGINE_RETURN_VALUE_NULL(mime_types, "");

	auto mine_string = std::string(mime_types[0]);
	SDL_free(mime_types);

	return mine_string;
}

void SDLWindow::copyClipboard(const u8 *data, size_t size, const char *mimeType) {
	std::vector<u8> mimeTypeData;
	mimeTypeData.insert(mimeTypeData.end(),
	                    reinterpret_cast<const u8 *>(&mimeType),
	                    reinterpret_cast<const u8 *>(&mimeType) + sizeof(mimeType));
	mimeTypeData.push_back(0x0);

	std::vector<u8> clipboardDataCallbackCtx;
	clipboardDataCallbackCtx.insert(clipboardDataCallbackCtx.end(),
	                                reinterpret_cast<const u8 *>(&data),
	                                reinterpret_cast<const u8 *>(&data) + sizeof(data));
	clipboardDataCallbackCtx.insert(clipboardDataCallbackCtx.end(),
	                                reinterpret_cast<const u8 *>(&size),
	                                reinterpret_cast<const u8 *>(&size) + sizeof(size));

	SDL_SetClipboardData([](void *ctx, const char *data, size_t *size) -> const void * {
		*size = *reinterpret_cast<size_t *>((void*)((size_t)&data + sizeof(const u8 *)));
		return ctx; },
	                     [](void *) {}, clipboardDataCallbackCtx.data(), (const char **)mimeTypeData.data(), mimeTypeData.size());
}

std::vector<u8> SDLWindow::pasteBytesClipboard() {
	std::vector<u8> data;
	size_t size = 0;

	const u8 *data_ptr = (const u8 *)SDL_GetClipboardData(getClipboardMimeType().c_str(), &size);
	data.resize(size);
	memcpy(data.data(), data_ptr, size);
	return data;
}

SDL_Window *SDLWindow::getWindow() {
	return m_window;
}

#endif // LTENGINE_COMPONENT_SDL
