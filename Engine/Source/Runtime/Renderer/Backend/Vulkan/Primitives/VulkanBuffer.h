#pragma once
#ifndef _DYNAMIK_VULKAN_BUFFER_H
#define _DYNAMIK_VULKAN_BUFFER_H

/*
 Author:     Dhiraj Wishal
 Date:       24/05/2020
*/
#include "../Common/VulkanDevice.h"

namespace Dynamik
{
    namespace Backend
    {
        enum class DMK_API VulkanBufferType {
            VULKAN_BUFFER_TYPE_STAGGING,
            VULKAN_BUFFER_TYPE_VERTEX,
            VULKAN_BUFFER_TYPE_INDEX,
            VULKAN_BUFFER_TYPE_UNIFORM,
        };

        /*
         Vulkan Buffer Object for the Dynamik Engine
        */
        class DMK_API VulkanBuffer {
        public:
            VulkanBuffer() {}
            ~VulkanBuffer() {}

            void initialize(const VulkanDevice& vDevice, VulkanBufferType type, UI32 bufferSize);
            void terminate(const VulkanDevice& vDevice);

            operator VkBuffer();
            operator VkDeviceMemory();

            VkBuffer buffer = VK_NULL_HANDLE;
            VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_BUFFER_H
