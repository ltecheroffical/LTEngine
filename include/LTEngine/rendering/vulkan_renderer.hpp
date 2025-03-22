#ifndef _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#define _LTENGINE_RENDERING_SDL_RENDERER_HPP_
#ifdef LTENGINE_VULKAN_API

#include <LTEngine/rendering/renderer.hpp>

#include <vulkan/vulkan.h>


namespace LTEngine::Rendering {
	class LTENGINE_API VulkanRenderer : public Renderer {
	public:
		VulkanRenderer(VkSurfaceKHR surface);
		~VulkanRenderer() override;

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
		VkInstance m_instance;
		VkDevice m_device;
		VkPhysicalDevice m_physicalDevice;
		VkSurfaceKHR m_surface;

		VkDebugUtilsMessengerEXT m_debugMessenger;

		static u32 m_vkRendererId;
	
		void vulkanInit();
		bool vulkanCheckValidationLayers();
	};
} // namespace LTEngine::Rendering

#endif
#endif