// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Instance.h"
#include "Display.h"
#include "Queue.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Structure containing support details for a Vulkan Swap Chain.
		 */
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities = {};			// Swap Chain capabilities.
			std::vector<VkSurfaceFormatKHR> formats = {};		// Swap Chain formats.
			std::vector<VkPresentModeKHR> presentModes = {};	// Swap Chain present modes.

			/**
			 * Query swap chain support details.
			 *
			 * @param vPhysicalDevice: The physical device to be checked for.
			 * @param vSurface: The surface to be checked with.
			 * @return SwapChainSupportDetails structure.
			 */
			static SwapChainSupportDetails Query(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface);
		};

		/**
		 * Vulkan Device structure.
		 * This object stores information about a single Vulkan Device.
		 */
		struct VulkanDevice {
			VulkanQueue vQueue = {};

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
			VkDevice vLogicalDevice = VK_NULL_HANDLE;
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;

			VkSampleCountFlags vSampleCount = VK_SAMPLE_COUNT_64_BIT;

			static VulkanDevice Create(const VulkanInstance& vInstance, const VulkanDisplay& vDisplay);
			static void Destroy(const VulkanInstance& vInstance, const VulkanDevice& device);

			static VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface);
		};
	}
}