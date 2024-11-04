#pragma once

#include <vector>

#include <LTEngine/common/types/inttypes.h>
#include <LTEngine/common/types/floattypes.h>

#include <LTEngine/math/vec2.hpp>
#include <LTEngine/math/rect.hpp>

#include <LTEngine/rendering/color.hpp>
#include <LTEngine/rendering/image.hpp>
#include <LTEngine/rendering/camera.hpp>


namespace LTEngine::Rendering {
    typedef u16 RendererFlags;

    class Renderer {
    public:
        virtual ~Renderer() = 0;

        void setScale(Math::Vec2 scale);
        void setRotation(f32 rotation);

        void setZOrder(u16 z);

        void setRotationOffset(f32 offset);
        void setScaleFactor(Math::Vec2 scale);
        void setPositionOffset(Math::Vec2 offset);

        void setIrisMode();
        void clearIrisMode();

        u32 createCamera(Math::Vec2 position, Math::Vec2 zoom);
        void deleteCamera(u32 id);
        void setCameraPosition(u32 id, Math::Vec2 position);
        void setCameraRotation(u32 id, f32 rotation);
        void setCameraZoom(u32 id, Math::Vec2 zoom);
        void setCameraInclude(u32 id);
        void setCameraExclude(u32 id);
        Math::Vec2 getCameraPosition(u32 id) const;
        Math::Vec2 getCameraZoom(u32 id) const;
        f32 getCameraRotation(u32 id) const;

        virtual u32 getScreenData(Color *data) = 0;

        virtual void clear(Color color) = 0;
        virtual void clear(ColorA color) = 0;

        virtual void setPixel(Math::Vec2i position, Color color) = 0;
        virtual void setPixel(Math::Vec2i position, ColorA color) = 0;
        virtual Color getPixel(Math::Vec2i position) = 0;

        virtual void drawRect(Math::Rect rect, ColorA color, RendererFlags flags) = 0;
        virtual void drawCircle(Math::Vec2 position, f32 radius, ColorA color, RendererFlags flags) = 0;
        void drawTriangle(Math::Vec2 a, Math::Vec2 b, Math::Vec2 c, ColorA color, RendererFlags flags);

        virtual void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) = 0;
        virtual void drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) = 0;

        virtual void drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) = 0;
        virtual void drawCamera(u32 id, Math::Recti rect, ColorA color, RendererFlags flags) = 0;

    protected:
        Math::Vec2 m_positionOffset = Math::Vec2::ZERO;
        Math::Vec2 m_scale = Math::Vec2::ONE;
        f32 m_rotation = 0.f;

        u16 m_zOrder = 0;

        bool m_irisMode:1;

    private:
        Math::Vec2 m_scaleFactor[2] = {Math::Vec2::ONE, Math::Vec2::ONE};
        f32 m_rotationOffset[2] = {0.f, 0.f};

        std::vector<Camera> m_cameras;
    };
}
