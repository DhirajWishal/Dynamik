// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_FRAME_BUFFER_H
#define _DYNAMIK_VULKAN_FRAME_BUFFER_H

#include "Renderer/Components/Context/RFrameBuffer.h"
#include "VulkanRenderPass.h"
#include "VulkanSwapChain.h"

namespace Backend
{
	/*
	 Vulkan Frame Buffer object for the Dynamik Engine
	*/
	class DMK_API VulkanFrameBuffer : public RFrameBuffer {
	public:
		VulkanFrameBuffer() {}
		~VulkanFrameBuffer() {}

		virtual void initialize(RCoreObject* pCoreObject, RRenderPass* pRenderPass, DMKExtent2D frameExtent, UI32 bufferCount, std::vector<std::vector<RFrameBufferAttachment*>> pAttachments) override final;
		virtual void terminate(RCoreObject* pCoreObject) override final;

		const VkFramebuffer operator[](UI32 index) const;

		std::vector<VkFramebuffer> buffers;
	};
}

#endif // !_DYNAMIK_VULKAN_FRAME_BUFFER_H