#pragma once
#ifndef _DYNAMIK_VULKAN_SYNC_OBJECTS_H
#define _DYNAMIK_VULKAN_SYNC_OBJECTS_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "VulkanDevice.h"
#include "VulkanCommandBuffer.h"

#include "../Context/VulkanSwapChain.h"

#include "Types/Array.h"

namespace Dynamik
{
    namespace Backend 
    {
        /*
         Vulkan Sync Objects for the Dynamik RBL.
         By calling the increment operator (VulkanSyncObjects++) the current frame index can be increamented by 
         1 but it will always be in between the 0 and the maximum number of frames in flight.
        */
        class DMK_API VulkanSyncObjects {
        public:
            VulkanSyncObjects() {}
            ~VulkanSyncObjects() {}

            void initialize(const VulkanDevice& vDevice);
            void syncFence(const VulkanDevice& vDevice);
            const UI32 getNextImage(const VulkanDevice& vDevice, const VulkanSwapChain& vSwapChain);
            void submitCommands(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const VulkanSwapChain& vSwapChain, const VulkanCommandBuffer& vCommandBuffer);
            void terminate(const VulkanDevice& vDevice);

            const VkSemaphore& getCurrentImageAvailableSemaphore() const;
            const VkSemaphore& getCurrentRenderFinishedSemaphore() const;
            const VkFence& getCurrentInFlightFence() const;
            const VkResult& getResult() const;

            void operator++(I32);

            ARRAY<VkSemaphore> imageAvailables;
            ARRAY<VkSemaphore> renderFinished;
            ARRAY<VkFence> inFlightFences;

            UI32 currentFrameIndex = 0;
            UI32 imageIndex = 0;

        private:
            VkResult frameResult = VkResult::VK_ERROR_UNKNOWN;

            VkSubmitInfo submitInfo = {};
            VkPresentInfoKHR presentInfo = {};
            VkPipelineStageFlags stageFlags[1] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        };
    }
}

#endif // !_DYNAMIK_VULKAN_SYNC_OBJECTS_H
