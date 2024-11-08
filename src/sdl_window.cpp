#ifdef LTENGINE_SDL_ENABLE

#include <string>
#include <stdexcept>

#include <LTEngine/sdl_window.hpp>


using namespace LTEngine;


SDLWindow::SDLWindow(const char *title, u32 width, u32 height) {
    if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    }
    
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        throw std::runtime_error("Failed to create SDL window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        throw std::runtime_error("Failed to create SDL renderer");
    }

    m_rgbTexture = nullptr;
    m_rgbaTexture = nullptr;
}

SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}


void SDLWindow::setSize(u32 width, u32 height) {
    SDL_SetWindowSize(m_window, width, height);
}

void SDLWindow::setPosition(u32 x, u32 y) {
    SDL_SetWindowPosition(m_window, x, y);
}

void SDLWindow::setTitle(const char *title) {
    SDL_SetWindowTitle(m_window, title);
}

void SDLWindow::setResizable(bool resizable) {
    SDL_SetWindowResizable(m_window, resizable ? SDL_TRUE : SDL_FALSE);
}

void SDLWindow::setFullscreen(bool fullscreen) {
    SDL_SetWindowFullscreen(m_window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void SDLWindow::setMinimized(bool minimized) {
    if (minimized) {
        SDL_MinimizeWindow(m_window);
    } else {
        SDL_RestoreWindow(m_window);
    }
}


void SDLWindow::show() {
    SDL_ShowWindow(m_window);
}

void SDLWindow::hide() {
    SDL_HideWindow(m_window);
}


u32 SDLWindow::getWidth() {
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    return w;
}

u32 SDLWindow::getHeight() {
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    return h;
}


u32 SDLWindow::getX() {
    int x, y;
    SDL_GetWindowPosition(m_window, &x, &y);
    return x;
}

u32 SDLWindow::getY() {
    int x, y;
    SDL_GetWindowPosition(m_window, &x, &y);
    return y;
}

const char *SDLWindow::getTitle() {
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


void SDLWindow::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_shouldClose = true;
                return;
        }
    }
}

void SDLWindow::clear(Rendering::ColorA color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void SDLWindow::present() {
    SDL_RenderPresent(m_renderer);
}


bool SDLWindow::shouldClose() {
    return m_shouldClose;
}


extern const int windowKeyToSDLKeyLookup[];
extern const int windowMouseButtonToSDLMouseButtonLookup[];

bool SDLWindow::isKeyPressed(WindowKey key) {
    return SDL_GetKeyboardState(nullptr)[windowKeyToSDLKeyLookup[static_cast<int>(key)]];
}

bool SDLWindow::isKeyReleased(WindowKey key) {
    return !SDL_GetKeyboardState(nullptr)[windowKeyToSDLKeyLookup[static_cast<int>(key)]];
}


f64 SDLWindow::getMouseX() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x;
}

f64 SDLWindow::getMouseY() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return y;
}

bool SDLWindow::isMousePressed(WindowMouseButton button) {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(windowMouseButtonToSDLMouseButtonLookup[static_cast<int>(button)]);
}

bool SDLWindow::isMouseReleased(WindowMouseButton button) {
    return !(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(windowMouseButtonToSDLMouseButtonLookup[static_cast<int>(button)]));
}


void SDLWindow::display(Rendering::Color *screen, u32 width, u32 height) {
    if (m_rgbTexture == nullptr || m_rgbTextureWidth != width || m_rgbTextureHeight != height) {
        m_rgbTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);
        m_rgbTextureWidth = width;
        m_rgbTextureHeight = height;
    }

    int pitch = 0;
    void *pixels = nullptr;
    if (SDL_LockTexture(m_rgbTexture, nullptr, &pixels, &pitch) != 0) {
        throw std::runtime_error("Failed to lock texture! SDL error: " + std::string(SDL_GetError()));
    }

    memcpy(pixels, screen, width * height * sizeof(Rendering::Color));
    SDL_UnlockTexture(m_rgbTexture);
    SDL_RenderCopy(m_renderer, m_rgbTexture, nullptr, nullptr);
}

void SDLWindow::display(Rendering::ColorA *screen, u32 width, u32 height) {
    if (m_rgbaTexture == nullptr || m_rgbaTextureWidth != width || m_rgbaTextureHeight != height) {
        m_rgbaTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
        m_rgbaTextureWidth = width;
        m_rgbaTextureHeight = height;
    }

    int pitch = 0;
    void *pixels = nullptr;
    if (SDL_LockTexture(m_rgbaTexture, nullptr, &pixels, &pitch) != 0) {
        throw std::runtime_error("Failed to lock texture! SDL error: " + std::string(SDL_GetError()));
    }

    memcpy(pixels, screen, width * height * sizeof(Rendering::ColorA));
    SDL_UnlockTexture(m_rgbaTexture);
    SDL_RenderCopy(m_renderer, m_rgbaTexture, nullptr, nullptr);
}


void SDLWindow::showMessageBox(SDL_MessageBoxFlags flags, const char *title, const char *message) {
    SDL_ShowSimpleMessageBox(flags, title, message, nullptr);
}




const int windowKeyToSDLKeyLookup[] = {
    SDL_SCANCODE_UNKNOWN,

    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_F1,
    SDL_SCANCODE_F2,
    SDL_SCANCODE_F3,
    SDL_SCANCODE_F4,
    SDL_SCANCODE_F5,
    SDL_SCANCODE_F6,
    SDL_SCANCODE_F7,
    SDL_SCANCODE_F8,
    SDL_SCANCODE_F9,
    SDL_SCANCODE_F10,
    SDL_SCANCODE_F11,
    SDL_SCANCODE_F12,

    SDL_SCANCODE_KP_EXCLAM,
    SDL_SCANCODE_KP_AT,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_KP_PERCENT,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_KP_AMPERSAND,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_KP_LEFTPAREN,
    SDL_SCANCODE_KP_RIGHTPAREN,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_KP_PLUS,
    SDL_SCANCODE_KP_EQUALS,
    SDL_SCANCODE_RIGHTBRACKET,
    SDL_SCANCODE_LEFTBRACKET,
    SDL_SCANCODE_BACKSLASH,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_SEMICOLON,

    SDL_SCANCODE_KP_COLON,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_COMMA,
    SDL_SCANCODE_PERIOD,
    SDL_SCANCODE_SLASH,
    SDL_SCANCODE_BACKSPACE,
    SDL_SCANCODE_TAB,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_RETURN,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_LSHIFT,
    SDL_SCANCODE_LCTRL,
    SDL_SCANCODE_LALT,
    SDL_SCANCODE_UNKNOWN,
    SDL_SCANCODE_RSHIFT,
    SDL_SCANCODE_RCTRL,
    SDL_SCANCODE_RALT,
    SDL_SCANCODE_UNKNOWN,

    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_4,
    SDL_SCANCODE_5,
    SDL_SCANCODE_6,
    SDL_SCANCODE_7,
    SDL_SCANCODE_8,
    SDL_SCANCODE_9,
    SDL_SCANCODE_0,

    SDL_SCANCODE_A,
    SDL_SCANCODE_B,
    SDL_SCANCODE_C,
    SDL_SCANCODE_D,
    SDL_SCANCODE_E,
    SDL_SCANCODE_F,
    SDL_SCANCODE_G,
    SDL_SCANCODE_H,
    SDL_SCANCODE_I,
    SDL_SCANCODE_J,
    SDL_SCANCODE_K,
    SDL_SCANCODE_L,
    SDL_SCANCODE_M,
    SDL_SCANCODE_N,
    SDL_SCANCODE_O,
    SDL_SCANCODE_P,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_R,
    SDL_SCANCODE_S,
    SDL_SCANCODE_T,
    SDL_SCANCODE_U,
    SDL_SCANCODE_V,
    SDL_SCANCODE_W,
    SDL_SCANCODE_X,
    SDL_SCANCODE_Y,
    SDL_SCANCODE_Z,

    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
};

const int windowMouseButtonToSDLMouseButtonLookup[] = {
    SDL_BUTTON_LEFT,
    SDL_BUTTON_RIGHT,
    SDL_BUTTON_MIDDLE
};

#endif
