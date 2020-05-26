#include "dmkafx.h"
#include "VulkanSurface.h"

#include "VulkanQueue.h"
#include "../Context/VulkanSwapChain.h"

#include <set>

namespace Dynamik 
{
	namespace Backend
	{
		B1 checkDeviceExtensionSupport(VkPhysicalDevice device, ARRAY<CCPTR> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME }) {
			UI32 extensionCount = 0;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

			ARRAY<VkExtensionProperties> availableExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

			std::set<STRING> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

			for (const auto& extension : availableExtensions)
				requiredExtensions.erase(extension.extensionName);

			return requiredExtensions.empty();
		}

		void VulkanSurface::initialize(VulkanInstance vInstance, POINTER<GLFWwindow> windowHandle)
		{
			DMK_VULKAN_ASSERT(glfwCreateWindowSurface(vInstance, windowHandle.get(), nullptr, &surface), "Failed to create window surface!");
		}

		void VulkanSurface::terminate(VulkanInstance vInstance)
		{
			vkDestroySurfaceKHR(vInstance, surface, nullptr);
		}

		B1 VulkanSurface::isDeviceSuitable(const VkPhysicalDevice& physicalDevice)
		{
			VulkanQueue _queue;
			_queue.findQueueFamilies(physicalDevice, surface);

			B1 extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
			B1 swapChainAdequate = false;
			if (extensionsSupported)
			{
				VulkanSwapChainSupportDetails swapChainSupport = VulkanSwapChain::querySwapChainSupport(physicalDevice, surface);
				swapChainAdequate = (!swapChainSupport.formats.empty()) && (!swapChainSupport.presentModes.empty());
			}

			VkPhysicalDeviceFeatures supportedFeatures;
			vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);

			return _queue.isComplete()
				&& extensionsSupported
				&& swapChainAdequate
				&& supportedFeatures.samplerAnisotropy;
		}

		VulkanSurface::operator VkSurfaceKHR() const
		{
			return this->surface;
		}

		VulkanSurface::operator VkSurfaceCapabilitiesKHR() const
		{
			return this->surfaceCapabilities;
		}
	}
}