// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_IMAGE_H
#define _DYNAMIK_VULKAN_IMAGE_H

/*
 Author:    Dhiraj Wishal
 Date:      25/05/2020
*/
#include "Object/Resource/Texture.h"
#include "../Common/VulkanDevice.h"
#include "../Common/VulkanQueue.h"
#include "VulkanBuffer.h"
#include "Renderer/Components/PrimitiveTypeDefs.h"
#include "Renderer/Components/CoreTypeDefs.h"

namespace Dynamik
{
	namespace Backend
	{
		struct DMK_API VulkanImageCreateInfo {
			UI32 imageWidth = 0;
			UI32 imageHeight = 0;
			UI32 imageDepth = 1;
			DMKTextureType imageType = DMKTextureType::DMK_TEXTURE_TYPE_2D;
			ImageUsage imageUsage = ImageUsage::IMAGE_USAGE_RENDER;
			UI32 layers = 1;
			UI32 mipLevels = 1;
			DMKFormat imageFormat = DMKFormat::DMK_FORMAT_UNDEFINED;
			ResourceMemoryType memoryType = ResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_ACCESSABLE;
			DMKSampleCount sampleCount = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
		};

		/*
		 Vulkan Image object for the Dynamik Engine
		*/
		class DMK_API VulkanImage {
		public:
			VulkanImage() {}
			~VulkanImage() {}

			void initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VulkanImageCreateInfo info);
			void copyBuffer(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const VulkanBuffer& vBuffer);
			void generateMipMaps(const VulkanDevice& vDevice, const VulkanQueue& vQueue);
			void setLayout(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VkImageLayout newLayout);
			void terminate(const VulkanDevice& vDevice);

			VPTR mapMemory(const VulkanDevice& vDevice, UI32 offset = 0);
			void unmapMemory(const VulkanDevice& vDevice);

			operator VkImage() const;
			operator VkDeviceMemory() const;

			VkImage image = VK_NULL_HANDLE;
			VkDeviceMemory imageMemory = VK_NULL_HANDLE;
			VkFormat format = VK_FORMAT_UNDEFINED;
			VkImageLayout currentLayout = VK_IMAGE_LAYOUT_UNDEFINED;

			DMKTextureType type = DMKTextureType::DMK_TEXTURE_TYPE_2D;
			ImageUsage usage = ImageUsage::IMAGE_USAGE_RENDER;

			UI32 width = 0;
			UI32 height = 0;
			UI32 depth = 1;
			UI32 size = 0;
			UI32 availabeMipLevels = 0;
			UI32 mipLevel = 0;
			UI32 layers = 0;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_IMAGE_H
