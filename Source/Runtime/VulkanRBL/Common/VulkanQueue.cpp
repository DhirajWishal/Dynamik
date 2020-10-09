// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanQueue.h"

namespace Backend
{
	void VulkanQueue::findQueueFamilies(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
	{
		UI32 queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		ARRAY<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

		I32 i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				processFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport)
				utilityFamily = i;

			if (isComplete())
				break;

			i++;
		}
	}

	void VulkanQueue::initializeQueues(const VkDevice& logicalDevice)
	{
		vkGetDeviceQueue(logicalDevice, processFamily.value(), 0, &processQueue);
		vkGetDeviceQueue(logicalDevice, utilityFamily.value(), 0, &utilityQueue);
	}

	B1 VulkanQueue::isComplete()
	{
		return processFamily.has_value() && utilityFamily.has_value();;
	}
}
