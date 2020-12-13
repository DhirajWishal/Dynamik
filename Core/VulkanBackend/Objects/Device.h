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
		};

		/**
		 * Vulkan Device structure.
		 * This object stores information about a single Vulkan Device.
		 */
		struct VulkanDevice {
			using Index = UI8;
			using Store = StaticSparseSet<VulkanDevice, Index>;

			VulkanQueue::Index vQueueIndex = 0;

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
			VkDevice vLogicalDevice = VK_NULL_HANDLE;
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;

			VkSampleCountFlags vSampleCount = VK_SAMPLE_COUNT_64_BIT;
		};

		/**
		 * Create a new device.
		 *
		 * @param vInstanceIndex: The instance index to which the device is created.
		 * @param vDisplayIndex: The idnex of the display.
		 * @return The Vulkan Device index.
		 */
		VulkanDevice::Index CreateDevice(const VulkanInstance::Index& vInstanceIndex, const VulkanDisplay::Index& vDisplayIndex);

		/**
		 * Destroy a created device.
		 *
		 * @param vInstanceIndex: The index of the index the device is bound to.
		 * @param vDeviceIndex: The index of the device.
		 */
		void DestroyDevice(const VulkanInstance::Index& vInstanceIndex, const VulkanDevice::Index& vDeviceIndex);
	}
}