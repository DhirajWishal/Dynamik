#include "dmkafx.h"
#include "VulkanSyncObjects.h"

#include "VulkanControlHeader.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanSyncObjects::initialize(const VulkanDevice& vDevice)
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
				DMK_VULKAN_ASSERT(vkCreateSemaphore(vDevice, &semaphoreInfo, nullptr, &imageAvailables.at(i)), "Failed to create image available semaphore!");
				DMK_VULKAN_ASSERT(vkCreateSemaphore(vDevice, &semaphoreInfo, nullptr, &renderFinished.at(i)), "Failed to create render finished semaphore!");
				DMK_VULKAN_ASSERT(vkCreateFence(vDevice, &fenceInfo, nullptr, &inFlightFences.at(i)), "Failed to create fence object!");
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

		void VulkanSyncObjects::syncFence(const VulkanDevice& vDevice)
		{
			vkWaitForFences(vDevice, 1, &inFlightFences[currentFrameIndex], VK_TRUE, std::numeric_limits<uint64_t>::max());
		}

		const UI32 VulkanSyncObjects::getNextImage(const VulkanDevice& vDevice, const VulkanSwapChain& vSwapChain)
		{
			imageIndex = 0;
			frameResult = vkAcquireNextImageKHR(vDevice, vSwapChain, std::numeric_limits<uint64_t>::max(), imageAvailables[currentFrameIndex], VK_NULL_HANDLE, &imageIndex);

			return imageIndex;
		}

		void VulkanSyncObjects::submitCommands(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const VulkanSwapChain& vSwapChain, const VulkanCommandBuffer& vCommandBuffer)
		{
			submitInfo.pWaitSemaphores = &imageAvailables[currentFrameIndex];
			submitInfo.pCommandBuffers = &vCommandBuffer.buffers[imageIndex];
			submitInfo.pSignalSemaphores = &renderFinished[currentFrameIndex];

			vkResetFences(vDevice, 1, &inFlightFences[currentFrameIndex]);

			DMK_VULKAN_ASSERT(vkQueueSubmit(vQueue.processQueue, 1, &submitInfo, inFlightFences[currentFrameIndex]), "Failed to submit draw command buffer!");
		
			presentInfo.pWaitSemaphores = &renderFinished[currentFrameIndex];
			presentInfo.pSwapchains = &vSwapChain.swapChain;
			presentInfo.pImageIndices = &imageIndex;

			frameResult = vkQueuePresentKHR(vQueue.utilityQueue, &presentInfo);
		}
		
		void VulkanSyncObjects::terminate(const VulkanDevice& vDevice)
		{
			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				vkDestroySemaphore(vDevice, imageAvailables[i], nullptr);
				vkDestroySemaphore(vDevice, renderFinished[i], nullptr);
				vkDestroyFence(vDevice, inFlightFences[i], nullptr);
			}
		}

		const VkSemaphore& VulkanSyncObjects::getCurrentImageAvailableSemaphore() const
		{
			return imageAvailables[currentFrameIndex];
		}

		const VkSemaphore& VulkanSyncObjects::getCurrentRenderFinishedSemaphore() const
		{
			return renderFinished[currentFrameIndex];
		}

		const VkFence& VulkanSyncObjects::getCurrentInFlightFence() const
		{
			return inFlightFences[currentFrameIndex];
		}

		const VkResult& VulkanSyncObjects::getResult() const
		{
			return frameResult;
		}
		
		void VulkanSyncObjects::operator++(I32)
		{
			this->currentFrameIndex = (this->currentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
		}
	}
}
