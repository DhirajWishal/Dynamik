// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCommandBuffer.h"

#include "../Pipelines/VulkanGraphicsPipeline.h"
#include "../VulkanUtilities.h"

#include "Core/Types/StaticArray.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanCommandBuffer::bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 bufferIndex, RSubpassContentType contentType)
		{
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass);
			renderPassInfo.framebuffer = InheritCast<VulkanFrameBuffer>(pRenderTarget->pFrameBuffer)[bufferIndex];
			renderPassInfo.renderArea.offset.x = pSwapChain->viewPort.xOffset;
			renderPassInfo.renderArea.offset.y = pSwapChain->viewPort.yOffset;
			renderPassInfo.renderArea.extent.width = (UI32)pRenderTarget->pFrameBuffer->width;
			renderPassInfo.renderArea.extent.height = (UI32)pRenderTarget->pFrameBuffer->height;

			StaticArray<VkClearValue, 2> clearValues = {};

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

			vkCmdBeginRenderPass(buffer, &renderPassInfo, Cast<VkSubpassContents>(contentType));
		}

		void VulkanCommandBuffer::begin(RCommandBufferUsage bufferUsage)
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = Cast<VkCommandBufferUsageFlagBits>(bufferUsage);

			DMK_VULKAN_ASSERT(vkBeginCommandBuffer(buffer, &beginInfo), "Failed to begin recording of command buffer!");
		}

		void VulkanCommandBuffer::beginParent()
		{
			begin(Cast<RCommandBufferUsage>(0));
		}

		void VulkanCommandBuffer::beginInherited(RRenderTarget* pRenderTarget, UI64 frameIndex)
		{
			VkCommandBufferInheritanceInfo inheritanceInfo = {};
			inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
			inheritanceInfo.pNext = VK_NULL_HANDLE;
			inheritanceInfo.renderPass = Inherit<VulkanRenderPass>(pRenderTarget->pRenderPass)->renderPass;
			inheritanceInfo.framebuffer = Inherit<VulkanFrameBuffer>(pRenderTarget->pFrameBuffer)->buffers[frameIndex];

			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			beginInfo.pInheritanceInfo = &inheritanceInfo;

			DMK_VULKAN_ASSERT(vkBeginCommandBuffer(buffer, &beginInfo), "Failed to begin recording of command buffer!");
		}

		void VulkanCommandBuffer::bindVertexBuffer(RBuffer* pBuffer, UI64 firstBinding)
		{
			VkDeviceSize offset[1] = { 0 };
			vkCmdBindVertexBuffers(this->buffer, (UI32)firstBinding, 1, &Inherit<VulkanBuffer>(pBuffer)->buffer, offset);
		}

		void VulkanCommandBuffer::bindIndexBuffer(RBuffer* pBuffer)
		{
			VkDeviceSize offset[1] = { 0 };
			vkCmdBindIndexBuffer(buffer, Inherit<VulkanBuffer>(pBuffer)->buffer, 0, VK_INDEX_TYPE_UINT32);
		}

		void VulkanCommandBuffer::bindGraphicsPipeline(RPipelineObject* pPipelineObject, RPipelineResource* pPipelineResource)
		{
			VulkanGraphicsPipeline pipeline = InheritCast<VulkanGraphicsPipeline>(pPipelineObject);
			vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

			if (pipeline.isResourceAvailable)
				vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline, 0, 1, &Inherit<VulkanGraphicsPipelineResource>(pPipelineResource)->set, 0, VK_NULL_HANDLE);

			for (auto block : pipeline.constantBlocks)
				vkCmdPushConstants(buffer, pipeline, VulkanUtilities::getShaderStage(block.location), Cast<UI32>(block.offset), Cast<UI32>(block.byteSize), block.data);
		}

		void VulkanCommandBuffer::drawIndexed(UI64 firstIndex, UI64 vertexOffset, UI64 indexCount, UI64 instanceCount)
		{
			vkCmdDrawIndexed(buffer, (UI32)indexCount, (UI32)instanceCount, (UI32)firstIndex, (UI32)vertexOffset, 0);
		}

		void VulkanCommandBuffer::drawVertexes(UI64 vertexIndex, UI64 vertexCount, UI64 instanceCount)
		{
			vkCmdDraw(buffer, (UI32)vertexCount, (UI32)instanceCount, (UI32)vertexIndex, 0);
		}

		void VulkanCommandBuffer::unbindRenderTarget()
		{
			vkCmdEndRenderPass(buffer);
		}

		void VulkanCommandBuffer::end()
		{
			DMK_VULKAN_ASSERT(vkEndCommandBuffer(buffer), "Failed to record command buffer!");
		}

		void VulkanCommandBuffer::executeSecondaryCommands(RCommandBuffer* pParentCommandBuffer)
		{
			vkCmdExecuteCommands(*Inherit<VulkanCommandBuffer>(pParentCommandBuffer), 1, &buffer);
		}

		VulkanCommandBuffer::operator VkCommandBuffer() const
		{
			return this->buffer;
		}
	}
}
