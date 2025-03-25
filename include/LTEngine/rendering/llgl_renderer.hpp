#if !_LTENGINE_RENDERING_LLGL_RENDERER_HPP_ && LTENGINE_COMPONENT_RENDERER_LLGL
#define _LTENGINE_RENDERING_LLGL_RENDERER_HPP_

#include <LLGL/LLGL.h>

#include <LTEngine/window.hpp>
#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
	class LTENGINE_API LLGLRenderer : public Renderer {
	public:
		enum class GraphicsAPI {
			OpenGL = 0,
			Vulkan,
			D3D11,
			D3D12
		};

		LLGLRenderer(Window *window, GraphicsAPI api);
		~LLGLRenderer() override;

		void clear(Color color) override;
		void clear(ColorA color) override;

		void setPixel(Math::Vec2i position, Color color) override;
		void setPixel(Math::Vec2i position, ColorA color) override;
		Color getPixel(Math::Vec2i position) override;

		void drawRect(Shapes::Rect rect, ColorA color, RendererFlags flags) override;
		void drawCircle(Shapes::Circle, ColorA color, RendererFlags flags) override;

		void drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, RendererFlags flags) override;
		void drawPoints(Shapes::Polygon polygon, ColorA color, RendererFlags flags) override;

		void drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color,
		               RendererFlags flags) override;

	private:
		LLGL::RenderSystemPtr m_renderer;
		LLGL::SwapChain *m_swapChain;
	};
} // namespace LTEngine::Rendering

#endif
