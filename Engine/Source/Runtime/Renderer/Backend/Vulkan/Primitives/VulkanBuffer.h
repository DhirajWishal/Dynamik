// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BUFFER_H
#define _DYNAMIK_VULKAN_BUFFER_H

/*
 Author:     Dhiraj Wishal
 Date:       24/05/2020
*/
#include "Renderer/Components/Primitives/RBuffer.h"
#include "../Common/VulkanDevice.h"
#include "Renderer/Components/PrimitiveTypeDefs.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Buffer Object for the Dynamik Engine
        */
        class DMK_API VulkanBuffer : public RBuffer {
        public:
            VulkanBuffer() {}
            ~VulkanBuffer() {}

            virtual void initialize(RCoreObject* pCoreObject, RBufferType eType, UI64 uSize,
                RResourceMemoryType memoryType = (RResourceMemoryType)
                (RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT)) override final;
            virtual void terminate(RCoreObject* pCoreObject) override final;

            virtual void setData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset, VPTR data) override final;
            virtual VPTR getData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset) override final;
            virtual void unmapMemory(RCoreObject* pCoreObject) override final;

            VkDescriptorBufferInfo createDescriptorInfo(UI32 offset = 0);

            operator VkBuffer() const;
            operator VkDeviceMemory() const;

            VkBuffer buffer = VK_NULL_HANDLE;
            VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_BUFFER_H
