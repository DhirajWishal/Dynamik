// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BUFFER_H
#define _DYNAMIK_VULKAN_BUFFER_H

/*
 Author:     Dhiraj Wishal
 Date:       24/05/2020
*/
#include "../Common/VulkanDevice.h"
#include "Renderer/Components/PrimitiveTypeDefs.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Buffer Object for the Dynamik Engine
        */
        class DMK_API VulkanBuffer {
        public:
            VulkanBuffer() {}
            ~VulkanBuffer() {}

            void initialize(
                const VulkanDevice& vDevice,
                BufferType type,
                UI32 bufferSize,
                ResourceMemoryType memoryType = 
                (ResourceMemoryType)
                (RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
            void terminate(const VulkanDevice& vDevice);

            VPTR mapMemory(const VulkanDevice& vDevice, UI32 offset = 0);
            void unmapMemory(const VulkanDevice& vDevice);

            VkDescriptorBufferInfo createDescriptorInfo(UI32 offset = 0);

            operator VkBuffer() const;
            operator VkDeviceMemory() const;

            VkBuffer buffer = VK_NULL_HANDLE;
            VkDeviceMemory bufferMemory = VK_NULL_HANDLE;

            UI32 size = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_BUFFER_H
