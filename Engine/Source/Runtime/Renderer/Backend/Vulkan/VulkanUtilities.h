// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_UTILITIES_H
#define _DYNAMIK_VULKAN_UTILITIES_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "VulkanCoreObject.h"
#include "Context/VulkanSwapChain.h"
#include "Common/VulkanViewPort.h"
#include "Context/VulkanRenderPass.h"

#include "Object/Resource/ShaderModule.h"
#include "Object/Resource/Primitives.h"

namespace Dynamik
{
    namespace Backend 
    {
        /*
         Vulkan Utilities for the Dynamik RBL
        */
        class DMK_API VulkanUtilities {
            VulkanUtilities() {}
            ~VulkanUtilities() {}

        public:     /* Global utilities */
            static VulkanViewport getViewport(DMKViewport viewport);
            static VkPresentModeKHR getPresentMode(RSwapChainPresentMode ePresentMode);

        public:
            static VkFormat getVulkanFormat(DMKFormat format);
            static VkImageLayout getVulkanLayout(ImageLayout layout);
            static UI32 findMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
            static B1 hasStencilComponent(const VkFormat& format);
            static VkFormat findSupportedFormat(const ARRAY<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
            static VkFormat findDepthFormat(const VkPhysicalDevice& physicalDevice);
            static VkComponentMapping getComponentMapping(DMKTexture::TextureSwizzles swizzles);

            static VkDescriptorType getDescriptorType(DMKUniformType type);
            static VkShaderStageFlagBits getShaderStage(DMKShaderLocation location);
            static ARRAY<VkDescriptorSetLayoutBinding> getDescriptorSetLayoutBindings(DMKUniformBufferDescriptor descriptor);
            static ARRAY<VkDescriptorSetLayoutBinding> getDescriptorSetLayoutBindings(ARRAY<DMKShaderModule> modules);
            static ARRAY<VkDescriptorPoolSize> getDescriptorPoolSizes(DMKUniformBufferDescriptor descriptor, UI32 descriptorCount);
        
            static ARRAY<VkVertexInputAttributeDescription> VulkanUtilities::getVertexAttributeDescriptions(DMKVertexBufferDescriptor descriptor);
            static VkFormat VulkanUtilities::vertexAttributeTypeToVkFormat(DMKDataType type);
        };
    }
}

#endif // !_DYNAMIK_VULKAN_UTILITIES_H
