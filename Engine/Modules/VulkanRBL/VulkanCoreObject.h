// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_CORE_OBJECT_H
#define _DYNAMIK_VULKAN_CORE_OBJECT_H

#include "Renderer/Components/RCoreObject.h"

#include "Common/VulkanDevice.h"
#include "Common/VulkanQueue.h"

namespace Backend
{
	class DMK_API VulkanInstance;
	class DMK_API VulkanDevice;
	class DMK_API VulkanSurface;
	class DMK_API VulkanQueue;
}

/*
 Vulkan Core Object
*/
class DMK_API VulkanCoreObject : public RCoreObject {
public:
	VulkanCoreObject() {}
	~VulkanCoreObject() {}

	virtual void initialize(DMKRendererDescription description, DMKWindowHandle* pWindow) override final;
	virtual void terminate() override final;

	virtual void idleCall() override final;

	virtual I32 prepareFrame(RSwapChain* pSwapChain) override final;
	virtual void submitCommand(RCommandBuffer* pCommandBuffer, RSwapChain* pSwapChain) override final;

	virtual DMKFormat getDepthFormat() override final;

	operator Backend::VulkanInstance() const;
	operator Backend::VulkanDevice() const;
	operator Backend::VulkanSurface() const;
	operator Backend::VulkanQueue() const;

	Backend::VulkanInstance instance;
	Backend::VulkanDevice device;
	Backend::VulkanSurface surface;
	Backend::VulkanQueue queues;

private:
	virtual void initializeSyncComponents() override final;

	std::vector<VkSemaphore> imageAvailables;
	std::vector<VkSemaphore> renderFinished;
	std::vector<VkFence> inFlightFences;

	UI32 currentFrameIndex = 0;
	UI32 imageIndex = 0;

private:
	VkResult frameResult = VkResult::VK_ERROR_UNKNOWN;

	VkSubmitInfo submitInfo = {};
	VkPresentInfoKHR presentInfo = {};
	VkPipelineStageFlags stageFlags[1] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
};

#endif // !_DYNAMIK_VULKAN_CORE_OBJECT_H
