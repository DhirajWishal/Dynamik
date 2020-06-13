// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanImage.h"

#include "../Common/VulkanUtilities.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanImage::initialize(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VulkanImageCreateInfo info)
		{
			type = info.imageType;
			usage = info.imageUsage;
			mipLevel = info.mipLevels;
			layers = info.layers;
			size = info.imageWidth * info.imageHeight * info.imageDepth * 4;
			width = info.imageWidth;
			height = info.imageHeight;
			depth = info.imageDepth;
			availabeMipLevels = info.mipLevels;
			format = VulkanUtilities::getVulkanFormat(info.imageFormat);

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
			imageInfo.samples = (VkSampleCountFlagBits)info.sampleCount;
			imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;

			if (info.imageType == DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP || info.imageType == DMKTextureType::DMK_TEXTURE_TYPE_CUBEMAP_ARRAY)
				imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

			DMK_VULKAN_ASSERT(vkCreateImage(vDevice, &imageInfo, nullptr, &image), "Failed to create image!");

			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(vDevice, image, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits,
				(VkMemoryPropertyFlagBits)info.memoryType, vDevice);

			DMK_VULKAN_ASSERT(vkAllocateMemory(vDevice, &allocInfo, nullptr, &imageMemory), "Failed to allocate image memory!");
			DMK_VULKAN_ASSERT(vkBindImageMemory(vDevice, image, imageMemory, 0), "Failed to bind image memory!");
		}

		void VulkanImage::copyBuffer(const VulkanDevice& vDevice, const VulkanQueue& vQueue, const VulkanBuffer& vBuffer)
		{
			setLayout(vDevice, vQueue, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

			VkBufferImageCopy region = {};
			region.bufferOffset = 0;
			region.bufferRowLength = 0;
			region.bufferImageHeight = 0;

			region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			region.imageSubresource.mipLevel = 0;
			region.imageSubresource.baseArrayLayer = 0;
			region.imageSubresource.layerCount = layers;

			region.imageOffset = { 0, 0, 0 };
			region.imageExtent = {
				width,
				height,
				depth
			};

			VulkanOneTimeCommandBuffer _commandBuffer(vDevice, vQueue);
			vkCmdCopyBufferToImage(
				_commandBuffer,
				vBuffer,
				image,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1,
				&region
			);
		}

		void VulkanImage::generateMipMaps(const VulkanDevice& vDevice, const VulkanQueue& vQueue)
		{
			VulkanOneTimeCommandBuffer _buffer(vDevice, vQueue);
			VkFormatProperties formatProperties;
			vkGetPhysicalDeviceFormatProperties(vDevice, format, &formatProperties);

			if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
				DMK_ERROR_BOX("Texture image format does not support linear blitting!");

			VkImageMemoryBarrier barrier = {};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.image = image;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = 1;
			barrier.subresourceRange.levelCount = 1;

			for (UI32 i = 1; i < availabeMipLevels; i++) {
				barrier.subresourceRange.baseMipLevel = i - 1;
				barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

				vkCmdPipelineBarrier(_buffer,
					VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
					0, nullptr,
					0, nullptr,
					1, &barrier);

				VkImageBlit blit = {};
				blit.srcOffsets[0] = { 0, 0, 0 };
				blit.srcOffsets[1] = { (I32)width, (I32)height, 1 };
				blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.srcSubresource.mipLevel = i - 1;
				blit.srcSubresource.baseArrayLayer = 0;
				blit.srcSubresource.layerCount = 1;
				blit.dstOffsets[0] = { 0, 0, 0 };
				blit.dstOffsets[1] = { (I32)width > 1 ? (I32)width / 2 : 1, (I32)height > 1 ? (I32)height / 2 : 1, 1 };
				blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.dstSubresource.mipLevel = i;
				blit.dstSubresource.baseArrayLayer = 0;
				blit.dstSubresource.layerCount = 1;

				vkCmdBlitImage(_buffer,
					image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					1, &blit,
					VK_FILTER_LINEAR);

				barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

				vkCmdPipelineBarrier(_buffer,
					VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
					0, nullptr,
					0, nullptr,
					1, &barrier);

				if (width > 1) width /= 2;
				if (height > 1) height /= 2;
			}
		}

		void VulkanImage::setLayout(const VulkanDevice& vDevice, const VulkanQueue& vQueue, VkImageLayout newLayout)
		{
			VulkanOneTimeCommandBuffer oneTimeCommandBuffer(vDevice, vQueue);

			VkImageMemoryBarrier barrier = {};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.oldLayout = currentLayout;
			barrier.newLayout = newLayout;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.image = image;

			if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
			{
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

				if (VulkanUtilities::hasStencilComponent(format))
					barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}
			else
				barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

			barrier.subresourceRange.baseMipLevel = 0;
			barrier.subresourceRange.levelCount = availabeMipLevels;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = layers;
			barrier.srcAccessMask = 0; // TODO
			barrier.dstAccessMask = 0; // TODO

			VkPipelineStageFlags sourceStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
			VkPipelineStageFlags destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

			switch (currentLayout)
			{
			case VK_IMAGE_LAYOUT_UNDEFINED:
				sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				barrier.srcAccessMask = 0;
				break;

			case VK_IMAGE_LAYOUT_PREINITIALIZED:
				barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
				break;
			default:
				DMK_ERROR_BOX("Unsupported layout transition!");
				break;
			}

			switch (newLayout)
			{
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
				destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				break;

			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
				destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
				destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
				barrier.dstAccessMask = barrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				break;

			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
				if (barrier.srcAccessMask == 0)
					barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;

				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				break;

			case VK_IMAGE_LAYOUT_GENERAL:
				destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
				break;
			default:
				DMK_ERROR_BOX("Unsupported layout transition!");
				break;
			}

			vkCmdPipelineBarrier(
				oneTimeCommandBuffer,
				sourceStage, destinationStage,
				0,
				0, nullptr,
				0, nullptr,
				1, &barrier
			);
		}

		void VulkanImage::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyImage(vDevice, image, nullptr);
			vkFreeMemory(vDevice, imageMemory, nullptr);
		}

		VPTR VulkanImage::mapMemory(const VulkanDevice& vDevice, UI32 offset)
		{
			VPTR data = nullptr;
			DMK_VULKAN_ASSERT(vkMapMemory(vDevice, imageMemory, offset, size, 0, &data), "Unable to map image memory!");
			return data;
		}

		void VulkanImage::unmapMemory(const VulkanDevice& vDevice)
		{
			vkUnmapMemory(vDevice, imageMemory);
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