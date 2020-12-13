// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Objects/Queue.h"

namespace DMK
{
	namespace VulkanBackend
	{
		VulkanQueue CreateTempQueue(const VkPhysicalDevice& vPhysicalDevice)
		{
			VulkanQueue queue = {};
			UI32 queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, nullptr);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, queueFamilies.data());

			I32 i = 0;
			for (auto itr = queueFamilies.begin(); itr != queueFamilies.end(); itr++, i++)
			{
				if (itr->queueCount > 0)
				{
					// Set graphics family.
					if (itr->queueFlags & VK_QUEUE_GRAPHICS_BIT)
						queue.mGraphicsFamily = i;

					// Set compute family.
					if (itr->queueFlags & VK_QUEUE_COMPUTE_BIT)
						queue.mComputeFamily = i;

					// Set transfer family.
					if (itr->queueFlags & VK_QUEUE_TRANSFER_BIT)
						queue.mTransferFamily = i;

					// Escape from the loop if the queues were found.
					if (IsQueueComplete(queue))
						break;
				}
			}

			return queue;
		}

		VulkanQueue::Index CreateQueue(const VkPhysicalDevice& vPhysicalDevice)
		{
			return VulkanQueue::Store::Insert(CreateTempQueue(vPhysicalDevice));
		}

		bool IsQueueComplete(const VulkanQueue& vQueue)
		{
			return vQueue.mGraphicsFamily.has_value() && vQueue.mComputeFamily.has_value() && vQueue.mTransferFamily.has_value();
		}

		bool IsQueueComplete(const VulkanQueue::Index& vIndex)
		{
			return IsQueueComplete(VulkanQueue::Store::Get(vIndex));
		}
	}
}