#if !_LTENGINE_VULKAN_RENDERER_HPP_ && LTENGINE_COMPONENT_RENDERER_VULKAN
#define _LTENGINE_VULKAN_RENDERER_HPP_

#include <functional>

#include <vulkan/vulkan.h>

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Rendering {
	class LTENGINE_API VulkanRenderer : public Renderer {
	public:
		VulkanRenderer(std::function<VkSurfaceKHR(VkInstance instance)> createSurface, std::vector<const char *> extensions);
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
		struct FrameData {
			VkCommandPool commandPool;
			VkCommandBuffer mainCommandBuffer;
			VkFence renderFence;
			VkSemaphore swapchainSemaphore, renderSemaphore;
		};
		constexpr static u32 FRAME_OVERLAP = 2;

		u64 m_frameCount;

        VkInstance m_instance;
		VkDevice m_device;
		VkSurfaceKHR m_surface;
        VkPhysicalDevice m_gpu;
		VkDebugUtilsMessengerEXT m_debug;

		VkSwapchainKHR m_swapchain;
		VkFormat m_swapchainImageFormat;
		std::vector<VkImage> m_swapchainImages;
		std::vector<VkImageView> m_swapchainImageViews;
		VkExtent2D m_swapchainExtent;

		FrameData m_frames[FRAME_OVERLAP];
		FrameData &getCurrentFrame() { return m_frames[m_frameCount & FRAME_OVERLAP]; }

		VkQueue m_graphicsQueue;
		u32 m_graphicsQueueFamily;

#ifdef LTENGINE_DEV_BUILD
		constexpr static bool requestValidationLayers = true;
#else
		constexpr static bool requestValidationLayers = false;
#endif

        void init_vulkan(std::function<VkSurfaceKHR(VkInstance instances)> createSurface, std::vector<const char *> extension);
        void init_swapchain();
        void init_commands();
        void init_sync_structures();

		void create_swapchain(u32 width, u32 height);
		void destroy_swapchain();

		VkCommandPoolCreateInfo createCommandPoolCreateInfo(u32 queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);
		VkCommandBufferAllocateInfo createCommandBufferAllocateInfo(VkCommandPool, u32 count = 1);
		VkFenceCreateInfo createFenceCreateInfo(VkFenceCreateFlags flags = 0);
		VkSemaphoreCreateInfo createSemaphoreCreateInfo(VkSemaphoreCreateFlags flags = 0);
		VkCommandBufferBeginInfo createCommandBufferBeginInfo(VkCommandBufferUsageFlags flags = 0);
		VkImageSubresourceRange createImageSubresourceRange(VkImageAspectFlags aspectMask);
		
		void transitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
    };
}

#endif