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
		void VulkanCommandBuffer::bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 bufferIndex)
		{
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass);
			renderPassInfo.framebuffer = InheritCast<VulkanFrameBuffer>(pRenderTarget->pFrameBuffer)[bufferIndex];
			renderPassInfo.renderArea.offset.x = pSwapChain->viewPort.xOffset;
			renderPassInfo.renderArea.offset.y = pSwapChain->viewPort.yOffset;
			renderPassInfo.renderArea.extent.width = pSwapChain->extent.width;
			renderPassInfo.renderArea.extent.height = pSwapChain->extent.height;

			std::array<VkClearValue, 2> clearValues = {};

			clearValues[0].color = {
				(2.0f / 255.0f),
				(8.0f / 255.0f),
				(32.0f / 255.0f),
				1.0f
			};
			clearValues[1].depthStencil.depth = 1.0f;
			clearValues[1].depthStencil.stencil = 0;

			renderPassInfo.clearValueCount = static_cast<UI32>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			//VkViewport viewPort;
			//viewPort.width = (F32)pSwapChain->extent.width;
			//viewPort.height = (F32)pSwapChain->extent.height;
			//viewPort.minDepth = 0.0f;
			//viewPort.maxDepth = 1.0f;
			//viewPort.x = pSwapChain->viewPort.xOffset;
			//viewPort.y = pSwapChain->viewPort.yOffset;
			//vkCmdSetViewport(Inherit<VulkanCommandBuffer>(pCommandBuffer)->buffer, 0, 1, &viewPort);
		}

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

			if (pipeline.isResourceAvailable)
				vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline, 0, 1, &pipeline.descriptor.set, 0, VK_NULL_HANDLE);
		}

		void VulkanCommandBuffer::drawIndexed(UI64 firstIndex, UI64 vertexOffset, UI64 indexCount, UI64 instanceCount)
		{
			vkCmdDrawIndexed(buffer, indexCount, instanceCount, firstIndex, vertexOffset, 0);
		}

		void VulkanCommandBuffer::drawVertexes(UI64 vertexIndex, UI64 vertexCount, UI64 instanceCount)
		{
			vkCmdDraw(buffer, vertexCount, instanceCount, vertexIndex, 0);
		}

		void VulkanCommandBuffer::unbindRenderTarget()
		{
			vkCmdEndRenderPass(buffer);
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
