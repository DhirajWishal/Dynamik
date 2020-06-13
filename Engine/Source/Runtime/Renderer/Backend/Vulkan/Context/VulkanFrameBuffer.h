// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_FRAME_BUFFER_H
#define _DYNAMIK_VULKAN_FRAME_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "VulkanRenderPass.h"
#include "VulkanSwapChain.h"
#include "VulkanFrameBufferAttachment.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Frame Buffer object for the Dynamik Engine
        */
        class DMK_API VulkanFrameBuffer {
        public:
            VulkanFrameBuffer() {}
            ~VulkanFrameBuffer() {}

            void initialize(
                const VulkanDevice& vDevice,
                const VulkanSwapChain& vSwapChain,
                const VulkanRenderPass& vRenderPass,
                const ARRAY<POINTER<VulkanFrameBufferAttachment>>& attachments);
            void terminate(const VulkanDevice& vDevice);

            const VkFramebuffer operator[](UI32 index) const;

            ARRAY<VkFramebuffer> buffers;
            UI32 frameWidth = 0, frameHeight = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_FRAME_BUFFER_H
