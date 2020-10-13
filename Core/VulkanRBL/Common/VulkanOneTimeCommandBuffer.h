// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H

#include "VulkanDevice.h"
#include "VulkanQueue.h"

#include "Renderer/Components/RCoreObject.h"

namespace Backend
{
	/*
	 Vulkan one time command buffer
	*/
	class DMK_API VulkanOneTimeCommandBuffer {
	public:
		VulkanOneTimeCommandBuffer(RCoreObject* pCoreObject);
		~VulkanOneTimeCommandBuffer();

		operator VkCommandBuffer() const;
		operator VkCommandPool() const;

		VkCommandBuffer buffer = VK_NULL_HANDLE;
		VkCommandPool pool = VK_NULL_HANDLE;

	private:
		VulkanDevice myDevice;
		VulkanQueue myQueues;
	};
}

#endif // !_DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H
