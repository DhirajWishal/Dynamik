// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCommandBuffer.h"

#include "../Pipelines/VulkanGraphicsPipeline.h"
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

		void VulkanCommandBuffer::bindVertexBuffer(RBuffer* pBuffer, UI64 firstBinding)
		{
			VkDeviceSize offset[1] = { 0 };
			vkCmdBindVertexBuffers(this->buffer, firstBinding, 1, &Inherit<VulkanBuffer>(pBuffer)->buffer, offset);
		}

		void VulkanCommandBuffer::bindIndexBuffer(RBuffer* pBuffer)
		{
			VkDeviceSize offset[1] = { 0 };
			vkCmdBindIndexBuffer(buffer, Inherit<VulkanBuffer>(pBuffer)->buffer, 0, VK_INDEX_TYPE_UINT32);
		}

		void VulkanCommandBuffer::bindGraphicsPipeline(RPipelineObject* pPipelineObject)
		{
			VulkanGraphicsPipeline pipeline = InheritCast<VulkanGraphicsPipeline>(pPipelineObject);
			vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

			ARRAY<VkDescriptorSet> descriptorSets;
			for (auto descriptor : pipeline.descriptors)
				descriptorSets.pushBack(descriptor.set);

			if (pipeline.descriptors.size())
				vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline, 0, pipeline.descriptors.size(), descriptorSets.data(), 0, VK_NULL_HANDLE);
		}

		void VulkanCommandBuffer::drawIndexed(UI64 firstIndex, UI64 vertexOffset, UI64 indexCount, UI64 instanceCount)
		{
			vkCmdDrawIndexed(buffer, indexCount, instanceCount, firstIndex, vertexOffset, 0);
		}

		void VulkanCommandBuffer::drawVertexes(UI64 vertexIndex, UI64 vertexCount, UI64 instanceCount)
		{
			vkCmdDraw(buffer, vertexCount, instanceCount, vertexIndex, 0);
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
