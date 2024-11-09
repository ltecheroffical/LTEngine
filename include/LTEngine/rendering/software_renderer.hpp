#pragma once

#include <unordered_map>

#include <LTEngine/rendering/renderer.hpp>
#include <LTEngine/rendering/cpu_shader.hpp>


namespace LTEngine::Rendering {
    class SoftwareRenderer : public Renderer {
    public: 
        SoftwareRenderer(u32 width, u32 height);
        ~SoftwareRenderer() override = default;

        void resize(u32 width, u32 height);

        u32 getScreenData(Color *data);
        void setScreenOnly();
        void clearScreenOnly();

        void clear(Color color) override;
        void clear(ColorA color) override;

        void setPixel(Math::Vec2i position, Color color) override;
        void setPixel(Math::Vec2i position, ColorA color) override;
        Color getPixel(Math::Vec2i position) override;

        void drawRect(Math::Rect rect, ColorA color, RendererFlags flags) override;
        void drawCircle(Math::Vec2 centerPosition, f32 radius, ColorA color, RendererFlags flags) override;

        void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
        void drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) override;

        void drawImage(const Image *image, Math::Vec2i position, Math::Recti region, ColorA color, RendererFlags flags) override;
        void drawCamera(u32 id, Math::Recti rect, ColorA color, RendererFlags flags);

        void setShader(CPUShader *shader);
        void clearShader();

    private:
        void prepareBuffer(u32 width, u32 height);
        void drawBufferPixel(u32 x, u32 y, ColorA color);
        void flushBuffer(i32 x, i32 y);

        void cameraCreated(u32 id) override;
        void cameraDestroyed(u32 id) override;
        void cameraSelected(u32 id) override;
        void cameraDeselected() override;

        std::unordered_map<u32, std::vector<Color>> m_cameraOutputs;

        std::vector<Color> m_screen;
        u32 m_screenWidth;
        u32 m_screenHeight;

        std::vector<ColorA> m_bufferData;
        u32 m_bufferWidth = 0;
        u32 m_bufferHeight = 0;

        bool m_screenOnly:1 = false;
        bool m_cameraSelected:1 = false;

        CPUShader *m_shader = nullptr;
    };
}
