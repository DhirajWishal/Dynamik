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

			DMK_VULKAN_ASSERT(vkCreateCommandPool(vDevice, &poolInfo, nullptr, &pool), "Failed to create command pool!");
		}

		void VulkanCommandBuffer::allocateCommandBuffers(const VulkanDevice& vDevice, UI32 bufferCount)
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = pool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = static_cast<UI32>(bufferCount);

			buffers.resize(bufferCount);
			DMK_VULKAN_ASSERT(vkAllocateCommandBuffers(vDevice, &allocInfo, buffers.data()), "Failed to allocate command buffers!");
		}

		const VkCommandBuffer& VulkanCommandBuffer::beginCommandBufferRecording(const VulkanDevice& vDevice, UI32 bufferIndex)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			DMK_VULKAN_ASSERT(vkBeginCommandBuffer(buffers[bufferIndex], &beginInfo), "Failed to begin recording of command buffer (@ index: " + std::to_string(bufferIndex) + ")!");

			return buffers[bufferIndex];
		}

		void VulkanCommandBuffer::endCommandBufferRecording(const VulkanDevice& vDevice, const VkCommandBuffer& commandBuffer)
		{
			DMK_VULKAN_ASSERT(vkEndCommandBuffer(commandBuffer), "Failed to record command buffer!");
		}

		void VulkanCommandBuffer::resetPool(const VulkanDevice& vDevice)
		{
			DMK_VULKAN_ASSERT(vkResetCommandPool(vDevice, pool, VK_NULL_HANDLE), "Failed to reset command pool!");
		}

		void VulkanCommandBuffer::resetBuffers()
		{
			for (auto _buffer : buffers)
				DMK_VULKAN_ASSERT(vkResetCommandBuffer(_buffer, VK_NULL_HANDLE), "Failed to reset command buffer!");
		}

		void VulkanCommandBuffer::terminate(const VulkanDevice& vDevice)
		{
			vkFreeCommandBuffers(vDevice, pool, static_cast<UI32>(buffers.size()), buffers.data());
			vkDestroyCommandPool(vDevice, pool, nullptr);
		}

		VulkanCommandBuffer::operator VkCommandPool() const
		{
			return this->pool;
		}

		const VkCommandBuffer VulkanCommandBuffer::operator[](UI32 index) const
		{
			return this->buffers[index];
		}
	}
}
