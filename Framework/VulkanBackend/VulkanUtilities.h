// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/Image.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		namespace Utilities
		{
			UI32 FindMemoryTypeBits(VkPhysicalDevice physicalDevice, VkMemoryPropertyFlags properties, UI32 typeFilter);

			VkImage CreateImage(VkDevice vLogicalDevice, VkSampleCountFlags sampleCount, VkImageUsageFlags usage, GraphicsCore::ImageExtent extent, GraphicsCore::ImageType type, VkFormat format, UI32 layers, UI32 mipLevels);
			VkDeviceMemory CreateImageMemory(VkDevice vLogicalDevice, VkPhysicalDevice vPhysicalDevice, VkImage vImage);
		}
	}
}