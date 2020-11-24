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
			 * Choose a swap chain surface format.
			 *
			 * @param availableFormats: All the available surface formats.
			 * @return VkSurfaceFormatKHR structure.
			 */
			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

			/**
			 * Choose swap chain present mode.
			 * This describes how the swap chain images should be presented to the screen buffer.
			 *
			 * @param availablePresentModes: All the available present modes.
			 * @return VkPresentModeKHR enum.
			 */
			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

			/**
			 * Choose a swap chain extent.
			 * This defines the width and height of every swap chain image.
			 *
			 * @param capabilities: The surface capabilities.
			 * @param width: The prefered width of the image.
			 * @param height: The prefered height of the image.
			 * @return VkExtent2D structure.
			 */
			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, UI32 width, UI32 height);

			/**
			 * Create image views for the swap chain images.
			 *
			 * @param vImages: The swap chain images.
			 * @param vDevice: The Vulkan logical device.
			 * @return Vector of image views.
			 */
			std::vector<VkImageView> CreateImageViews(const std::vector<VkImage>& vImages, VkFormat imageFormat, VkDevice vDevice);

			/**
			 * Create image memory for the Color Buffer.
			 * This creates one image memory block to fit all of the images.
			 *
			 * @param vImages: The images to be binded.
			 * @param vPhysicalDevice: The physical device in which the memory is allocated to.
			 * @param vLogicalDevice: The logical device to bind the memory to.
			 * @return The Vulkan Device Memory handle.
			 */
			VkDeviceMemory CreateImageMemory(const std::vector<VkImage>& vImages, VkPhysicalDevice vPhysicalDevice, VkDevice vLogicalDevice);

			/**
			 * Find a supported image format in a list of candidate formats.
			 *
			 * @param vCandidateFormats: The candidate image formats.
			 * @param vImageTiling: The image tiling.
			 * @param vFeatures: The forat features.s
			 * @param vPhysicalDevice: The physical device which the image is bound to.
			 * @return The selected format.
			 */
			VkFormat FindSupportedFormat(const std::vector<VkFormat>& vCandidateFormats, VkImageTiling vImageTiling, VkFormatFeatureFlags vFeatures, VkPhysicalDevice vPhysicalDevice);

			/**
			 * Find the depth format supported by the physical device.
			 *
			 * @param vPhysicalDevice: The physical device to be bound to.
			 * @return The selected format.
			 */
			VkFormat FindDepthFormat(const VkPhysicalDevice& vPhysicalDevice);
		}
	}
}