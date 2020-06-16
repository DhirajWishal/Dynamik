// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_FRAME_BUFFER_ATTACHMENT_H
#define _DYNAMIK_VULKAN_FRAME_BUFFER_ATTACHMENT_H

/*
 Author:    Dhiraj Wishal
 Date:      28/05/2020
*/
#include "../Primitives/VulkanImageView.h"

namespace Dynamik
{
    namespace Backend
    {
        class DMK_API VulkanImage;
        class DMK_API VulkanImageView;

        /*
         Vulkan Frame Buffer Attachment Info
        */
        struct DMK_API VulkanFrameBufferAttachmentInitInfo {
            DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
            DMKSampleCount msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
            UI32 imageWidth = 0;
            UI32 imageHeight = 0;
        };

        /*
         Vulkan Frame Buffer Attachment for the Dynamik RBL
        */
        class DMK_API VulkanFrameBufferAttachment {
        public:
            VulkanFrameBufferAttachment() {}
            virtual ~VulkanFrameBufferAttachment() {}

            virtual void initialize(POINTER<RCoreObject> pCoreObject, VulkanFrameBufferAttachmentInitInfo initInfo) {}
            virtual void terminate(POINTER<RCoreObject> pCoreObject);

            operator VulkanImage() const;
            operator VulkanImageView() const;

            VulkanImage image;
            VulkanImageView imageView;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_FRAME_BUFFER_ATTACHMENT_H
