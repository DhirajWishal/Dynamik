#pragma once
#ifndef _DYNAMIK_VULKAN_TEXTURE_H
#define _DYNAMIK_VULKAN_TEXTURE_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"

#include "Core/Object/Resource/TextureComponent.h"

#include "VulkanImage.h"
#include "VulkanImageSampler.h"
#include "VulkanImageView.h"

namespace Dynamik
{
    namespace Backend
    {
        class DMK_API VulkanTexture {
        public:
            VulkanTexture() {}
            ~VulkanTexture() {}

            void initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const DMKTextureComponent& textureComponent);
            void terminate(const VulkanDevice& vDevice);

            operator VulkanImage() const;
            operator VulkanImageView() const;
            operator VulkanImageSampler() const;

            VulkanImage image;
            VulkanImageView imageView;
            VulkanImageSampler sampler;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_TEXTURE_H
