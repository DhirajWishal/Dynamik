// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanSurface.h"

#include "VulkanQueue.h"
#include "../Context/VulkanSwapChain.h"

#if defined(DMK_PLATFORM_WINDOWS)
	#include "Window/Windows/WindowsWindow.h"

#elif defined(DMK_PLATFORM_LINUX)

#elif defined(DMK_PLATFORM_MAC)

#endif

#include <set>

namespace Backend
{
	bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<CCPTR> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME }) {
		UI32 extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<STRING> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);

		return requiredExtensions.empty();
	}

	void VulkanSurface::initialize(VulkanInstance vInstance, DMKWindowHandle* windowHandle)
	{
		windowID = GetPointerAsInteger(windowHandle);

#if defined(DMK_PLATFORM_WINDOWS)
		WindowsWindow* _windPtr = (WindowsWindow*)windowHandle;
		DMK_VULKAN_ASSERT(glfwCreateWindowSurface(vInstance, _windPtr->getHandle(), nullptr, &surface), "Failed to create window surface!");

#elif defined(DMK_PLATFORM_LINUX)

#elif defined(DMK_PLATFORM_MAC)

#endif
	}

	void VulkanSurface::terminate(VulkanInstance vInstance)
	{
		vkDestroySurfaceKHR(vInstance, surface, nullptr);
	}

	bool VulkanSurface::isDeviceSuitable(const VkPhysicalDevice& physicalDevice)
	{
		VulkanQueue _queue;
		_queue.findQueueFamilies(physicalDevice, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
		bool swapChainAdequate = false;
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
