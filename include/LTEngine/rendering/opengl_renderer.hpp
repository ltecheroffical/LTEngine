#pragma once

#include <functional>
#include <queue>

#include <glad/glad.h>

#include <LTEngine/common/compiler_utils.h>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
	class OpenGLRenderer : public Renderer {
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

		static void loadOpenGL(GLADloadproc loadProc);

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
		void drawImageNearest(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		                      RendererFlags flags);

		void flush();

		u32 compileShader(const char *source, GLenum shaderType);
		void deleteShader(u32 shader);
		void useShader(u32 vertexShader, u32 fragmentShader);
		void resetShader();

		bool getMessage(OpenGLMessage *message);

	private:
		const u32 MAX_IMAGE_LIFETIME = 5000;

		LTENGINE_PACK_START() struct Vertex {
			f32 x, y;
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
			Shapes::Recti dataRegion = {0, 0, 0, 0};
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

		std::queue<OpenGLMessage> m_messageQueue;

		std::queue<RenderQueueOp> m_renderOpQueue;

		std::unordered_map<const Image *, u32> m_imageCacheLifetime;
		std::unordered_map<const Image *, u32> m_imageCache;

		std::function<void()> m_switchContextCallback = nullptr;

		u32 m_width;
		u32 m_height;

		u32 m_vbo;
		u32 m_vao;

		u32 m_currentShaderProgram;
		u32 m_defaultShaderProgram;
	};
} // namespace LTEngine::Rendering
