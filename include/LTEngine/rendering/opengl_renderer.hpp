#if !_LTENGINE_RENDERING_OPENGL_RENDERER_HPP_ && LTENGINE_COMPONENT_RENDERER_OPENGL
#define _LTENGINE_RENDERING_OPENGL_RENDERER_HPP_

#include <functional>
#include <queue>

#include <glad/glad.h>

#include <LTEngine/rendering/renderer.hpp>
#include <LTEngine/logger.hpp>


namespace LTEngine::Rendering {
	class LTENGINE_API OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer(u32 width, u32 height, std::function<void()> switchContextCallback, Logger *logger = nullptr);
		~OpenGLRenderer() override;


		void setNearestFilter() {
			m_nearestFilter = true;
		}
		void clearNearestFilter() {
			m_nearestFilter = false;
		}


		void resize(u32 width, u32 height);

		void clear(Color color) override;
		void clear(ColorA color) override;

		void setPixel(Math::Vec2i position, Color color) override;
		void setPixel(Math::Vec2i position, ColorA color) override;
		void getPixelPromise(Math::Vec2i position, std::function<void(Color color)> pixelFunction);
		Color getPixel(Math::Vec2i position) override;

		void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
		void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags) override;

		void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
		void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags) override;

		void flush();

		void setLogger(Logger *logger) {
			m_logger = logger;
		}

		u32 compileShader(const char *source, GLenum shaderType);
		void useShader(u32 vertexShader, u32 fragmentShader);
		void resetShader();

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
				GetPixelPromise,

				Clear,

				Rect,
				Circle,
				Line,
				Polygon,

				Image,
			} opType = RenderOpType::None;

			RendererFlags flags = 0;
			u16 zOrder = 0;

			Shapes::Polygon polygon = {};
			std::function<void(Color color)> function = nullptr;

			union DrawPayload {
				struct ClearData {
					ColorA color = ColorA::Clear;
				} clear;

				struct PixelModify {
					Math::Vec2i position = {};
					ColorA color = ColorA::Clear;
				} setPixel;

				struct GetPixelPromise {
					Math::Vec2i position = {};
				} getPixelPromise;


				struct DrawRect {
					Shapes::Rect rect = {0, 0,0 ,0};
					ColorA color = ColorA::Clear;
				} drawRect;

				struct DrawCircle {
					Shapes::Circle circle = {};
					ColorA color = ColorA::Clear;
				} drawCircle;


				struct DrawLine {
					Math::Vec2 a = {};
					Math::Vec2 b = {};
					u16 thickness = 1;
					ColorA color = ColorA::Clear;
				} drawLine;

				struct DrawPoints {
					ColorA color = ColorA::Clear;
				} drawPoints;

				struct DrawImage {
					const Image *image = nullptr;
					Math::Vec2i position = {};
					Shapes::Recti region = {0, 0, 0, 0};
					f32 rotation = 0.f;
					ColorA color = ColorA::Clear;
				} drawImage;
			} payload;
		};

		void switchContext();

		f32 posToOpenGLX(f32 x) {
			return 2.f * (x / (f32)m_width) - 1.f;
		}
		f32 posToOpenGLY(f32 y) {
			return 1.f - 2.f * (y / (f32)m_height);
		}
		f32 openGLToPosX(f32 x) {
			return (x + 1.f) * (f32)m_width / 2.f;
		}
		f32 openGLToPosY(f32 y) {
			return (1.f - (y + 1.f)) * (f32)m_height / 2.f;
		}

		Math::Vec2 rotatePosition(Math::Vec2 position, Math::Vec2 center, f32 angle) {
			Math::Vec2 result;
			result.x = center.x + (position.x - center.x) * cos(angle) - (position.y - center.y) * sin(angle);
			result.y = center.y + (position.x - center.x) * sin(angle) + (position.y - center.y) * cos(angle);
			return result;
		}


		const u32 MAX_IMAGE_LIFETIME = 5000;

		std::queue<RenderQueueOp> m_renderOpQueue;

		std::unordered_map<const Image *, u32> m_imageCacheLifetime;
		std::unordered_map<const Image *, u32> m_imageCache;

		std::unordered_map<u32, u32> m_shaderCache;

		std::function<void()> m_switchContextCallback = nullptr;

		bool m_nearestFilter : 1 = false;

		Logger *m_logger;

		u32 m_width;
		u32 m_height;

		u32 m_vbo;
		u32 m_vao;

		u32 m_currentShaderProgram;
		u32 m_defaultShaderProgram;
	};
} // namespace LTEngine::Rendering

#endif
