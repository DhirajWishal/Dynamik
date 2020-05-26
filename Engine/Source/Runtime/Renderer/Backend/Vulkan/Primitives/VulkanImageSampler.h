#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_SAMPLER_H
#define _DYNAMIK_VULKAN_IMAGE_SAMPLER_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "VulkanImage.h"

namespace Dynamik
{
    namespace Backend
    {
        struct DMK_API VulkanImageSamplerCreateInfo {
            ImageSamplerFilter magFilter = ImageSamplerFilter::IMAGE_SAMPLER_FILTER_LINEAR;
            ImageSamplerFilter minFilter = ImageSamplerFilter::IMAGE_SAMPLER_FILTER_LINEAR;
            ImageSamplerAddressMode addressModeU = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            ImageSamplerAddressMode addressModeV = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            ImageSamplerAddressMode addressModeW = ImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            B1 enableAnisotropy = false;
            F32 maxAntisotropy = 0.0f;
            ImageSamplerBorderColor borderColor = ImageSamplerBorderColor::IMAGE_SAMPLER_BORDER_COLOR_F32_OPAQUE_BLACK;
            B1 unnormalizedCoordinates = false;
            B1 compareEnable = false;
            StencilCompareOp compareOp = StencilCompareOp::STENCIL_COMPARE_OP_NEVER;
            DMKMipMapMode mipmapMode = DMKMipMapMode::DMK_MIPMAP_MODE_LINEAR;
            F32 minLOD = 0.0f;
            F32 maxLOD = 1.0f;
            F32 mipLODBias = 1.0f;
        };

        /*
         Vulkan Image Sampler for the Dynamik RBL
        */
        class DMK_API VulkanImageSampler {
        public:
            VulkanImageSampler() {}
            ~VulkanImageSampler() {}

            void initialize(const VulkanDevice& vDevice, VulkanImageSamplerCreateInfo info);
            void terminate(const VulkanDevice& vDevice);

            operator VkSampler();

            VkSampler sampler = VK_NULL_HANDLE;
        };
    }
}

#endif // !_DYNAMIK_VULKAN_IMAGE_SAMPLER_H
