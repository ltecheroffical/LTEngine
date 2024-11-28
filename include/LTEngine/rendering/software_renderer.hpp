#ifndef _LTENGINE_SOFTWARE_RENDERER_HPP_
#define _LTENGINE_SOFTWARE_RENDERER_HPP_

#include <mutex>
#include <queue>
#include <unordered_map>

#include <LTEngine/rendering/cpu_shader.hpp>
#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
	class SoftwareRenderer : public Renderer {
	public:
		SoftwareRenderer(u32 width, u32 height);
		~SoftwareRenderer() override = default;

		enum class ScalingMode { Nearest, Linear };

		void resize(u32 width, u32 height);

		size_t getScreenData(Color *data);
		void setScreenOnly();
		void clearScreenOnly();

		void clear(Color color) override;
		void clear(ColorA color) override;

		void setPixel(Math::Vec2i position, Color color) override;
		void setPixel(Math::Vec2i position, ColorA color) override;
		Color getPixel(Math::Vec2i position) override;

		void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags = 0) override;
		void drawCircle(Shapes::Circle circle, ColorA color, RendererFlags flags = 0) override;

		void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags = 0) override;
		void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags = 0) override;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags = 0) override;
		void drawCamera(u32 id, Shapes::Recti rect, ColorA color, RendererFlags flags = 0);

		bool process();
		void processAll();

		void setScalingMode(ScalingMode mode);

		void setShader(CPUShader *shader);
		void clearShader();

	private:
		struct RendererQueueOp {
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
				Camera
			} opType = RenderOpType::None;

			bool screenOnly : 1 = false;

			ColorA color = ColorA::Clear;
			RendererFlags flags = 0;
			u16 zOrder = 0;

			std::chrono::high_resolution_clock::time_point timestamp = std::chrono::high_resolution_clock::now();

			CPUShader *shader = nullptr;


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
			u32 dataCamId = 0;
		};

		void prepareBuffer(u32 width, u32 height);
		void drawBufferPixel(u32 x, u32 y, ColorA color);
		void displayBuffer(i32 x, i32 y, const RendererQueueOp *op, f32 rotation);

		void cameraCreated(u32 id) override;
		void cameraDestroyed(u32 id) override;
		void cameraSelected(u32 id) override;
		void cameraDeselected() override;

		ScalingMode m_scalingMode;

		std::unordered_map<u32, std::vector<Color>> m_cameraOutputs;
		std::unordered_map<u32, std::vector<u16>> m_cameraDepth;
		std::unordered_map<u32, std::mutex> m_cameraMutexes;

		std::vector<Color> m_screen;
		std::vector<u16> m_screenDepth;
		std::mutex m_screenMutex;
		u32 m_screenWidth;
		u32 m_screenHeight;

		std::vector<ColorA> m_bufferData;
		std::vector<ColorA> m_bufferWorkspace1;
		std::vector<ColorA> m_bufferWorkspace2;
		u32 m_bufferWidth = 0;
		u32 m_bufferHeight = 0;

		bool m_screenOnly : 1 = false;
		bool m_cameraSelected : 1 = false;

		CPUShader *m_shader = nullptr;

		std::queue<RendererQueueOp> m_rendererQueue;
		std::mutex m_rendererQueueMutex;

		std::chrono::high_resolution_clock::time_point m_creationTime = std::chrono::high_resolution_clock::now();
	};
} // namespace LTEngine::Rendering

#endif
