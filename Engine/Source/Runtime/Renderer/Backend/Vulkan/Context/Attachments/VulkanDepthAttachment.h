// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H
#define _DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H

/*
 Author:    Dhiraj Wishal
 Date:      29/05/2020
*/
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

            void initialize(POINTER<RCoreObject> pCoreObject, VulkanFrameBufferAttachmentInitInfo initInfo) override;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_DEPTH_ATTACHMENT_H
