#include "dmkafx.h"
#include "VulkanCommandBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanCommandBuffer::initializeCommandPool(const VulkanDevice& vDevice, const VulkanQueue& vQueue)
		{
			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = vQueue.processFamily.value();
			poolInfo.flags = 0;

			if (vkCreateCommandPool(vDevice, &poolInfo, nullptr, &pool) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to create command pool!");
		}

		void VulkanCommandBuffer::allocateCommandBuffers(const VulkanDevice& vDevice, UI32 bufferCount)
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = pool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = static_cast<UI32>(bufferCount);

			buffers.resize(bufferCount);
			if (vkAllocateCommandBuffers(vDevice, &allocInfo, buffers.data()) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to allocate command buffers!");
		}

		const VkCommandBuffer& VulkanCommandBuffer::beginCommandBufferRecording(const VulkanDevice& vDevice, UI32 bufferIndex)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			if (vkBeginCommandBuffer(buffers[bufferIndex], &beginInfo) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to begin recording of command buffer (@ index: " + std::to_string(bufferIndex) + ")!");
		
			return buffers[bufferIndex];
		}

		void VulkanCommandBuffer::endCommandBufferRecording(const VulkanDevice& vDevice, const VkCommandBuffer& commandBuffer)
		{
			if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to record command buffer!");
		}

		void VulkanCommandBuffer::terminate(const VulkanDevice& vDevice)
		{
			vkFreeCommandBuffers(vDevice, pool, static_cast<UI32>(buffers.size()), buffers.data());
		}
		
		VulkanCommandBuffer::operator VkCommandPool() const
		{
			return this->pool;
		}
	}
}
