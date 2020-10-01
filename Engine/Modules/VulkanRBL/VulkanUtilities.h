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

#include "Core/Objects/Resources/ShaderModule.h"
#include "Core/Objects/Resources/VertexBuffer.h"
#include "Core/Objects/Resources/UniformBuffer.h"

namespace Backend
{
	/*
	 Vulkan Resource Layout
	 This contains resource information of a given shader module based on its resource layout.
	*/
	struct DMK_API VulkanResourceLayout {
		std::vector<VkVertexInputAttributeDescription> vertexInputAttributes;
		std::vector<VkVertexInputBindingDescription> vertexInputBindings;
		std::vector<VkDescriptorSetLayoutBinding> descriptorBindings;
		std::vector<VkDescriptorPoolSize> descriptorPoolSizes;
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
		static bool hasStencilComponent(const VkFormat& format);
		static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
		static VkFormat findDepthFormat(const VkPhysicalDevice& physicalDevice);
		static VkComponentMapping getComponentMapping(DMKTexture::TextureSwizzles swizzles);
		static void rawTransitionImageLayout(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout, UI32 mipLevels, UI32 layerCount, DMKFormat format);

		static VkDescriptorType getDescriptorType(DMKUniformType type);
		static VkShaderStageFlagBits getShaderStage(DMKShaderLocation location);
		static DMKShaderLocation getShaderLocation(VkShaderStageFlagBits flag);
		static std::vector<VkDescriptorSetLayoutBinding> getDescriptorSetLayoutBindings(std::vector<DMKShaderModule> modules);

		static std::vector<VkVertexInputAttributeDescription> getVertexAttributeDescriptions(DMKVertexLayout descriptor);
		static std::vector<VkVertexInputAttributeDescription> getVertexAttributeDescriptions(DMKShaderModule shaderModule);
		static std::vector<VkVertexInputBindingDescription> getVertexBindingDescriptions(DMKShaderModule shaderModule);
		static VkFormat vertexAttributeTypeToVkFormat(DMKDataType type);

		static void copyDataToImage(RCoreObject* pCoreObject, RImage* pImage, void* data, UI64 byteSize, UI64 dstOffset = 0, UI64 srcOffset = 0);

	public:     /* Pipeline */
		static VkShaderModule createShaderModule(const RCoreObject* pCoreObject, const DMKShaderModule& shaderModule);
		static VkPolygonMode getPolygonMode(const RPolygonMode& ePolygonMode);
		static VkStencilOpState getStencilOpState(const RStencilOpState& opState);
		static std::vector<VkPipelineColorBlendAttachmentState> getBlendStates(const std::vector<RColorBlendState>& blendStates);
		static std::vector<VkDynamicState> getDynamicStates(const std::vector<RDynamicState>& states);
	};
}

#endif // !_DYNAMIK_VULKAN_UTILITIES_H
