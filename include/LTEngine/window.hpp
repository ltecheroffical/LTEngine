#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
    class Window {
    public:
        Window(char *title, u32 width, u32 height);
        virtual ~Window() = 0;
        
        virtual void close() = 0;

        virtual void set_size(u32 width, u32 height) = 0;
        virtual void set_position(u32 x, u32 y) = 0;
        virtual void set_title(char *title) = 0;
        virtual void set_fullscreen(bool fullscreen) = 0;
        virtual void set_minimized(bool minimized) = 0;

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual u32 get_width(), get_height() = 0;
        virtual u32 get_x(), get_y() = 0;
        virtual char *get_title() = 0;
        virtual bool is_fullscreen() = 0;
        virtual bool is_minimized() = 0;
        virtual bool is_hidden();

        virtual void poll_events() = 0;

        virtual bool should_close() = 0;
    };
}
