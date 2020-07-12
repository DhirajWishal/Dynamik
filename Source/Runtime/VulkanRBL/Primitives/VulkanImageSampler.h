// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_SAMPLER_H
#define _DYNAMIK_VULKAN_IMAGE_SAMPLER_H

#include "VulkanImage.h"
#include "Renderer/Components/Primitives/RImageSampler.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Image Sampler for the Dynamik RBL
        */
        class DMK_API VulkanImageSampler : public RImageSampler {
        public:
            VulkanImageSampler() {}
            ~VulkanImageSampler() {}

            virtual void initialize(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo) override final;
            virtual void terminate(RCoreObject* pCoreObject) override final;

            operator VkSampler();

            VkSampler sampler = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_IMAGE_SAMPLER_H
