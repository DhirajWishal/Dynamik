// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H
#define _DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H

#include <vulkan/vulkan.h>
#include "Renderer/Components/RCommandBufferManager.h"

namespace Backend
{
	/*
	 Vulkan Command Buffer Manager
	*/
	class DMK_API VulkanCommandBufferManager : public RCommandBufferManager {
	public:
		VulkanCommandBufferManager() {}
		~VulkanCommandBufferManager() {}

		virtual void initialize(RCoreObject* pCoreObject) override final;
		virtual std::vector<RCommandBuffer*> allocateCommandBuffers(RCoreObject* pCoreObject, UI32 bufferCount, RCommandBufferLevel level = RCommandBufferLevel::COMMAND_BUFFEER_LEVEL_PRIMARY) override final;
		virtual void resetBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) override final;
		virtual void terminateBuffers(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) override final;
		virtual void terminate(RCoreObject* pCoreObject, std::vector<RCommandBuffer*> commandBuffers) override final;

	private:
		VkCommandPool pool = VK_NULL_HANDLE;
	};
}

#endif // !_DYNAMIK_VULKAN_COMMAND_BUFFER_MANAGER_H
