#include "dmkafx.h"
#include "VulkanImage.h"

#include "../Common/VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImage::initialize(const VulkanDevice& vDevice, VulkanImageCreateInfo info)
		{
			VkImageCreateInfo imageInfo = {};
			imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageInfo.imageType = VK_IMAGE_TYPE_2D;
			imageInfo.extent.width = info.imageWidth;
			imageInfo.extent.height = info.imageHeight;
			imageInfo.extent.depth = info.imageDepth;
			imageInfo.mipLevels = info.mipLevels;
			imageInfo.arrayLayers = info.layers;
			imageInfo.format = VulkanUtilities::getVulkanFormat(info.imageFormat);
			imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageInfo.usage = (VkImageUsageFlagBits)info.imageUsage;
			imageInfo.samples = info.numSamples;
			imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			if (info.imageType == VulkanImageType::VULKAN_IMAGE_TYPE_CUBEMAP)
				imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

			if (vkCreateImage(vDevice, &imageInfo, nullptr, &image) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to create image!");

			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(vDevice, image, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits,
				(VkMemoryPropertyFlagBits)info.memoryType, vDevice);

			if (vkAllocateMemory(vDevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
				DMK_ERROR_BOX("Failed to allocate image memory!");

			vkBindImageMemory(vDevice, image, imageMemory, 0);
		}

		void VulkanImage::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyImage(vDevice, image, nullptr);
			vkFreeMemory(vDevice, imageMemory, nullptr);
		}

		VulkanImage::operator VkImage() const
		{
			return this->image;
		}

		VulkanImage::operator VkDeviceMemory() const
		{
			return this->imageMemory;
		}
	}
}