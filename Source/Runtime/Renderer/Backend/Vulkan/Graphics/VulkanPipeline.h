// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_PIPELINE_H
#define _DYNAMIK_VULKAN_PIPELINE_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "../Common/VulkanDevice.h"
#include "../Context/VulkanRenderPass.h"

namespace Dynamik
{
    namespace Backend 
    {
        class DMK_API VulkanPipeline 
        {
        public:
            VulkanPipeline() {}
            ~VulkanPipeline() {}

            void terminate(const VulkanDevice& vDevice);

            operator VkPipeline() const;
            operator VkPipelineLayout() const;

            VkPipeline pipeline = VK_NULL_HANDLE;
            VkPipelineLayout layout = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_PIPELINE_H
