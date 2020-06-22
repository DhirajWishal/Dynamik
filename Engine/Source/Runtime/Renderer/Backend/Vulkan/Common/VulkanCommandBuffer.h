// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Renderer/Components/RCommandBuffer.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"

#include "../Context/VulkanRenderPass.h"
#include "../Context/VulkanFrameBuffer.h"
#include "../Context/VulkanSwapChain.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Command Buffer for the Dynamik RBL
		*/
		class DMK_API VulkanCommandBuffer : public RCommandBuffer {
		public:
			VulkanCommandBuffer() {}
			~VulkanCommandBuffer() {}

			virtual void begin() override final;
			virtual void bindPipeline(POINTER<RPipelineObject> pPipelineObject) override final;
			virtual void end() override final;

			operator VkCommandBuffer() const;

			VkCommandBuffer buffer = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_COMMAND_POOL_H
