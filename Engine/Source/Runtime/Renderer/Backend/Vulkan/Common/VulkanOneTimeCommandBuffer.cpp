// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanOneTimeCommandBuffer.h"

#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		VulkanOneTimeCommandBuffer::VulkanOneTimeCommandBuffer(RCoreObject* pCoreObject)
			: myDevice(Inherit<VulkanCoreObject>(pCoreObject)->device), myQueues(Inherit<VulkanCoreObject>(pCoreObject)->queues)
		{
			/* Create the command pool for the command buffer */
			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = myQueues.processFamily.value();
			poolInfo.flags = 0;

			DMK_VULKAN_ASSERT(vkCreateCommandPool(myDevice, &poolInfo, nullptr, &pool), "Failed to create the one time command pool!");

			/* Create the command buffer */
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandPool = pool;
			allocInfo.commandBufferCount = 1;

			DMK_VULKAN_ASSERT(vkAllocateCommandBuffers(myDevice, &allocInfo, &buffer), "Unable to allocate the one time command buffer!");

			/* Begin recording the command buffer */
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

			DMK_VULKAN_ASSERT(vkBeginCommandBuffer(buffer, &beginInfo), "Failed to start recording the one time command buffer!");
		}

		VulkanOneTimeCommandBuffer::~VulkanOneTimeCommandBuffer()
		{
			/* End the command buffer recording */
			DMK_VULKAN_ASSERT(vkEndCommandBuffer(buffer), "Failed to stop recording the one time command buffer!");

			/* Submit the command buffer to execute the commands */
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &buffer;

			DMK_VULKAN_ASSERT(vkQueueSubmit(myQueues.processQueue, 1, &submitInfo, VK_NULL_HANDLE), "Faild to submit the process queue of the one time command buffer!");
			DMK_VULKAN_ASSERT(vkQueueWaitIdle(myQueues.utilityQueue), "Failed to call idle after subitting one time command buffer data!");

			/* Free the allocated command buffers and pools */
			vkFreeCommandBuffers(myDevice, pool, 1, &buffer);
			vkDestroyCommandPool(myDevice, pool, nullptr);
		}

		VulkanOneTimeCommandBuffer::operator VkCommandBuffer() const
		{
			return this->buffer;
		}

		VulkanOneTimeCommandBuffer::operator VkCommandPool() const
		{
			return this->pool;
		}
	}
}