#pragma once

#include <unordered_map>

#include <LTEngine/rendering/renderer.hpp>
#include <LTEngine/rendering/cpu_shader.hpp>


namespace LTEngine::Rendering {
    class SoftwareRenderer : public Renderer {
    public: 
        SoftwareRenderer(u32 width, u32 height);
        ~SoftwareRenderer() override = default;

        enum class ScalingMode {
            SCALING_MODE_NEAREST,
            SCALING_MODE_LINEAR
        };

        void resize(u32 width, u32 height);

        u32 getScreenData(Color *data);
        void setScreenOnly();
        void clearScreenOnly();

        void clear(Color color) override;
        void clear(ColorA color) override;

        void setPixel(Math::Vec2i position, Color color) override;
        void setPixel(Math::Vec2i position, ColorA color) override;
        Color getPixel(Math::Vec2i position) override;

        void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
        void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) override;

        void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
        void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

        void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color, RendererFlags flags) override;
        void drawCamera(u32 id, Shapes::Recti rect, ColorA color, RendererFlags flags);

        void setScalingMode(ScalingMode mode);

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

        ScalingMode m_scalingMode;

        std::unordered_map<u32, std::vector<Color>> m_cameraOutputs;
        std::unordered_map<u32, std::vector<u16>> m_cameraDepth;

        std::vector<Color> m_screen;
        std::vector<u16> m_screenDepth;
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
