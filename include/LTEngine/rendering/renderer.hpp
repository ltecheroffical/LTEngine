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
        Renderer() = default;
        virtual ~Renderer() = default;

        const static RendererFlags FLAG_FLIP_H = ((RendererFlags)1 << 0);
        const static RendererFlags FLAG_FLIP_V = ((RendererFlags)1 << 1);

        const static RendererFlags FLAG_FILL = ((RendererFlags)1 << 2);


        void setScale(Math::Vec2 scale);
        void setRotation(f32 rotation);

        void setZOrder(u16 z);

        void setRotationOffset(f32 offset);
        void setScaleFactor(Math::Vec2 scale);
        void setPositionOffset(Math::Vec2 offset);

        void resetTransform();

        void setIrisMode();
        void clearIrisMode();

        u32 createCamera(Math::Vec2 position, Math::Vec2 zoom);
        void deleteCamera(u32 id);
        void setCameraPosition(u32 id, Math::Vec2 position);
        void setCameraRotation(u32 id, f32 rotation);
        void setCameraZoom(u32 id, Math::Vec2 zoom);
        void setCameraInclude(u32 id);
        void setCameraExclude(u32 id);
        void setCurrentCamera(u32 id);
        void clearCurrentCamera();
        Math::Vec2 getCameraPosition(u32 id) const;
        Math::Vec2 getCameraZoom(u32 id) const;
        f32 getCameraRotation(u32 id) const;

        virtual void clear(Color color) = 0;
        virtual void clear(ColorA color) = 0;

        virtual void setPixel(Math::Vec2i position, Color color) = 0;
        virtual void setPixel(Math::Vec2i position, ColorA color) = 0;
        virtual Color getPixel(Math::Vec2i position) = 0;

        virtual void drawRect(Math::Rect rect, ColorA color, RendererFlags flags) = 0;
        virtual void drawCircle(Math::Vec2 centerPosition, f32 radius, ColorA color, RendererFlags flags) = 0;
        void drawTriangle(Math::Vec2 a, Math::Vec2 b, Math::Vec2 c, ColorA color, RendererFlags flags);

        virtual void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) = 0;
        virtual void drawPoints(const Math::Vec2 *points, u32 count, ColorA color, RendererFlags flags) = 0;

        virtual void drawImage(const Image *image, Math::Vec2i position, ColorA color, RendererFlags flags) = 0;

    protected:
        virtual void cameraCreated(u32 id) {};
        virtual void cameraDestroyed(u32 id) {};
        virtual void cameraSelected(u32 id) {};
        virtual void cameraDeselected() {};

        Math::Vec2 m_positionOffset = Math::Vec2::ZERO;
        Math::Vec2 m_scale = Math::Vec2::ONE;
        f32 m_rotation = 0.f;

        u16 m_zOrder = 0;

        bool m_irisMode:1 = false;
        bool m_currentCameraActive:1 = false;

        std::vector<Camera> m_cameras;

    private:
        void recalculateTransform();

        u32 m_nextCameraId = 0;
        u32 m_currentCamera = 0;

        Math::Vec2 m_realPositionOffset = Math::Vec2::ZERO;
        Math::Vec2 m_scaleFactor[2] = {Math::Vec2::ONE, Math::Vec2::ONE};
        f32 m_rotationOffset[2] = {0.f, 0.f};
    };
}
