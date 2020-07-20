// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_COLOR_ATTACHMENT_H
#define _DYNAMIK_VULKAN_COLOR_ATTACHMENT_H

#include "Renderer/Components/Context/RFrameBufferAttachment.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Color Attachment for the Dynamik RBL
        */
        class DMK_API VulkanColorAttachment : public RFrameBufferAttachment {
        public:
            VulkanColorAttachment() {}
            ~VulkanColorAttachment() {}

            virtual void initialize(RCoreObject* pCoreObject, RFrameBufferAttachmentInfo initInfo) override final;
            virtual void terminate(RCoreObject* pCoreObject) override final;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_COLOR_ATTACHMENT_H
