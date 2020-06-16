// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_SAMPLER_H
#define _DYNAMIK_VULKAN_IMAGE_SAMPLER_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
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

            virtual void initialize(POINTER<RCoreObject> pCoreObject, RImageSamplerCreateInfo createInfo) override final;
            virtual void terminate(POINTER<RCoreObject> pCoreObject) override final;

            operator VkSampler();

            VkSampler sampler = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_IMAGE_SAMPLER_H
