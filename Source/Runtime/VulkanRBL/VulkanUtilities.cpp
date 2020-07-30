// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		VulkanViewport VulkanUtilities::getViewport(DMKViewport viewport)
		{
			VulkanViewport _viewport;
			_viewport.width = viewport.width;
			_viewport.height = viewport.height;
			_viewport.xOffset = viewport.xOffset;
			_viewport.yOffset = viewport.yOffset;
			return _viewport;
		}

		VkPresentModeKHR VulkanUtilities::getPresentMode(RSwapChainPresentMode ePresentMode)
		{
			switch (ePresentMode)
			{
			case Dynamik::RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_IMMEDIATE:					return VK_PRESENT_MODE_IMMEDIATE_KHR;
			case Dynamik::RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_FIFO:						return VK_PRESENT_MODE_FIFO_KHR;
			case Dynamik::RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_MAILBOX:					return VK_PRESENT_MODE_MAILBOX_KHR;
			case Dynamik::RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_SHADER_DEMAND_REFRESH:		return VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR;
			case Dynamik::RSwapChainPresentMode::SWAPCHAIN_PRESENT_MODE_SHADER_CONTINUOUS_REFRESH:	return VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR;
			default:
				DMK_ERROR_BOX("Unsupported swapchain present mode!");
				break;
			}

			return VK_PRESENT_MODE_FIFO_KHR;
		}

		VkFormat VulkanUtilities::getVulkanFormat(DMKFormat format)
		{
			return (VkFormat)(UI32)format;
		}

		VkImageLayout VulkanUtilities::getVulkanLayout(RImageLayout layout)
		{
			switch (layout)
			{
			case Dynamik::RImageLayout::IMAGE_LAYOUT_UNDEFINED:							return VK_IMAGE_LAYOUT_UNDEFINED;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_GENERAL:							return VK_IMAGE_LAYOUT_GENERAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_COLOR_ATTACHMENT:					return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT:			return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_STECIL_READ_ONLY:				return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_SHADER_READ_ONLY:					return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_TRANSFER_SRC:						return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_TRANSFER_DST:						return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_PREINITIALIZED:						return VK_IMAGE_LAYOUT_PREINITIALIZED;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT: return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY: return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_ATTACHMENT:			return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_DEPTH_READ_ONLY:			return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_STENCIL_ATTACHMENT:			return VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_STENCIL_READ_ONLY:			return VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_PRESENT_SRC:						return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_SHARED_PRESENT:						return VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_SHADING_RATE:						return VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV;
			case Dynamik::RImageLayout::IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP:				return VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT;
			default:
				DMK_ERROR_BOX("Invalid image layout!");
				break;
			}

			return VK_IMAGE_LAYOUT_UNDEFINED;
		}

		UI32 VulkanUtilities::findMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice)
		{
			VkPhysicalDeviceMemoryProperties memProperties = {};
			vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

			for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
				if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
					return i;

			DMK_ERROR_BOX("Failed to find suitable memory type!");
			return 0;
		}

		B1 VulkanUtilities::hasStencilComponent(const VkFormat& format)
		{
			return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
		}

		VkFormat VulkanUtilities::findSupportedFormat(const ARRAY<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice)
		{
			for (VkFormat format : candidates) {
				VkFormatProperties props;

				vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

				if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
					return format;

				else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
					return format;
			}

			DMK_ERROR_BOX("Failed to find supported format!");
			return VkFormat();
		}

		VkFormat VulkanUtilities::findDepthFormat(const VkPhysicalDevice& physicalDevice)
		{
			return findSupportedFormat(
				{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
				VK_IMAGE_TILING_OPTIMAL,
				VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
				physicalDevice
			);
		}

		VkComponentMapping VulkanUtilities::getComponentMapping(DMKTexture::TextureSwizzles swizzles)
		{
			VkComponentMapping _mapping;
			_mapping.r = (VkComponentSwizzle)swizzles.componentOne;
			_mapping.g = (VkComponentSwizzle)swizzles.componentTwo;
			_mapping.b = (VkComponentSwizzle)swizzles.componentThree;
			_mapping.a = (VkComponentSwizzle)swizzles.componentFour;

			return _mapping;
		}

		void VulkanUtilities::rawTransitionImageLayout(
			VkCommandBuffer commandBuffer,
			VkImage image,
			VkImageLayout oldLayout, VkImageLayout newLayout,
			UI32 mipLevels, UI32 layerCount, DMKFormat format)
		{
			VkImageMemoryBarrier barrier = {};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.oldLayout = oldLayout;
			barrier.newLayout = newLayout;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.image = image;

			if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
			{
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

				if (VulkanUtilities::hasStencilComponent(VulkanUtilities::getVulkanFormat(format)))
					barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}
			else
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

			barrier.subresourceRange.baseMipLevel = 0;
			barrier.subresourceRange.levelCount = mipLevels;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = layerCount;
			barrier.srcAccessMask = 0; // TODO
			barrier.dstAccessMask = 0; // TODO

			VkPipelineStageFlags sourceStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
			VkPipelineStageFlags destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

			switch (barrier.oldLayout)
			{
			case VK_IMAGE_LAYOUT_UNDEFINED:
				//sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				barrier.srcAccessMask = 0;
				break;

			case VK_IMAGE_LAYOUT_PREINITIALIZED:
				barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				//sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
				break;
			default:
				DMK_ERROR_BOX("Unsupported layout transition!");
				break;
			}

			switch (barrier.newLayout)
			{
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				//destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
				barrier.dstAccessMask = barrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				if (barrier.srcAccessMask == 0)
					barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;

				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				break;

			case VK_IMAGE_LAYOUT_GENERAL:
				//destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
				break;
			default:
				DMK_ERROR_BOX("Unsupported layout transition!");
				break;
			}

			vkCmdPipelineBarrier(
				commandBuffer,
				sourceStage, destinationStage,
				0,
				0, nullptr,
				0, nullptr,
				1, &barrier
			);
		}

		VkDescriptorType VulkanUtilities::getDescriptorType(DMKUniformType type)
		{
			switch (type)
			{
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER:			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER:			return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER_DYNAMIC:	return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER_DYNAMIC:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_TEXEL_BUFFER:	return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_TEXEL_BUFFER:	return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_INPUT_ATTACHMENT:		return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_IMAGE:			return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D:				return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE:			return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D_ARRAY:		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE_ARRAY:		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_ACCELERATION_STRUCTURE:	return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
			default:
				DMK_ERROR_BOX("Invalid uniform type!");
				break;
			}

			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		}

		VkShaderStageFlagBits VulkanUtilities::getShaderStage(DMKShaderLocation location)
		{
			switch (location)
			{
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX:		return VK_SHADER_STAGE_VERTEX_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TESSELLATION:	return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_GEOMETRY:		return VK_SHADER_STAGE_GEOMETRY_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT:		return VK_SHADER_STAGE_FRAGMENT_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_COMPUTE:		return VK_SHADER_STAGE_COMPUTE_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ALL_GRAPHICS:	return VK_SHADER_STAGE_ALL;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_RAY_GEN:		return VK_SHADER_STAGE_RAYGEN_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ANY_HIT:		return VK_SHADER_STAGE_ANY_HIT_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CLOSEST_HIT:	return VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MISS:			return VK_SHADER_STAGE_MISS_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_INTERSECTION:	return VK_SHADER_STAGE_INTERSECTION_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CALLABLE:		return VK_SHADER_STAGE_CALLABLE_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TASK:			return VK_SHADER_STAGE_TASK_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MESH:			return VK_SHADER_STAGE_MESH_BIT_NV;
			default:
				DMK_ERROR_BOX("Invalid shader location!");
				break;
			}

			return VK_SHADER_STAGE_ALL;
		}

		DMKShaderLocation VulkanUtilities::getShaderLocation(VkShaderStageFlagBits flag)
		{
			switch (flag)
			{
			case VK_SHADER_STAGE_VERTEX_BIT:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
			case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:		return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TESSELLATION;
			case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:	return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TESSELLATION;
			case VK_SHADER_STAGE_GEOMETRY_BIT:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_GEOMETRY;
			case VK_SHADER_STAGE_FRAGMENT_BIT:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT;
			case VK_SHADER_STAGE_COMPUTE_BIT:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_COMPUTE;
			case VK_SHADER_STAGE_ALL_GRAPHICS:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ALL_GRAPHICS;
			case VK_SHADER_STAGE_ALL:							return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
			case VK_SHADER_STAGE_RAYGEN_BIT_KHR:				return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_RAY_GEN;
			case VK_SHADER_STAGE_ANY_HIT_BIT_KHR:				return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ANY_HIT;
			case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:			return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CLOSEST_HIT;
			case VK_SHADER_STAGE_MISS_BIT_KHR:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MISS;
			case VK_SHADER_STAGE_INTERSECTION_BIT_KHR:			return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_INTERSECTION;
			case VK_SHADER_STAGE_CALLABLE_BIT_KHR:				return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CALLABLE;
			case VK_SHADER_STAGE_TASK_BIT_NV:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TASK;
			case VK_SHADER_STAGE_MESH_BIT_NV:					return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MESH;
			default:
				DMK_ERROR("Invalid Vulkan Shader Stage!");
				break;
			}

			return ::Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ALL;
		}

		ARRAY<VkVertexInputAttributeDescription> VulkanUtilities::getVertexAttributeDescriptions(DMKVertexLayout descriptor)
		{
			ARRAY<VkVertexInputAttributeDescription> attributeDescriptions;
			UI64 _previousTypeSize = 0;

			for (UI32 _index = 0; _index < descriptor.attributes.size(); _index++)
			{
				VkVertexInputAttributeDescription _description = {};
				_description.binding = 0;
				_description.location = _index;
				_description.format = getVulkanFormat(descriptor.attributes[_index].dataFormat);
				_description.offset = Cast<UI32>(_previousTypeSize);
				attributeDescriptions.pushBack(_description);

				_previousTypeSize += FormatSize(descriptor.attributes[_index].dataFormat);
			}

			return attributeDescriptions;
		}

		ARRAY<VkVertexInputAttributeDescription> VulkanUtilities::getVertexAttributeDescriptions(DMKShaderModule shaderModule)
		{
			if (shaderModule.location != DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
				DMK_WARN("The submitted shader module is not bound as a Vertex Shader!");

			ARRAY<VkVertexInputAttributeDescription> attributeDescriptions;

			VkVertexInputAttributeDescription _description = {};
			_description.binding = 0;
			_description.location = 0;
			_description.offset = 0;

			for (auto attribute : shaderModule.getAttributes())
			{
				_description.format = getVulkanFormat(attribute.dataFormat);
				attributeDescriptions.pushBack(_description);

				_description.offset += Cast<UI32>(FormatSize(attribute.dataFormat) * attribute.dataCount);
				_description.location++;
			}

			return attributeDescriptions;
		}

		ARRAY<VkVertexInputBindingDescription> VulkanUtilities::getVertexBindingDescriptions(DMKShaderModule shaderModule)
		{
			if (shaderModule.location != DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX)
				DMK_WARN("The submitted shader module is not bound as a Vertex Shader!");

			ARRAY<VkVertexInputBindingDescription> descriptions;

			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			UI64 stride = 0;
			for (auto attribute : shaderModule.getAttributes())
				stride += FormatSize(attribute.dataFormat);

			if (stride)
			{
				bindingDescription.stride = Cast<UI32>(stride);
				descriptions.pushBack(bindingDescription);
			}
			return descriptions;
		}

		VkFormat VulkanUtilities::vertexAttributeTypeToVkFormat(DMKDataType type)
		{
			switch ((UI32)type)
			{
			case (sizeof(F32) * 1): return VkFormat::VK_FORMAT_R32_SFLOAT;
			case (sizeof(F32) * 2): return VkFormat::VK_FORMAT_R32G32_SFLOAT;
			case (sizeof(F32) * 3): return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
			case (sizeof(F32) * 4): return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
			case (sizeof(F32) * 9): return VkFormat::VK_FORMAT_R32_SFLOAT;
			case (sizeof(F32) * 16): return VkFormat::VK_FORMAT_R32_SFLOAT;
			}

			return VkFormat::VK_FORMAT_UNDEFINED;
		}

		void VulkanUtilities::copyDataToImage(RCoreObject* pCoreObject, RImage* pImage, VPTR data, UI64 byteSize, UI64 dstOffset, UI64 srcOffset)
		{
			VulkanBuffer staggingBuffer;
			staggingBuffer.initialize(pCoreObject, RBufferType::BUFFER_TYPE_STAGGING, byteSize);
			staggingBuffer.setData(pCoreObject, byteSize, srcOffset, data);

			pImage->setLayout(pCoreObject, RImageLayout::IMAGE_LAYOUT_TRANSFER_DST);
			pImage->copyBuffer(pCoreObject, &staggingBuffer);

			staggingBuffer.terminate(pCoreObject);
		}

		VkShaderModule VulkanUtilities::createShaderModule(const RCoreObject* pCoreObject, const DMKShaderModule& shaderModule)
		{
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.codeSize = shaderModule.shaderCode.size();
			createInfo.pCode = shaderModule.shaderCode.data();

			VkShaderModule vModule = VK_NULL_HANDLE;
			DMK_VULKAN_ASSERT(vkCreateShaderModule(InheritCast<VulkanCoreObject>(pCoreObject).device, &createInfo, nullptr, &vModule), "Failed to create shader module!");

			return vModule;
		}

		VkPolygonMode VulkanUtilities::getPolygonMode(const RPolygonMode& ePolygonMode)
		{
			switch (ePolygonMode)
			{
			case Dynamik::RPolygonMode::POLYGON_MODE_FILL:
				return VK_POLYGON_MODE_FILL;
			case Dynamik::RPolygonMode::POLYGON_MODE_LINE:
				return VK_POLYGON_MODE_LINE;
			case Dynamik::RPolygonMode::POLYGON_MODE_POINT:
				return VK_POLYGON_MODE_POINT;
			case Dynamik::RPolygonMode::POLYGON_MODE_FILL_RECTANGLE:
				return VK_POLYGON_MODE_FILL_RECTANGLE_NV;
			default:
				DMK_ERROR_BOX("Invalid polygon mode!");
				break;
			}

			return VkPolygonMode();
		}

		VkStencilOpState VulkanUtilities::getStencilOpState(const RStencilOpState& opState)
		{
			VkStencilOpState state;
			state.compareMask = opState.compareMask;
			state.compareOp = (VkCompareOp)opState.compareOp;
			state.depthFailOp = (VkStencilOp)opState.depthFailOp;
			state.failOp = (VkStencilOp)opState.failOp;
			state.passOp = (VkStencilOp)opState.passOp;
			state.reference = opState.reference;
			state.writeMask = opState.writeMask;

			return state;
		}

		ARRAY<VkPipelineColorBlendAttachmentState> VulkanUtilities::getBlendStates(const ARRAY<RColorBlendState>& blendStates)
		{
			ARRAY<VkPipelineColorBlendAttachmentState> states;
			VkPipelineColorBlendAttachmentState attachmentState;
			for (auto state : blendStates)
			{
				attachmentState.alphaBlendOp = (VkBlendOp)state.alphaBlendOp;
				attachmentState.blendEnable = state.enable;
				attachmentState.colorBlendOp = (VkBlendOp)state.colorBlendOp;
				attachmentState.colorWriteMask = VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT;
				//attachmentState.colorWriteMask = (VkColorComponentFlags)state.colorWriteMask;
				attachmentState.srcAlphaBlendFactor = (VkBlendFactor)state.srcAlphaBlendFactor;
				attachmentState.dstAlphaBlendFactor = (VkBlendFactor)state.dstAlphaBlendFactor;
				attachmentState.srcColorBlendFactor = (VkBlendFactor)state.srcAlphaBlendFactor;
				attachmentState.dstColorBlendFactor = (VkBlendFactor)state.dstAlphaBlendFactor;
				states.pushBack(attachmentState);
			}

			return states;
		}

		ARRAY<VkDynamicState> VulkanUtilities::getDynamicStates(const ARRAY<RDynamicState>& states)
		{
			ARRAY<VkDynamicState> vStates;
			for (auto state : states)
			{
				vStates.pushBack((VkDynamicState)state);
			}

			return vStates;
		}
	}
}