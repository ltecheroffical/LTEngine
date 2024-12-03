#ifndef _LTENGINE_RENDERING_OPENGL_RENDERER_HPP_
#define _LTENGINE_RENDERING_OPENGL_RENDERER_HPP_

#include <functional>
#include <queue>

#include <glad/glad.h>

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/rendering/renderer.hpp>

#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Rendering {
	class LTENGINE_API OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback);
		~OpenGLRenderer() override;

		struct OpenGLMessage {
			GLenum source;
			std::string stringSource;
			GLenum type;
			std::string stringType;
			GLenum severity;
			std::string stringSeverity;

			u32 id;
			std::string msg;
		};

		void setNearestFilter() { m_nearestFilter = true; }
		void clearNearestFilter() { m_nearestFilter = false; }

		void resize(u32 width, u32 height);

		void clear(Color color) override;
		void clear(ColorA color) override;

		void setPixel(Math::Vec2i position, Color color) override;
		void setPixel(Math::Vec2i position, ColorA color) override;
		Color getPixel(Math::Vec2i position) override;

		void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
		void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) override;

		void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
		void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags) override;

		void flush();

		u32 compileShader(const char *source, GLenum shaderType);
		void deleteShader(u32 shader);
		void useShader(u32 vertexShader, u32 fragmentShader);
		void resetShader();

		/**
		 * @brief Get any messags OpenGL might have
		 *
		 * @returns True if there are any messges
		 *
		 * @details
		 * Currently this function is unused, in a later version, the messages will be used for debugging
		 * but with that comes the fact the `OpenGLMessage` structure will be changed.
		 */
		bool getMessage(OpenGLMessage *message);

	private:
		LTENGINE_PACK_START() struct Vertex {
			f32 x, y, z;
			f32 r, g, b, a;
			f32 u = 0, v = 0;
		} LTENGINE_PACK_END();

		struct RenderQueueOp {
			enum class RenderOpType {
				None = 0,

				SetPixel,

				Clear,
				ClearA,

				Rect,
				Circle,
				Line,
				Polygon,

				Image,
			} opType = RenderOpType::None;

			ColorA color = ColorA::Clear;
			RendererFlags flags = 0;
			u16 zOrder;


			Math::Vec2i dataPosition = Math::Vec2i::Zero;
			Math::Vec2 dataScale = Math::Vec2::One;
			f32 dataRotation = 0.f;

			Shapes::Recti dataRect = {0, 0, 0, 0};
			Shapes::Circle dataCircle = {{0, 0}, 0.f};
			Shapes::Polygon dataPolygon = {{}};

			Math::Vec2 dataPointA = Math::Vec2::Zero;
			Math::Vec2 dataPointB = Math::Vec2::Zero;
			u16 dataThickness = 0;

			const Image *dataImage = nullptr;
			bool dataImageNearestFilter = false;
			u32 dataCamId = 0;
		};

		void switchContext();

		f32 posToOpenGLX(f32 x) { return 2.f * (x / (f32)m_width) - 1.f; }
		f32 posToOpenGLY(f32 y) { return 1.f - 2.f * (y / (f32)m_height); }
		f32 openGLToPosX(f32 x) { return (x + 1.f) * (f32)m_width / 2.f; }
		f32 openGLToPosY(f32 y) { return (1.f - (y + 1.f)) * (f32)m_height / 2.f; }

		Math::Vec2 rotatePosition(Math::Vec2 position, Math::Vec2 center, f32 angle) {
			Math::Vec2 result;
			result.x = center.x + (position.x - center.x) * cos(angle) - (position.y - center.y) * sin(angle);
			result.y = center.y + (position.x - center.x) * sin(angle) + (position.y - center.y) * cos(angle);
			return result;
		}


		const u32 MAX_IMAGE_LIFETIME = 5000;

		std::queue<OpenGLMessage> m_messageQueue;

		std::queue<RenderQueueOp> m_renderOpQueue;

		std::unordered_map<const Image *, u32> m_imageCacheLifetime;
		std::unordered_map<const Image *, u32> m_imageCache;

		std::function<void()> m_switchContextCallback = nullptr;

		bool m_nearestFilter : 1 = false;

		u32 m_width;
		u32 m_height;

		u32 m_vbo;
		u32 m_vao;

		u32 m_currentShaderProgram;
		u32 m_defaultShaderProgram;
	};
} // namespace LTEngine::Rendering

#endif
