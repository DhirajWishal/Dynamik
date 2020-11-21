// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace Utilities
		{
			/**
			 * Find the suitable memory type.
			 *
			 * @param typeFilter: The memory type filter.
			 * @param properties: The memory property flags.
			 * @param vPhyscialDevice: The Vulkan Physical Device handle.
			 * @return The memory type.
			 */
			UI32 FindMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice vPhyscialDevice);

			/**
			 * Set a new layout to a given image.
			 *
			 * @param vCommandBuffer: The command buffer to which the command is passed to.
			 * @param vImage: The image to which switch the layout.
			 * @param oldLayout: The previous layout of the image.
			 * @param newLayout: The new layout of the image (the layout to be set to).
			 * @param mipLevels: The number of mip levels in the image.
			 * @param layerCount: The number of layers in the image.
			 * @param vFormat: The format of the image.
			 */
			void TransitionImageLayout(VkCommandBuffer vCommandBuffer, VkImage vImage, VkImageLayout oldLayout, VkImageLayout newLayout, UI32 mipLevels, UI32 layerCount, VkFormat vFormat);
		}
	}
}