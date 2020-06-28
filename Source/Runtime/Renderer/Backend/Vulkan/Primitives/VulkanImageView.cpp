// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanImageView.h"

#include "../VulkanCoreObject.h"
#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImageView::initialize(RCoreObject* pCoreObject, RImage* pImage, DMKTexture::TextureSwizzles swizzles)
		{
			VkImageViewCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = *Inherit<VulkanImage>(pImage);
			createInfo.format = VulkanUtilities::getVulkanFormat(InheritCast<VulkanImage>(pImage).format);
			createInfo.pNext = VK_NULL_HANDLE;

			switch (InheritCast<VulkanImage>(pImage).type)
			{
			case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_2D:
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				break;
			case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_2D_ARRAY:
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
				break;
			case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP:
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
				break;
			case Dynamik::DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP_ARRAY:
				createInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
				break;
			default:
				DMK_ERROR_BOX("Invalid image type!");
				break;
			}

			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.aspectMask = (InheritCast<VulkanImage>(pImage).usage == RImageUsage::IMAGE_USAGE_DEPTH_ATTACHMENT) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.layerCount = InheritCast<VulkanImage>(pImage).layers;
			createInfo.subresourceRange.levelCount = InheritCast<VulkanImage>(pImage).mipLevel;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.components = VulkanUtilities::getComponentMapping(swizzles);
			// { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A }

			DMK_VULKAN_ASSERT(vkCreateImageView(Inherit<VulkanCoreObject>(pCoreObject)->device, &createInfo, nullptr, &imageView), "Failed to create texture image view!");
		}

		void VulkanImageView::terminate(RCoreObject* pCoreObject)
		{
			vkDestroyImageView(Inherit<VulkanCoreObject>(pCoreObject)->device, imageView, nullptr);
		}

		VulkanImageView::operator VkImageView() const
		{
			return this->imageView;
		}
	}
}