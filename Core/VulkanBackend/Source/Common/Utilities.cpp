#include "VulkanBackend/Common/Utilities.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace Utilities
		{
			UI32 FindMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice vPhyscialDevice)
			{
				VkPhysicalDeviceMemoryProperties memProperties = {};
				vkGetPhysicalDeviceMemoryProperties(vPhyscialDevice, &memProperties);

				for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
					if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
						return i;

				Logger::LogError(TEXT("Failed to find suitable memory type!"));
				return 0;
			}

			void TransitionImageLayout(
				VkCommandBuffer vCommandBuffer,
				VkImage vImage,
				VkImageLayout oldLayout, VkImageLayout newLayout,
				UI32 mipLevels, UI32 layerCount, VkFormat vFormat)
			{
				VkImageMemoryBarrier barrier = {};
				barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				barrier.oldLayout = oldLayout;
				barrier.newLayout = newLayout;
				barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				barrier.image = vImage;

				if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
				{
					barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

					if (vFormat == VK_FORMAT_D32_SFLOAT_S8_UINT || vFormat == VK_FORMAT_D24_UNORM_S8_UINT)
						barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
				}
				else
					barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

				barrier.subresourceRange.baseMipLevel = 0;
				barrier.subresourceRange.levelCount = mipLevels;
				barrier.subresourceRange.baseArrayLayer = 0;
				barrier.subresourceRange.layerCount = layerCount;
				barrier.srcAccessMask = 0; // TODO
				barrier.dstAccessMask = 0; // TODO

				VkPipelineStageFlags sourceStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
				VkPipelineStageFlags destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

				switch (barrier.oldLayout)
				{
				case VK_IMAGE_LAYOUT_UNDEFINED:
					//sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
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
					//sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
					barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
					break;

				case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
					//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
					barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
					break;
				default:
					Logger::LogError(TEXT("Unsupported layout transition!"));
					break;
				}

				switch (barrier.newLayout)
				{
				case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
					//destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
					barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
					break;

				case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
					barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
					break;

				case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
					//destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
					break;

				case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
					//destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
					barrier.dstAccessMask = barrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
					break;

				case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
					if (barrier.srcAccessMask == 0)
						barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;

					barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
					//destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
					break;

				case VK_IMAGE_LAYOUT_GENERAL:
					//destinationStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
					break;
				default:
					Logger::LogError(TEXT("Unsupported layout transition!"));
					break;
				}

				vkCmdPipelineBarrier(
					vCommandBuffer,
					sourceStage, destinationStage,
					0,
					0, nullptr,
					0, nullptr,
					1, &barrier
				);
			}
		}
	}
}