// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_PASS_H
#define _DYNAMIK_VULKAN_RENDER_PASS_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "Renderer/Components/Context/RRenderPass.h"

#include "../Common/VulkanDevice.h"
#include "Renderer/Components/ContextTypeDefs.h"
#include "Renderer/Components/CoreTypeDefs.h"

namespace Dynamik
{
    namespace Backend 
    {
        struct DMK_API VulkanRenerPassAtachmentDescription {
            RenderPassAttachment attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
            DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
            DMKSampleCount msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
        };

        struct DMK_API VulkanRenderPassSubpass {
            ARRAY<VulkanRenerPassAtachmentDescription> attachments;
        };

        /*
         Vulkan Render Pass object for the Dynamik RBL
        */
        class DMK_API VulkanRenderPass : public RRenderPass {
        public:
            VulkanRenderPass() {}
            ~VulkanRenderPass() {}

            virtual void initialize(RCoreObject* pCoreObject, ARRAY<RSubPasses> aSubPasses, RSwapChain* pSwapChain) override;
            virtual void terminate(RCoreObject* pCoreObject) override;

            operator VkRenderPass() const;

            VkRenderPass renderPass = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_RENDER_PASS_H
