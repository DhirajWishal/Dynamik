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
		void VulkanCommandBufferManager::initialize(POINTER<RCoreObject> pCoreObject)
		{
			VkCommandPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = Inherit<VulkanCoreObject>(pCoreObject)->queues.processFamily.value();
			poolInfo.flags = 0;

			DMK_VULKAN_ASSERT(vkCreateCommandPool(Inherit<VulkanCoreObject>(pCoreObject)->device, &poolInfo, nullptr, &pool), "Failed to create command pool!");
		}

		ARRAY<POINTER<RCommandBuffer>> VulkanCommandBufferManager::allocateCommandBuffers(POINTER<RCoreObject> pCoreObject, UI32 bufferCount)
		{
			VkCommandBufferAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.commandPool = pool;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandBufferCount = static_cast<UI32>(bufferCount);

			ARRAY<POINTER<RCommandBuffer>> _buffers(bufferCount);
			POINTER<VulkanCommandBuffer> _buffer;
			for (UI32 itr = 0; itr < bufferCount; itr++)
			{
				_buffer = StaticAllocator<VulkanCommandBuffer>::allocate();
				DMK_VULKAN_ASSERT(vkAllocateCommandBuffers(Inherit<VulkanCoreObject>(pCoreObject)->device, &allocInfo, &_buffer->buffer), "Failed to allocate command buffers!");

				_buffers.pushBack(_buffer);
			}

			return _buffers;
		}

		void VulkanCommandBufferManager::bindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer, POINTER<RRenderTarget> pRenderTarget, UI32 bufferIndex)
		{
			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = InheritCast<VulkanRenderPass>(pRenderTarget->pRenderPass);
			renderPassInfo.framebuffer = InheritCast<VulkanFrameBuffer>(pRenderTarget->pFrameBuffer)[bufferIndex];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent.width = pRenderTarget->pSwapChain->extent.width;
			renderPassInfo.renderArea.extent.height = pRenderTarget->pSwapChain->extent.height;

			std::array<VkClearValue, 2> clearValues = {};

			clearValues[0].color = {
				(2.0f / 255.0f),
				(8.0f / 255.0f),
				(32.0f / 255.0f),
				1.0f
			};

			renderPassInfo.clearValueCount = static_cast<UI32>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(InheritCast<VulkanCommandBuffer>(pCommandBuffer), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			VkViewport viewport;
			viewport.width = (F32)pRenderTarget->pSwapChain->extent.width;
			viewport.height = (F32)pRenderTarget->pSwapChain->extent.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			viewport.x = pRenderTarget->pSwapChain->viewPort.xOffset;
			viewport.y = pRenderTarget->pSwapChain->viewPort.yOffset;
			vkCmdSetViewport(InheritCast<VulkanCommandBuffer>(pCommandBuffer), 0, 1, &viewport);
		}

		void VulkanCommandBufferManager::unbindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer)
		{
			vkCmdEndRenderPass(InheritCast<VulkanCommandBuffer>(pCommandBuffer));
		}

		void VulkanCommandBufferManager::resetBuffers(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers)
		{
			for (auto _buffer : commandBuffers)
				DMK_VULKAN_ASSERT(vkResetCommandBuffer(InheritCast<VulkanCommandBuffer>(_buffer), VK_NULL_HANDLE), "Failed to reset command buffer!");
		}

		void VulkanCommandBufferManager::terminate(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers)
		{
			for (auto _buffer : commandBuffers)
			{
				auto vBuffer = InheritCast<VulkanCommandBuffer>(_buffer).buffer;
				vkFreeCommandBuffers(Inherit<VulkanCoreObject>(pCoreObject)->device, pool, 1, &vBuffer);
			}

			vkDestroyCommandPool(Inherit<VulkanCoreObject>(pCoreObject)->device, pool, nullptr);
		}
	}
}
