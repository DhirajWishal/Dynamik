// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanCoreObject.h"

#include "Common/VulkanCommandBuffer.h"
#include "Context/VulkanSwapChain.h"
#include "Common/VulkanControlHeader.h"

namespace Dynamik
{
	void VulkanCoreObject::initialize(DMKWindowHandle* pWindow, DMKSampleCount eSamples, B1 bEnableValidation)
	{
		/* Initialize the Vulkan Instance */
		instance.initialize(bEnableValidation);

		/* Initialize the Vulkan Surface */
		surface.initialize(instance, pWindow);

		/* Initialize the Vulkan Device */
		device.initialize(instance, surface);

		sampleCount = eSamples;
		if ((UI32)eSamples > (UI32)device.getMaxUsableSampleCount())
		{
			DMKErrorManager::logWarn(DMK_TEXT("Pre defined samples are not supported by the GPU. Setting the default to the maximum usable count."));
			sampleCount = (DMKSampleCount)device.getMaxUsableSampleCount();
		}

		/* Initialize the Vulkan Queues */
		queues.findQueueFamilies(device, surface);
		queues.initializeQueues(device);

		/* Initialize the Vulkan Sync Objects */
		initializeSyncComponents();
	}

	void VulkanCoreObject::terminate()
	{
		/* Terminate surface */
		surface.terminate(instance);

		/* Terminate devices */
		device.terminate(instance);

		/* Terminate instance */
		instance.terminate();
	}

	void VulkanCoreObject::idleCall()
	{
		vkDeviceWaitIdle(device);
	}

	UI32 VulkanCoreObject::prepareFrame(RSwapChain* pSwapChain)
	{
		vkWaitForFences(device, 1, &inFlightFences[currentFrameIndex], VK_TRUE, std::numeric_limits<uint64_t>::max());

		imageIndex = 0;
		frameResult = vkAcquireNextImageKHR(device, InheritCast<Backend::VulkanSwapChain>(pSwapChain), std::numeric_limits<uint64_t>::max(), imageAvailables[currentFrameIndex], VK_NULL_HANDLE, &imageIndex);

		/* Check if any errors were encountered */
		if (frameResult == VK_ERROR_OUT_OF_DATE_KHR)
		{
			//recreateSwapChain();
			return 0;
		}
		else if (frameResult != VK_SUCCESS && frameResult != VK_SUBOPTIMAL_KHR)
			DMK_ERROR_BOX("Failed to acquire Swap Chain image!");

		return imageIndex;
	}

	void VulkanCoreObject::submitCommand(RCommandBuffer* pCommandBuffer, RSwapChain* pSwapChain)
	{
		submitInfo.pWaitSemaphores = &imageAvailables[currentFrameIndex];
		submitInfo.pCommandBuffers = &Inherit<Backend::VulkanCommandBuffer>(pCommandBuffer)->buffer;
		submitInfo.pSignalSemaphores = &renderFinished[currentFrameIndex];

		vkResetFences(device, 1, &inFlightFences[currentFrameIndex]);

		DMK_VULKAN_ASSERT(vkQueueSubmit(queues.processQueue, 1, &submitInfo, inFlightFences[currentFrameIndex]), "Failed to submit draw command buffer!");

		presentInfo.pWaitSemaphores = &renderFinished[currentFrameIndex];
		presentInfo.pSwapchains = &Inherit<Backend::VulkanSwapChain>(pSwapChain)->swapChain;
		presentInfo.pImageIndices = &imageIndex;

		frameResult = vkQueuePresentKHR(queues.utilityQueue, &presentInfo);
		this->currentFrameIndex = (this->currentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	VulkanCoreObject::operator Backend::VulkanInstance() const
	{
		return instance;
	}

	VulkanCoreObject::operator Backend::VulkanDevice() const
	{
		return device;
	}

	VulkanCoreObject::operator Backend::VulkanSurface() const
	{
		return surface;
	}

	VulkanCoreObject::operator Backend::VulkanQueue() const
	{
		return queues;
	}
	
	void VulkanCoreObject::initializeSyncComponents()
	{
		imageAvailables.resize(MAX_FRAMES_IN_FLIGHT);
		renderFinished.resize(MAX_FRAMES_IN_FLIGHT);
		inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			DMK_VULKAN_ASSERT(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailables.at(i)), "Failed to create image available semaphore!");
			DMK_VULKAN_ASSERT(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinished.at(i)), "Failed to create render finished semaphore!");
			DMK_VULKAN_ASSERT(vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences.at(i)), "Failed to create fence object!");
		}

		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.commandBufferCount = 1;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pWaitDstStageMask = stageFlags;

		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.swapchainCount = 1;
	}
}
