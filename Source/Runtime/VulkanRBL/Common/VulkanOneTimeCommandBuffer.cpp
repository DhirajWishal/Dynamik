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

			/* Create a fence */
			VkFenceCreateInfo fenceCreateInfo = {};
			fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fenceCreateInfo.flags = VK_NULL_HANDLE;
			fenceCreateInfo.pNext = VK_NULL_HANDLE;

			VkFence fence = VK_NULL_HANDLE;
			DMK_VULKAN_ASSERT(vkCreateFence(myDevice, &fenceCreateInfo, nullptr, &fence), "Failed to create fence!");

			/* Submit the queue */
			DMK_VULKAN_ASSERT(vkQueueSubmit(myQueues.processQueue, 1, &submitInfo, fence), "Failed to submit the process queue of the one time command buffer!");
			
			/* Wait for fence */
			DMK_VULKAN_ASSERT(vkWaitForFences(myDevice, 1, &fence, VK_TRUE, std::numeric_limits<UI32>::max()), "Failed to wait for fence to complete!");
			
			/* Destroy the created fence */
			vkDestroyFence(myDevice, fence, nullptr);

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