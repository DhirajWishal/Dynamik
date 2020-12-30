// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "VulkanBackend/Common/VulkanDevice.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Image object.
		 * This object handles a single Vulkan Image handle.
		 */
		class Image {
		public:
			/**
			 * Default constructor.
			 */
			Image() {}

			/**
			 * Default destructor.
			 */
			~Image() {}

			/**
			 * Initialize the image.
			 */
			void Initialize(const VulkanDevice& vDevice, VkImageType vImageType, VkFormat vFormat, VkExtent3D vExtent, VkImageUsageFlags vUsage);

			/**
			 * Terminate the image.
			 */
			void Terminate(const VulkanDevice& vDevice);

			/**
			 * VkImage operator.
			 */
			operator VkImage() const { return vImage; }

			VkImage vImage = VK_NULL_HANDLE;	// Vulkan image handle.
		};
	}
}