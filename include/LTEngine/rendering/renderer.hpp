#ifndef _LTENGINE_RENDERER_HPP_
#define _LTENGINE_RENDERER_HPP_

#include <vector>

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>

#include <LTEngine/math/vec2.hpp>

#include <LTEngine/shapes/circle.hpp>
#include <LTEngine/shapes/polygon.hpp>
#include <LTEngine/shapes/rect.hpp>
#include <LTEngine/shapes/triangle.hpp>

#include <LTEngine/rendering/camera.hpp>
#include <LTEngine/rendering/color.hpp>
#include <LTEngine/rendering/image.hpp>


namespace LTEngine::Rendering {
	class Renderer {
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		typedef u16 RendererFlags;

		const static RendererFlags FLAG_FLIP_H = ((RendererFlags)1 << 0);
		const static RendererFlags FLAG_FLIP_V = ((RendererFlags)1 << 1);

		/**
		 * @brief Fills the shape
		 *
		 * @details
		 * Depending on the renderer, certain shapes will not get affected, the current list (that will change) is:
		 *  - Rectangles
		 *  - Lines
		 *  - Polygons
		 *
		 *  So far, all the listed unaffected shapes can be replicated by drawing lines or by calculating the paramters to fill.
		 */
		const static RendererFlags FLAG_FILL = ((RendererFlags)1 << 2);


		void setScale(Math::Vec2 scale);

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

		virtual void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags = 0) = 0;
		virtual void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags = 0) = 0;
		void drawTriangle(Shapes::Triangle triangle, ColorA color, RendererFlags flags = 0);

		virtual void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags = 0) = 0;
		virtual void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags = 0) = 0;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, ColorA color, RendererFlags flags = 0);
		virtual void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		                       RendererFlags flags = 0) = 0;
		void drawImage(const Image *image, Math::Vec2 position, f32 rotation, ColorA color, RendererFlags flags = 0) {
			drawImage(image, Math::Vec2i{(i32)position.x, (i32)position.y}, rotation, color, flags);
		}
		void drawImage(const Image *image, Math::Vec2 position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags = 0) {
			drawImage(image, Math::Vec2i{(i32)position.x, (i32)position.y}, rotation, region, color, flags);
		}

		void setOffsetsApplied() { m_offsetsApplied = true; }
		void clearOffsetsApplied() { m_offsetsApplied = false; }

		Math::Vec2 worldToScreenPosition(Math::Vec2 position) const;
		Math::Vec2i worldToScreenPosition(Math::Vec2i position) const;
		void worldToScreenPosition(f32 *x, f32 *y) const;
		void worldToScreenPosition(i32 *x, i32 *y) const;
		f32 worldToScreenRotation(f32 rotation) const;
		void worldToScreenRotation(f32 *rotation) const;

		Math::Vec2 screenToWorldPosition(Math::Vec2 position) const;
		Math::Vec2i screenToWorldPosition(Math::Vec2i position) const;
		void screenToWorldPosition(f32 *x, f32 *y) const;
		void screenToWorldPosition(i32 *x, i32 *y) const;
		f32 screenToWorldRotation(f32 rotation) const;
		void screenToWorldRotation(f32 *rotation) const;

		Math::Vec2 getWorldScale() const;

	protected:
		virtual void cameraCreated(u32 id) {};
		virtual void cameraDestroyed(u32 id) {};
		virtual void cameraSelected(u32 id) {};
		virtual void cameraDeselected() {};

		u16 getZOrder() { return m_zOrder; }
		bool isIsIrisMode() { return m_irisMode; }

		Camera *getCameraById(u32 id);
		u32 getCurrentCamera() { return m_currentCamera; }
		bool isCameraActive() { return m_currentCameraActive; }

	private:
		u16 m_zOrder = 0;

		bool m_irisMode : 1 = false;
		bool m_currentCameraActive : 1 = false;

		std::vector<Camera> m_cameras;

		u32 m_nextCameraId = 0;
		u32 m_currentCamera = 0;

		bool m_offsetsApplied : 1 = true;

		Math::Vec2 m_positionOffset = Math::Vec2::Zero;
		f32 m_rotationOffset = 0.f;
		Math::Vec2 m_scaleFactor[2] = {Math::Vec2::One, Math::Vec2::One};
	};
} // namespace LTEngine::Rendering

#endif
