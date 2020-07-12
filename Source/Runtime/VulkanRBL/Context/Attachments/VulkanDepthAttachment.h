// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H
#define _DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H

#include "../VulkanFrameBufferAttachment.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Depth Attachment for the Dynamik RBL
        */
        class DMK_API VulkanDepthAttachment : public VulkanFrameBufferAttachment {
        public:
            VulkanDepthAttachment() {}
            ~VulkanDepthAttachment() {}

            void initialize(RCoreObject* pCoreObject, VulkanFrameBufferAttachmentInitInfo initInfo) override;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H
