#include "dmkafx.h"
#include "VulkanImageView.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImageView::initialize(const VulkanDevice& vDevice, const VulkanImage& vImage, VkComponentMapping mapping)
		{
			VkImageViewCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = vImage;
			createInfo.format = vImage.format;
			createInfo.pNext = VK_NULL_HANDLE;

			switch (vImage.type)
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
			createInfo.subresourceRange.aspectMask = (vImage.usage == ImageUsage::IMAGE_USAGE_DEPTH_ATTACHMENT) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.layerCount = vImage.layers;
			createInfo.subresourceRange.levelCount = vImage.mipLevel;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.components = mapping;

			// { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A }

			DMK_VULKAN_ASSERT(vkCreateImageView(vDevice, &createInfo, nullptr, &imageView), "Failed to create texture image view!");
		}

		void VulkanImageView::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyImageView(vDevice, imageView, nullptr);
		}

		VulkanImageView::operator VkImageView() const
		{
			return this->imageView;
		}
	}
}