#pragma once

#include <LTEngine/rendering/color.hpp>

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>


namespace LTEngine {
    enum class WindowKey {
        KEY_UNKNOWN = 0,

        KEY_ESCAPE,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,

        KEY_EXCLAMATION,
        KEY_AT,
        KEY_POUND,
        KEY_DOLLAR,
        KEY_PERCENT,
        KEY_CARET,
        KEY_AMPERSAND,
        KEY_ASTERISK,
        KEY_LEFT_PARENTHESIS,
        KEY_RIGHT_PARENTHESIS,
        KEY_HYPHEN,
        KEY_PLUS,
        KEY_EQUAL,
        KEY_RIGHT_BRACKET,
        KEY_LEFT_BRACKET,
        KEY_BACKSLASH,
        KEY_PIPE,
        KEY_SEMICOLON,

        KEY_COLON,
        KEY_QUOTE,
        KEY_BACKQUOTE,
        KEY_COMMA,
        KEY_PERIOD,
        KEY_SLASH,
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_SPACE,
        KEY_RETURN,
        KEY_ENTER,
        KEY_LEFT_SHIFT,
        KEY_LEFT_CONTROL,
        KEY_LEFT_ALT,
        KEY_LEFT_SUPER,
        KEY_RIGHT_SHIFT,
        KEY_RIGHT_CONTROL,
        KEY_RIGHT_ALT,
        KEY_RIGHT_SUPER,

        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,

        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,

        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,

        KEY_COUNT
    };

    enum class WindowMouseButton {
        MOUSE_LEFT,
        MOUSE_RIGHT,
        MOUSE_MIDDLE
    };

    class Window {
    public:
        virtual ~Window() = default;

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

        virtual void pollEvents() = 0;

        virtual bool shouldClose() = 0;

        virtual bool isKeyPressed(WindowKey key) = 0;
        virtual bool isKeyReleased(WindowKey key) = 0;
        
        virtual f64 getMouseX() = 0;
        virtual f64 getMouseY() = 0;
        virtual bool isMousePressed(WindowMouseButton button) = 0;
        virtual bool isMouseReleased(WindowMouseButton button) = 0;

        virtual void display(Rendering::Color *screen, u32 width, u32 height) = 0;
        virtual void display(Rendering::ColorA *screen, u32 width, u32 height) = 0;
    };
}
