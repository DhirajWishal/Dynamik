// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_TEXTURE_H
#define _DYNAMIK_VULKAN_TEXTURE_H

#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"

#include "Core/Objects/Resources/Texture.h"
#include "Renderer/Components/Primitives/RTexture.h"

#include "VulkanImage.h"
#include "VulkanImageSampler.h"
#include "VulkanImageView.h"

namespace Dynamik
{
    namespace Backend
    {
        /*
         Vulkan Texture object for the Dynamik RBL
        */
        class DMK_API VulkanTexture : public RTexture {
        public:
            VulkanTexture() {}
            ~VulkanTexture() {}

            virtual void initialize(RCoreObject* pCoreObject, DMKTexture* pTextureObject) override final;
            virtual void createView(RCoreObject* pCoreObject) override final;
            virtual void createSampler(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo) override final;
            virtual void makeRenderable(RCoreObject* pCoreObject) override final;
            virtual void terminate(RCoreObject* pCoreObject) override final;

            operator VulkanImage() const;
            operator VulkanImageView() const;
            operator VulkanImageSampler() const;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_TEXTURE_H
