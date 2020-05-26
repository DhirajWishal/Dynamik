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
		}

		void VulkanSyncObjects::syncFence(const VulkanDevice& vDevice)
		{
			vkWaitForFences(vDevice, 1, &inFlightFences[currentFrameIndex], VK_TRUE, std::numeric_limits<uint64_t>::max());
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
		
		void VulkanSyncObjects::operator++(I32)
		{
			this->currentFrameIndex = (this->currentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
		}
	}
}
