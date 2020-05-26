#pragma once
#ifndef _DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H
#define _DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "VulkanDevice.h"
#include "VulkanQueue.h"

namespace Dynamik
{
    namespace Backend
    {
        class DMK_API VulkanOneTimeCommandBuffer {
        public:
            VulkanOneTimeCommandBuffer(const VulkanDevice& vDevice, const VulkanQueue& vQueue);
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
}

#endif // !_DYNAMIK_VULKAN_ONE_TIME_COMMAND_BUFFER_H
