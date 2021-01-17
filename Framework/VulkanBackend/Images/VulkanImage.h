// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/Image.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanImage : public GraphicsCore::Image {
		public:
			VulkanImage() {}
			virtual ~VulkanImage() {}

		protected:
			VkImage vImage = VK_NULL_HANDLE;
			VkImageView vImageView = VK_NULL_HANDLE;
			VkSampler vSampler = VK_NULL_HANDLE;

			VkDeviceMemory vImageMemory = VK_NULL_HANDLE;

			VkImageLayout vCurrentLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		};
	}
}