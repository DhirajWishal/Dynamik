#include "dmkafx.h"
#include "VulkanCommandBuffer.h"

#include <array>

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

		void VulkanCommandBuffer::beginRenderPass(
			const VulkanDevice& vDevice,
			const VulkanRenderPass& vRenderPass,
			const VulkanFrameBuffer& vFrameBuffer,
			const VulkanSwapChain& vSwapChain,
			UI32 bufferIndex,
			ARRAY<F32> clearScrValues)
		{
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = vRenderPass;
			renderPassInfo.framebuffer = vFrameBuffer[bufferIndex];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = vSwapChain.swapChainExtent;

			std::array<VkClearValue, 2> clearValues = {};

			clearValues[0].color = {
				clearScrValues[0],
				clearScrValues[1],
				clearScrValues[2],
				clearScrValues[3]
			};

			renderPassInfo.clearValueCount = static_cast<UI32>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(buffers[bufferIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			VkViewport viewport;
			viewport.width = (F32)vSwapChain.myViewport.width;
			viewport.height = (F32)vSwapChain.myViewport.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			viewport.x = vSwapChain.myViewport.xOffset;
			viewport.y = vSwapChain.myViewport.yOffset;
			vkCmdSetViewport(buffers[bufferIndex], 0, 1, &viewport);
		}

		void VulkanCommandBuffer::endRenderPass(const VkCommandBuffer& buffer)
		{
			vkCmdEndRenderPass(buffer);
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
