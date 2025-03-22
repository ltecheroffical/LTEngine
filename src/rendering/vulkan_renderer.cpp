#ifdef LTENGINE_VULKAN_API
#include <format>

#ifndef LTENGINE_DISABLE_GLFW
#include <GLFW/glfw3.h>
#endif

#include <VkBootstrap.h>

#include <LTEngine/exceptions/exc_not_possible.hpp>
#include <LTEngine/rendering/vulkan_renderer.hpp>

using namespace LTEngine;
using namespace LTEngine::Rendering;

const std::vector<const char*> validationLayers = {
#ifdef LTENGINE_DEV_BUILD
    "VK_LAYER_KHRONOS_validation"
#endif
};


VulkanRenderer::VulkanRenderer(VkSurfaceKHR surface) {
	m_surface = surface;

    vulkanInit();
}

VulkanRenderer::~VulkanRenderer() {
    vkDestroyInstance(m_instance, nullptr);
}


void VulkanRenderer::vulkanInit() {
    vkb::InstanceBuilder builder;

    auto inst_ret = builder.set_app_name(std::format("LTEngine Renderer #{}", m_vkRendererId++).c_str())
        .request_validation_layers(!validationLayers.empty())
        .use_default_debug_messenger()
        .require_api_version(1, 3, 0)
        .build();

    vkb::Instance vkb_inst = inst_ret.value();

    // Vulkan 1.3 Features
	VkPhysicalDeviceVulkan13Features features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
	features.dynamicRendering = true;
	features.synchronization2 = true;

	// Vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

    vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 3)
		.set_required_features_13(features)
		.set_required_features_12(features12)
		.set_surface(m_surface)
		.select()
		.value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };
	vkb::Device vkbDevice = deviceBuilder.build().value();

	m_device = vkbDevice.device;
	m_physicalDevice = vkbDevice.physical_device;
}

u32 VulkanRenderer::m_vkRendererId = 0;

#endif