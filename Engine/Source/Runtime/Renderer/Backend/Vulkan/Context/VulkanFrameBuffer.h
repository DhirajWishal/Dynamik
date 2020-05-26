#pragma once
#ifndef _DYNAMIK_VULKAN_FRAME_BUFFER_H
#define _DYNAMIK_VULKAN_FRAME_BUFFER_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "VulkanRenderPass.h"
#include "../Primitives/VulkanImageView.h"

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
                UI32 bufferCount,
                const VulkanRenderPass& vRenderPass,
                const ARRAY<VulkanImageView>& attachments,
                UI32 width, UI32 height);
            void terminate(const VulkanDevice& vDevice);

            const VkFramebuffer operator[](UI32 index);

            ARRAY<VkFramebuffer> buffers;
            UI32 frameWidth = 0, frameHeight = 0;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_FRAME_BUFFER_H
