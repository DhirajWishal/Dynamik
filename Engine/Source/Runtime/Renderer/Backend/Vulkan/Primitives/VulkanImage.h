#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_H
#define _DYNAMIK_VULKAN_IMAGE_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "../Common/VulkanDevice.h"

namespace Dynamik
{
	namespace Backend
	{
		/* Vulkan Image Type enum */
		enum class DMK_API VulkanImageType {
			VULKAN_IMAGE_TYPE_2D,
			VULKAN_IMAGE_TYPE_CUBEMAP,
		};

		/* OR operator can be used */
		enum class DMK_API VulkanImageUsage {
			VULKAN_IMAGE_USAGE_TRANSFER_SRC = BIT_SHIFT(1),
			VULKAN_IMAGE_USAGE_TRANSFER_DST = BIT_SHIFT(2),
			VULKAN_IMAGE_USAGE_RENDER = BIT_SHIFT(3),
			VULKAN_IMAGE_USAGE_STORAGE = BIT_SHIFT(4),
			VULKAN_IMAGE_USAGE_COLOR_ATTACHMENT = BIT_SHIFT(5),
			VULKAN_IMAGE_USAGE_DEPTH_ATTACHMENT = BIT_SHIFT(6),
			VULKAN_IMAGE_USAGE_TRANSIENT_ATTACHMENT = BIT_SHIFT(7),
			VULKAN_IMAGE_USAGE_INPUT_ATTACHMENT = BIT_SHIFT(8),
		};

		enum class DMK_API VulkanImageMemoryType {
			VULKAN_IMAGE_MEMORY_TYPE_HOST_ACCESSABLE = BIT_SHIFT(1),
			VULKAN_IMAGE_MEMORY_TYPE_HOST_VISIBLE = BIT_SHIFT(2),
			VULKAN_IMAGE_MEMORY_TYPE_HOST_COHERENT = BIT_SHIFT(3),
			VULKAN_IMAGE_MEMORY_TYPE_HOST_CACHED = BIT_SHIFT(4),
			VULKAN_IMAGE_MEMORY_TYPE_PROTECTED = BIT_SHIFT(6),
		};

		struct DMK_API VulkanImageCreateInfo {
			UI32 imageWidth = 0;
			UI32 imageHeight = 0;
			UI32 imageDepth = 1;
			VulkanImageType imageType = VulkanImageType::VULKAN_IMAGE_TYPE_2D;
			VulkanImageUsage imageUsage = VulkanImageUsage::VULKAN_IMAGE_USAGE_RENDER;
			UI32 layers = 1;
			UI32 mipLevels = 1;
			DMKFormat imageFormat = DMKFormat::DMK_FORMAT_UNDEFINED;
			VkSampleCountFlagBits numSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
			VulkanImageMemoryType memoryType = VulkanImageMemoryType::VULKAN_IMAGE_MEMORY_TYPE_HOST_ACCESSABLE;
		};

		/*
		 Vulkan Image object for the Dynamik Engine
		*/
		class DMK_API VulkanImage {
		public:
			VulkanImage() {}
			~VulkanImage() {}

			void initialize(const VulkanDevice& vDevice, VulkanImageCreateInfo info);
			void terminate(const VulkanDevice& vDevice);

			void generateMipMaps();

			operator VkImage() const;
			operator VkDeviceMemory() const;

			VkImage image = VK_NULL_HANDLE;
			VkDeviceMemory imageMemory = VK_NULL_HANDLE;
			VkFormat imageFormat = VK_FORMAT_UNDEFINED;
			VkImageLayout currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IMAGE_H
