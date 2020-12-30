// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/Queue.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void Queue::FindQueueFamilies(VkPhysicalDevice vPhysicalDevice, VkSurfaceKHR vSurface)
		{
			UI32 queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, queueFamilies.data());

			I32 i = 0;
			for (auto itr = queueFamilies.begin(); itr != queueFamilies.end(); itr++, i++)
			{
				// Set graphics family.
				if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_GRAPHICS_BIT))
					graphicsFamily = i;

				// Set compute family.
				if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_COMPUTE_BIT))
					computeFamily = i;

				// Set transfer family.
				if ((itr->queueCount > 0) && (itr->queueFlags & VK_QUEUE_TRANSFER_BIT))
					transferFamily = i;

				// Escape from the loop if the queues were found.
				if (IsComplete())
					break;
			}
		}

		bool Queue::IsComplete()
		{
			return graphicsFamily.has_value() && computeFamily.has_value() && transferFamily.has_value();
		}
	}
}