// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCommandBufferManager.h"

#include "VulkanCommandBuffer.h"
#include "../VulkanCoreObject.h"

#include <array>

namespace Backend
{
	void VulkanCommandBufferManager::initialize(RCoreObject* pCoreObject)
	{
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = pCoreObject->getAs<VulkanCoreObject>()->queues.processFamily.value();
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		DMK_VULKAN_ASSERT(vkCreateCommandPool(pCoreObject->getAs<VulkanCoreObject>()->device, &poolInfo, nullptr, &pool), "Failed to create command pool!");
	}

	std::vector<RCommandBuffer*> VulkanCommandBufferManager::allocateCommandBuffers(RCoreObject* pCoreObject, UI32 bufferCount, RCommandBufferLevel level)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = pool;
		allocInfo.level = Cast<VkCommandBufferLevel>(level);
		allocInfo.commandBufferCount = static_cast<UI32>(bufferCount);

		std::vector<VkCommandBuffer> _bufferArray(bufferCount);
		DMK_VULKAN_ASSERT(vkAllocateCommandBuffers(pCoreObject->getAs<VulkanCoreObject>()->device, &allocInfo, _bufferArray.data()), "Failed to allocate command buffers!");

		std::vector<RCommandBuffer*> _buffers;
		VulkanCommandBuffer* _buffer = nullptr;

		for (UI32 itr = 0; itr < bufferCount; itr++)
		{
			_buffer = StaticAllocator<VulkanCommandBuffer>::rawAllocate();
			_buffer->buffer = _bufferArray[itr];
			_buffers.push_back(_buffer);
		}

		return _buffers;
	}

	void VulkanCommandBufferManager::resetBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers)
	{
		for (auto _buffer : commandBuffers)
			DMK_VULKAN_ASSERT(vkResetCommandBuffer(Inherit<VulkanCommandBuffer>(_buffer)->buffer, VK_NULL_HANDLE), "Failed to reset command buffer!");
	}

	void VulkanCommandBufferManager::terminateBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers)
	{
		for (auto _buffer : commandBuffers)
		{
			vkFreeCommandBuffers(pCoreObject->getAs<VulkanCoreObject>()->device, pool, 1, &Inherit<VulkanCommandBuffer>(_buffer)->buffer);
			StaticAllocator<VulkanCommandBuffer>::rawDeallocate(_buffer);
		}
	}

	void VulkanCommandBufferManager::terminate(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers)
	{
		terminateBuffers(pCoreObject, commandBuffers);

		vkDestroyCommandPool(pCoreObject->getAs<VulkanCoreObject>()->device, pool, nullptr);
	}
}
