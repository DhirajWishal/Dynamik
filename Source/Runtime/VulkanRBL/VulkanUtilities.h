// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_UTILITIES_H
#define _DYNAMIK_VULKAN_UTILITIES_H

#include "VulkanCoreObject.h"
#include "Context/VulkanSwapChain.h"
#include "Common/VulkanViewPort.h"
#include "Context/VulkanRenderPass.h"
#include "Pipelines/VulkanGraphicsPipeline.h"

#include "Core/Objects/Resource/ShaderModule.h"
#include "Core/Objects/Resource/Primitives.h"

namespace Dynamik
{
    namespace Backend 
    {
        /*
         Vulkan Resource Layout
         This contains resource information of a given shader module based on its resource layout.
        */
        struct DMK_API VulkanResourceLayout {
            ARRAY<VkVertexInputAttributeDescription> vertexInputAttributes;
            VkVertexInputBindingDescription vertexInputBinding;
            ARRAY<VkDescriptorSetLayoutBinding> descriptorBindings;
            ARRAY<VkDescriptorPoolSize> descriptorPoolSizes;
        };

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
            static VkImageLayout getVulkanLayout(RImageLayout layout);
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
        
            static ARRAY<VkVertexInputAttributeDescription> VulkanUtilities::getVertexAttributeDescriptions(DMKVertexLayout descriptor);
            static VkFormat VulkanUtilities::vertexAttributeTypeToVkFormat(DMKDataType type);

        public:     /* Pipeline */
            static VkShaderModule createShaderModule(const RCoreObject* pCoreObject, const DMKShaderModule& shaderModule);
            static VkPolygonMode getPolygonMode(const RPolygonMode& ePolygonMode);
            static VkStencilOpState getStencilOpState(const RStencilOpState& opState);
            static ARRAY<VkPipelineColorBlendAttachmentState> getBlendStates(const ARRAY<RColorBlendState>& blendStates);
            static ARRAY<VkDynamicState> getDynamicStates(const ARRAY<RDynamicState>& states);
        };
    }
}

#endif // !_DYNAMIK_VULKAN_UTILITIES_H
