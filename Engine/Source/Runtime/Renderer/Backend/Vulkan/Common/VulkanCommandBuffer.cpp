// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCommandBuffer.h"

#include <array>

namespace Dynamik
{
	namespace Backend
	{
		void VulkanCommandBuffer::begin()
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			DMK_VULKAN_ASSERT(vkBeginCommandBuffer(buffer, &beginInfo), "Failed to begin recording of command buffer!");
		}

		void VulkanCommandBuffer::bindPipeline(RPipelineObject* pPipelineObject)
		{
		}

		void VulkanCommandBuffer::end()
		{
			DMK_VULKAN_ASSERT(vkEndCommandBuffer(buffer), "Failed to record command buffer!");
		}

		VulkanCommandBuffer::operator VkCommandBuffer() const
		{
			return this->buffer;
		}
	}
}
