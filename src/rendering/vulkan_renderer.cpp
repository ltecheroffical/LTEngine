#ifdef LTENGINE_COMPONENT_RENDERER_VULKAN

#include <VkBootstrap.h>

#include <LTEngine/rendering/vulkan_renderer.hpp>


using namespace LTEngine;
using namespace LTEngine::Rendering;


VulkanRenderer::VulkanRenderer(std::function<VkSurfaceKHR(VkInstance instances)> createSurface, std::vector<const char *> extensions) {
    init_vulkan(createSurface, extensions);
    init_swapchain();
    init_commands();
    init_sync_structures();

    u32 swapchainImageIndex;
    vkAcquireNextImageKHR(m_device, m_swapchain, 1000000000, getCurrentFrame().swapchainSemaphore, nullptr, &swapchainImageIndex);

    VkCommandBuffer cmd = getCurrentFrame().mainCommandBuffer;
    vkResetCommandBuffer(cmd, 0);

    VkCommandBufferBeginInfo cmdBeginInfo = createCommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    vkBeginCommandBuffer(cmd, &cmdBeginInfo);

    transitionImage(cmd, m_swapchainImages[swapchainImageIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);
}

VulkanRenderer::~VulkanRenderer() {
    vkDeviceWaitIdle(m_device);
    for (u32 i = 0; i < FRAME_OVERLAP; i++) {
        vkDestroyCommandPool(m_device, m_frames[i].commandPool, nullptr);
    }

    destroy_swapchain();

    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    vkDestroyDevice(m_device, nullptr);
    
    vkb::destroy_debug_utils_messenger(m_instance, m_debug);
    vkDestroyInstance(m_instance, nullptr);
}


void VulkanRenderer::clear(Color color) {

}

void VulkanRenderer::clear(ColorA color) {

}


void VulkanRenderer::setPixel(Math::Vec2i position, Color color) {

}

void VulkanRenderer::setPixel(Math::Vec2i position, ColorA color) {

}

Color VulkanRenderer::getPixel(Math::Vec2i position) {

}


void VulkanRenderer::drawRect(Shapes::Rect rect, ColorA color, Renderer::RendererFlags flags) {

}

void VulkanRenderer::drawCircle(Shapes::Circle, ColorA color, Renderer::RendererFlags flags) {

}


void VulkanRenderer::drawLine(Math::Vec2 a, Math::Vec2 b, u16 thickness, ColorA color, Renderer::RendererFlags flags) {

}

void VulkanRenderer::drawPoints(Shapes::Polygon polygon, ColorA color, Renderer::RendererFlags flags) {

}


void VulkanRenderer::drawImage(const Image *image, Math::Vec2i position, f32 rotation, Shapes::Recti region, ColorA color, Renderer::RendererFlags flags) {

}


void VulkanRenderer::init_vulkan(std::function<VkSurfaceKHR(VkInstance instances)> createSurface, std::vector<const char *> extensions) {
    vkb::InstanceBuilder builder;

    auto inst_ret = builder.set_app_name("LTEngine Renderer")
        .request_validation_layers(requestValidationLayers)
        .use_default_debug_messenger()
        .require_api_version(1, 3, 0)
        .enable_extensions(extensions)
        .build();

    vkb::Instance vkb_inst = inst_ret.value();

    m_instance = vkb_inst.instance;
    m_debug = vkb_inst.debug_messenger;

    VkPhysicalDeviceVulkan13Features features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
    features.dynamicRendering = true;
    features.synchronization2 = true;

    VkPhysicalDeviceVulkan12Features features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
    features12.bufferDeviceAddress = true;
    features12.descriptorIndexing = true;

    m_surface = createSurface(m_instance);

    vkb::PhysicalDeviceSelector selector(vkb_inst);
    vkb::PhysicalDevice physicalDevice = selector
        .set_minimum_version(1, 2)
        .set_required_features_13(features)
        .set_required_features_12(features12)
        .set_surface(m_surface)
        .select()
        .value();

    vkb::DeviceBuilder deviceBuilder{physicalDevice};
    vkb::Device vkbDevice = deviceBuilder.build().value();

    m_device = vkbDevice.device;
    m_gpu = physicalDevice.physical_device;

    m_graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
    m_graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
}

void VulkanRenderer::init_swapchain() {
    create_swapchain(1, 1);
}

void VulkanRenderer::init_commands() {
    VkCommandPoolCreateInfo commandPoolInfo = createCommandPoolCreateInfo(m_graphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    for (u32 i = 0; i < FRAME_OVERLAP; i++) {
        vkCreateCommandPool(m_device, &commandPoolInfo, nullptr, &m_frames[i].commandPool);
        VkCommandBufferAllocateInfo cmdAllocInfo = createCommandBufferAllocateInfo(m_frames[i].commandPool);
        vkAllocateCommandBuffers(m_device, &cmdAllocInfo, &m_frames[i].mainCommandBuffer);
    }
}

void VulkanRenderer::init_sync_structures() {
    VkFenceCreateInfo fenceCreateInfo = createFenceCreateInfo(VK_FENCE_CREATE_SIGNALED_BIT);
    VkSemaphoreCreateInfo semaphoreCreateInfo = createSemaphoreCreateInfo();

    for (u32 i = 0; i < FRAME_OVERLAP; i++) {
        vkCreateFence(m_device, &fenceCreateInfo, nullptr, &m_frames[i].renderFence);
        
        vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_frames[i].swapchainSemaphore);
        vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_frames[i].renderSemaphore);
    }
}


void VulkanRenderer::create_swapchain(u32 width, u32 height) {
    vkb::SwapchainBuilder swapchainBuilder{m_gpu, m_device, m_surface};
    m_swapchainImageFormat = VK_FORMAT_R8G8B8A8_UNORM;

    vkb::Swapchain vkbSwapchain = swapchainBuilder
        .set_desired_format(VkSurfaceFormatKHR{ .format = m_swapchainImageFormat, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR })
        .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
        .set_desired_extent(width, height)
        .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
        .build()
        .value();

    m_swapchainExtent = vkbSwapchain.extent;
    m_swapchain = vkbSwapchain.swapchain;
    m_swapchainImages = vkbSwapchain.get_images().value();
    m_swapchainImageViews = vkbSwapchain.get_image_views().value();
}

void VulkanRenderer::destroy_swapchain() {
    vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
    for (u32 i = 0; i < m_swapchainImageViews.size(); i++) {
        vkDestroyImageView(m_device, m_swapchainImageViews[i], nullptr);
    }
}


VkCommandPoolCreateInfo VulkanRenderer::createCommandPoolCreateInfo(u32 queueFamilyIndex, VkCommandPoolCreateFlags flags /*= 0*/) {
    VkCommandPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.queueFamilyIndex = queueFamilyIndex;
    info.flags = flags;
    return info;
}

VkCommandBufferAllocateInfo VulkanRenderer::createCommandBufferAllocateInfo(VkCommandPool pool, u32 count /*= 1*/) {
    VkCommandBufferAllocateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = nullptr;

    info.commandPool = pool;
    info.commandBufferCount = count;
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    return info;
}

VkFenceCreateInfo VulkanRenderer::createFenceCreateInfo(VkFenceCreateFlags flags /*= 0*/) {
    VkFenceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = flags;
    return info;
}

VkSemaphoreCreateInfo VulkanRenderer::createSemaphoreCreateInfo(VkSemaphoreCreateFlags flags /*= 0*/) {
    VkSemaphoreCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = flags;
    return info;
}

VkCommandBufferBeginInfo VulkanRenderer::createCommandBufferBeginInfo(VkCommandBufferUsageFlags flags /*= 0*/) {
    VkCommandBufferBeginInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;

    info.pInheritanceInfo = nullptr;
    info.flags = flags;
    return info;
}

VkImageSubresourceRange createImageSubresourceRange(VkImageAspectFlags aspectMask) {
    VkImageSubresourceRange subImage {};
    subImage.aspectMask = aspectMask;
    subImage.baseMipLevel = 0;
    subImage.levelCount = VK_REMAINING_MIP_LEVELS;
    subImage.baseArrayLayer = 0;
    subImage.layerCount = VK_REMAINING_ARRAY_LAYERS;

    return subImage;
}


void VulkanRenderer::transitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout) {
    VkImageMemoryBarrier2 imageBarrier {.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2};
    imageBarrier.pNext = nullptr;

    imageBarrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    imageBarrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
    imageBarrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    imageBarrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

    imageBarrier.oldLayout = currentLayout;
    imageBarrier.newLayout = newLayout;

    VkImageAspectFlags aspectMask = (newLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    imageBarrier.subresourceRange = createImageSubresourceRange(aspectMask);
    imageBarrier.image = image;

    VkDependencyInfo depInfo {};
    depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    depInfo.pNext = nullptr;

    depInfo.imageMemoryBarrierCount = 1;
    depInfo.pImageMemoryBarriers = &imageBarrier;

    vkCmdPipelineBarrier2(cmd, &depInfo);
}

#endif