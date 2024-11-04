#pragma once

#include <vector>

#include <LTEngine/rendering/renderer.hpp>
#include <LTEngine/rendering/cpu_shader.hpp>


namespace LTEngine::Rendering {
    class SoftwareRenderer : Renderer {
    public:
        SoftwareRenderer(u32 width, u32 height);
        ~SoftwareRenderer() override;

        void resize(u32 width, u32 height);

        u32 getScreenData(Color *data) override;

        void clear(Color color) override;
        void clear(ColorA color) override;

        void setPixel(Math::Vec2i position, Color color) override;
        void setPixel(Math::Vec2i position, ColorA color) override;
        Color getPixel(Math::Vec2i position) override;

        void drawRect(Math::Rect rect, ColorA color, RendererFlags flags) override;
        void drawCircle(Math::Vec2 position, f32 radius, ColorA color, RendererFlags flags) override;
        void drawTriangle(Math::Vec2 a, Math::Vec2 b, Math::Vec2 c, ColorA color, RendererFlags flags);

        void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
        void drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) override;

        void drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) override;
        void drawCamera(u32 id, Math::Recti rect, ColorA color, RendererFlags flags) override;

        void setShader(CPUShader *shader);
        void clearShader();


    private:
        std::vector<Color> m_screen;
        u32 m_screenWidth;
        u32 m_screenHeight;

        std::vector<ColorA> m_bufferData;
        u32 m_bufferWidth = 0;
        u32 m_bufferHeight = 0;

        CPUShader *m_shader = nullptr;
    };
}
