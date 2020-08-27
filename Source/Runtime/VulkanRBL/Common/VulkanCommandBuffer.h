// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_H

#include "Renderer/Components/RCommandBuffer.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"

#include "../Context/VulkanRenderPass.h"
#include "../Context/VulkanFrameBuffer.h"
#include "../Context/VulkanSwapChain.h"

namespace Backend
{
	/*
	 Vulkan Command Buffer for the Dynamik RBL
	*/
	class DMK_API VulkanCommandBuffer : public RCommandBuffer {
	public:
		VulkanCommandBuffer() {}
		~VulkanCommandBuffer() {}

		virtual void begin(RCommandBufferUsage bufferUsage = RCommandBufferUsage::COMMAND_BUFFER_USAGE_SIMULTANEOUS) override final;
		virtual void beginParent() override final;
		virtual void beginInherited(RRenderTarget* pRenderTarget, UI64 frameIndex) override final;
		virtual void bindRenderTarget(RRenderTarget* pRenderTarget, RSwapChain* pSwapChain, UI32 bufferIndex, RSubpassContentType contentType = RSubpassContentType::SUBPASS_CONTENT_TYPE_INLINE) override final;
		virtual void bindVertexBuffer(RBuffer* pBuffer, UI64 firstBinding) override final;
		virtual void bindIndexBuffer(RBuffer* pBuffer) override final;
		virtual void bindGraphicsPipeline(RPipelineObject* pPipelineObject, RPipelineResource* pPipelineResource) override final;
		virtual void drawIndexed(UI64 firstIndex, UI64 vertexOffset, UI64 indexCount, UI64 instanceCount) override final;
		virtual void drawVertexes(UI64 vertexIndex, UI64 vertexCount, UI64 instanceCount) override final;
		virtual void unbindRenderTarget() override final;
		virtual void end() override final;
		virtual void executeSecondaryCommands(RCommandBuffer* pParentCommandBuffer) override final;

		operator VkCommandBuffer() const;

		VkCommandBuffer buffer = VK_NULL_HANDLE;
	};
}

#endif // !_DYNAMIK_VULKAN_COMMAND_POOL_H
