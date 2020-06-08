#pragma once
#ifndef _DYNAMIK_VULKAN_TEXTURE_H
#define _DYNAMIK_VULKAN_TEXTURE_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"

#include "Object/Resource/Texture.h"

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
        class DMK_API VulkanTexture {
        public:
            VulkanTexture() {}
            ~VulkanTexture() {}

            void initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, POINTER<DMKTexture> textureComponent);
            void initializeView(const VulkanDevice& vDevice);
            void initializeSampler(const VulkanDevice& vDevice);
            void terminate(const VulkanDevice& vDevice);

            operator VulkanImage() const;
            operator VulkanImageView() const;
            operator VulkanImageSampler() const;

            VulkanImage image;
            VulkanImageView imageView;
            VulkanImageSampler sampler;
            POINTER<DMKTexture> texture;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_TEXTURE_H
