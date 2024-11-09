#pragma once
#ifdef LTENGINE_SDL_ENABLE

#include <SDL2/SDL.h>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
    class SDLRenderer : public Renderer {
    public: 
        SDLRenderer(SDL_Renderer *renderer);
        ~SDLRenderer() override = default;

        void clear(Color color) override;
        void clear(ColorA color) override;

        void setPixel(Math::Vec2i position, Color color) override;
        void setPixel(Math::Vec2i position, ColorA color) override;
        Color getPixel(Math::Vec2i position) override;

        void drawRect(Math::Rect rect, ColorA color, RendererFlags flags) override;
        void drawCircle(Math::Vec2 centerPosition, f32 radius, ColorA color, RendererFlags flags) override;

        void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
        void drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) override;

        void drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) override;

    private:
        SDL_Renderer *m_renderer;
    };
}
#endif
