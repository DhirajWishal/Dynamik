// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_VIEW_H
#define _DYNAMIK_VULKAN_IMAGE_VIEW_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020
*/
#include "VulkanImage.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Image View object for the Dynamik RBL
		*/
		class DMK_API VulkanImageView {
		public:
			VulkanImageView() {}
			~VulkanImageView() {}

			void initialize(const VulkanDevice& vDevice, const VulkanImage& vImage, VkComponentMapping mapping = {});
			void terminate(const VulkanDevice& vDevice);

			operator VkImageView() const;

			VkImageView imageView = VK_NULL_HANDLE;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IMAGE_VIEW_H
