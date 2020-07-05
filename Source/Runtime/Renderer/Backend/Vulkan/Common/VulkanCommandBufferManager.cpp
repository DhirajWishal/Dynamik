// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCommandBufferManager.h"

#include "VulkanCommandBuffer.h"
#include "../VulkanCoreObject.h"

#include <array>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanCommandBufferManager::initialize(RCoreObject* pCoreObject)
		{
			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = Inherit<VulkanCoreObject>(pCoreObject)->queues.processFamily.value();
			poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

			DMK_VULKAN_ASSERT(vkCreateCommandPool(Inherit<VulkanCoreObject>(pCoreObject)->device, &poolInfo, nullptr, &pool), "Failed to create command pool!");
		}

		ARRAY<RCommandBuffer*> VulkanCommandBufferManager::allocateCommandBuffers(RCoreObject* pCoreObject, UI32 bufferCount)
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = pool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = static_cast<UI32>(bufferCount);

			ARRAY<RCommandBuffer*> _buffers;
			VulkanCommandBuffer* _buffer;
			for (UI32 itr = 0; itr < bufferCount; itr++)
			{
				_buffer = StaticAllocator<VulkanCommandBuffer>::allocate();
				DMK_VULKAN_ASSERT(vkAllocateCommandBuffers(Inherit<VulkanCoreObject>(pCoreObject)->device, &allocInfo, &_buffer->buffer), "Failed to allocate command buffers!");

				_buffers.pushBack(_buffer);
			}

			return _buffers;
		}

		void VulkanCommandBufferManager::resetBuffers(RCoreObject* pCoreObject, ARRAY<RCommandBuffer*> commandBuffers)
		{
			for (auto _buffer : commandBuffers)
				DMK_VULKAN_ASSERT(vkResetCommandBuffer(Inherit<VulkanCommandBuffer>(_buffer)->buffer, VK_NULL_HANDLE), "Failed to reset command buffer!");
		}

		void VulkanCommandBufferManager::terminateBuffers(RCoreObject* pCoreObject, ARRAY<RCommandBuffer*> commandBuffers)
		{
			for (auto _buffer : commandBuffers)
			{
				vkFreeCommandBuffers(Inherit<VulkanCoreObject>(pCoreObject)->device, pool, 1, &Inherit<VulkanCommandBuffer>(_buffer)->buffer);
				StaticAllocator<VulkanCommandBuffer>::deallocate(_buffer);
			}
		}

		void VulkanCommandBufferManager::terminate(RCoreObject* pCoreObject, ARRAY<RCommandBuffer*> commandBuffers)
		{
			terminateBuffers(pCoreObject, commandBuffers);

			vkDestroyCommandPool(Inherit<VulkanCoreObject>(pCoreObject)->device, pool, nullptr);
		}
	}
}
