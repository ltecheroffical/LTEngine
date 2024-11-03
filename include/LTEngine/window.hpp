#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
    class Window {
    public:
        Window(char *title, u32 width, u32 height);
        virtual ~Window() = 0;
        
        virtual void close() = 0;

        virtual void setSize(u32 width, u32 height) = 0;
        virtual void setPosition(u32 x, u32 y) = 0;
        virtual void setTitle(char *title) = 0;
        virtual void setFullscreen(bool fullscreen) = 0;
        virtual void setMinimized(bool minimized) = 0;

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual u32 getWidth(), getHeight() = 0;
        virtual u32 getX(), getY() = 0;
        virtual char *getTitle() = 0;
        virtual bool isFullscreen() = 0;
        virtual bool isMinimized() = 0;
        virtual bool isHidden();

        virtual void pollEvents() = 0;

        virtual bool shouldClose() = 0;
    };
}
