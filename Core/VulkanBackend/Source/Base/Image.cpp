// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Base/Image.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void Image::Initialize(const VulkanDevice& vDevice, VkImageType vImageType, VkFormat vFormat, VkExtent3D vExtent, VkImageUsageFlags vUsage)
		{
			VkImageCreateInfo createInfo = {};
		}

		void Image::Terminate(const VulkanDevice& vDevice)
		{
		}
	}
}
