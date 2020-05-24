#pragma once
#ifndef _DYNAMIK_VULKAN_QUEUE_H
#define _DYNAMIK_VULKAN_QUEUE_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Macros/Global.h"
#include "Types/DataTypes.h"
#include <vulkan/vulkan.h>
#include <optional>

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Queue object for the Dynamik Engine
        */
        class DMK_API VulkanQueue {
        public:
            VulkanQueue() {}
            ~VulkanQueue() {}

            void findQueueFamilies(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);
            void initializeQueues(const VkDevice& logicalDevice);

            std::optional<UI32> processFamily;      /* Graphics Family */
            std::optional<UI32> utilityFamily;      /* Present Family */

            B1 isComplete();

            VkQueue processQueue = VK_NULL_HANDLE;
            VkQueue utilityQueue = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_QUEUE_H
