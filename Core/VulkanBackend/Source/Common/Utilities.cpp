// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace Utilities
		{
			UI32 FindMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice vPhyscialDevice)
			{
				VkPhysicalDeviceMemoryProperties memProperties = {};
				vkGetPhysicalDeviceMemoryProperties(vPhyscialDevice, &memProperties);

				for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
					if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
						return i;

				Logger::LogError(TEXT("Failed to find suitable memory type!"));
				return 0;
			}

			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
			{
				for (const auto& availableFormat : availableFormats)
					if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM
						&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
						return availableFormat;

				return availableFormats[0];
			}

			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
			{
				VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

				for (const auto& availablePresentMode : availablePresentModes)
				{
					if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
						return availablePresentMode;
					else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
						bestMode = availablePresentMode;
				}

				return bestMode;
			}

			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, UI32 width, UI32 height)
			{
				VkExtent2D actualExtent = {
					width,
					height
				};

				if ((width >= capabilities.maxImageExtent.width) || (width <= capabilities.minImageExtent.width))
					actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));

				if ((height >= capabilities.maxImageExtent.height) || (height <= capabilities.minImageExtent.height))
					actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

				return actualExtent;
			}

			std::vector<VkImageView> CreateImageViews(const std::vector<VkImage>& vImages, VkFormat imageFormat, VkDevice vDevice)
			{
				VkImageViewCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				createInfo.flags = VK_NULL_HANDLE;
				createInfo.pNext = VK_NULL_HANDLE;
				createInfo.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
				createInfo.format = imageFormat;

				VkImageSubresourceRange vSubRange = {};
				vSubRange.baseArrayLayer = 1;
				vSubRange.layerCount = 1;
				vSubRange.levelCount = 1;
				vSubRange.baseMipLevel = 0;

				createInfo.subresourceRange = vSubRange;

				std::vector<VkImageView> vImageViews(vImages.size());
				UI8 counter = 0;
				for (auto itr = vImages.begin(); itr != vImages.end(); itr++)
				{
					createInfo.image = *itr;
					DMK_VK_ASSERT(vkCreateImageView(vDevice, &createInfo, nullptr, vImageViews.data() + counter), "Failed to create Vulkan Image Views for the Swap Chain images!");
					counter++;
				}

				return vImageViews;
			}

			VkDeviceMemory CreateImageMemory(const std::vector<VkImage>& vImages, VkPhysicalDevice vPhysicalDevice, VkDevice vLogicalDevice)
			{
				// Get memory requirements.
				VkMemoryRequirements memRequirements = {};
				vkGetImageMemoryRequirements(vLogicalDevice, vImages[0], &memRequirements);

				// Memory allocate info.
				VkMemoryAllocateInfo allocInfo = {};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = memRequirements.size * vImages.size();
				allocInfo.memoryTypeIndex = Utilities::FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vPhysicalDevice);

				// Allocate the image memory
				VkDeviceMemory vImageMemory = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkAllocateMemory(vLogicalDevice, &allocInfo, nullptr, &vImageMemory), "Failed to allocate image memory!");

				// Bind the image to the image memory.
				UI32 counter = 0;
				while (counter < vImages.size())
				{
					DMK_VK_ASSERT(vkBindImageMemory(vLogicalDevice, *(vImages.data() + counter), vImageMemory, memRequirements.size * counter), "Failed to bind image memory!");
					counter++;
				}

				return vImageMemory;
			}

			VkFormat FindSupportedFormat(const std::vector<VkFormat>& vCandidateFormats, VkImageTiling vImageTiling, VkFormatFeatureFlags vFeatures, VkPhysicalDevice vPhysicalDevice)
			{
				// Go through the candidates and check if any suitable format is present.
				for (auto itr = vCandidateFormats.begin(); itr != vCandidateFormats.end(); itr++) {
					VkFormatProperties props;

					vkGetPhysicalDeviceFormatProperties(vPhysicalDevice, *itr, &props);

					if (vImageTiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & vFeatures) == vFeatures)
						return *itr;

					else if (vImageTiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & vFeatures) == vFeatures)
						return *itr;
				}

				// Assert and return VK_UNDEFINED.
				Logger::LogError(TEXT("Failed to find supported format!"));
				return VkFormat::VK_FORMAT_UNDEFINED;
			}

			VkFormat FindDepthFormat(const VkPhysicalDevice& vPhysicalDevice)
			{
				return FindSupportedFormat(
					{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
					VK_IMAGE_TILING_OPTIMAL,
					VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
					vPhysicalDevice
				);
			}
		}
	}
}