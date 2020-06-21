// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		16/06/2020
*/
#include <vulkan/vulkan.h>
#include "Renderer/Components/RCommandBufferManager.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Command Buffer Manager
		*/
		class DMK_API VulkanCommandBufferManager : public RCommandBufferManager {
		public:
			VulkanCommandBufferManager() {}
			~VulkanCommandBufferManager() {}

			virtual void initialize(POINTER<RCoreObject> pCoreObject) override final;
			virtual ARRAY<POINTER<RCommandBuffer>> allocateCommandBuffers(POINTER<RCoreObject> pCoreObject, UI32 bufferCount) override final;
			virtual void bindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer, POINTER<RRenderTarget> pRenderTarget, DMKViewport viewport, UI32 bufferIndex) override final;
			virtual void unbindRenderTarget(POINTER<RCommandBuffer> pCommandBuffer) override final;
			virtual void resetBuffers(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers) override final;
			virtual void terminate(POINTER<RCoreObject> pCoreObject, ARRAY<POINTER<RCommandBuffer>> commandBuffers) override final;

		private:
			VkCommandPool pool = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H
