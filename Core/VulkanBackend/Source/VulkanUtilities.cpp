// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanUtilities.h"
#include "VulkanBackend/Macros.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace Utilities
		{

			UI32 FindMemoryTypeBits(VkPhysicalDevice physicalDevice, VkMemoryPropertyFlags properties, UI32 typeFilter)
			{
				VkPhysicalDeviceMemoryProperties memProperties = {};
				vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

				for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
					if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
						return i;
				DMK_LOG_ERROR(TEXT("Failed to find suitable memory type!"));
				return 0;
			}

			VkImage CreateImage(VkDevice vLogicalDevice, VkSampleCountFlags sampleCount, VkImageUsageFlags usage, GraphicsCore::ImageExtent extent, GraphicsCore::ImageType type, VkFormat format, UI32 layers, UI32 mipLevels)
			{
				VkImageCreateInfo vCI = {};
				vCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				vCI.pNext = VK_NULL_HANDLE;
				vCI.flags = 0;
				vCI.usage = usage;
				vCI.queueFamilyIndexCount = 0;
				vCI.pQueueFamilyIndices = VK_NULL_HANDLE;
				vCI.extent = { extent.mWidth, extent.mHeight, extent.mDepth };
				vCI.format = format;
				vCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

				switch (type)
				{
				case DMK::GraphicsCore::ImageType::STORAGE_2D:
					vCI.imageType = VK_IMAGE_TYPE_2D;
					break;
				case DMK::GraphicsCore::ImageType::STORAGE_3D:
					vCI.imageType = VK_IMAGE_TYPE_3D;
					break;
				case DMK::GraphicsCore::ImageType::RENDER_2D:
					vCI.imageType = VK_IMAGE_TYPE_2D;
					break;
				case DMK::GraphicsCore::ImageType::RENDER_3D:
					vCI.imageType = VK_IMAGE_TYPE_3D;
					break;
				case DMK::GraphicsCore::ImageType::CUBE_MAP:
					vCI.imageType = VK_IMAGE_TYPE_2D;
					vCI.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
					break;
				default:
					DMK_LOG_ERROR(TEXT("Invalid or undefined image type!"));
					break;
				}

				vCI.arrayLayers = layers;
				vCI.mipLevels = mipLevels;
				vCI.samples = static_cast<VkSampleCountFlagBits>(sampleCount);
				vCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

				VkImage vImage = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkCreateImage(vLogicalDevice, &vCI, nullptr, &vImage), "Failed to create Vulkan Image!");

				return vImage;
			}

			VkDeviceMemory CreateImageMemory(VkDevice vLogicalDevice, VkPhysicalDevice vPhysicalDevice, VkImage vImage)
			{
				VkMemoryRequirements vMemReq = {};
				vkGetImageMemoryRequirements(vLogicalDevice, vImage, &vMemReq);

				VkMemoryAllocateInfo vAI = {};
				vAI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				vAI.allocationSize = vMemReq.size;
				vAI.memoryTypeIndex = FindMemoryTypeBits(vPhysicalDevice, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vMemReq.memoryTypeBits);

				VkDeviceMemory vMemory = VK_NULL_HANDLE;
				DMK_VK_ASSERT(vkAllocateMemory(vLogicalDevice, &vAI, nullptr, &vMemory), "Failed to allocate GPU memory! (Image)");

				return vMemory;
			}
		}
	}
}