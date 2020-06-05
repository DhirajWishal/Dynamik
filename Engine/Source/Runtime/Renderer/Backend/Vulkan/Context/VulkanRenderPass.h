#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_PASS_H
#define _DYNAMIK_VULKAN_RENDER_PASS_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
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
        class DMK_API VulkanRenderPass {
        public:
            VulkanRenderPass() {}
            ~VulkanRenderPass() {}

            void initialize(const VulkanDevice& vDevice, ARRAY<VulkanRenderPassSubpass> subPasses);
            void terminate(const VulkanDevice& vDevice);

            operator VkRenderPass() const;

            VkRenderPass renderPass = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_RENDER_PASS_H
