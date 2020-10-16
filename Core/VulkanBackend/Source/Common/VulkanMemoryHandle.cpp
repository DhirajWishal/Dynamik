// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Common/VulkanMemoryHandle.h"
#include "VulkanBackend/Common/Assert.h"

#include "VulkanBackend/VulkanBackend.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			MemoryHandle* VulkanBackend::AllocateMemory(UI64 size, MemoryProperty memoryProperty)
			{
				// Allocate the memory handle object.
				VulkanMemoryHandle* pMemoryHandle = new VulkanMemoryHandle;

				// Set basic data.
				pMemoryHandle->SetDevice(GetLogicalDevice());
				pMemoryHandle->SetPhysicalDevice(GetPhysicalDevice());

				return pMemoryHandle->Inherit<MemoryHandle>();
			}

			void VulkanBackend::DeallocateMemory(MemoryHandle* pMemoryHandle)
			{
				// Free the allocated memory block.
				vkFreeMemory(GetLogicalDevice(), pMemoryHandle->Inherit<VulkanMemoryHandle>()->GetDeviceMemory(), nullptr);

				// Delete the allocated memory handle from the memory.
				delete pMemoryHandle->Inherit<VulkanMemoryHandle>();
			}

			void* VulkanMemoryHandle::MapToLocal(UI64 size, UI64 offset)
			{
				// Check if the size or the offset is valid. 
				if (!size || (offset > byteSize))
				{
					ErrorHandler::Logger::LogError(TEXT("Invalid size or offset to map device memory!"));
					return nullptr;
				}

				// Map the memory to the local address space. 
				void* pData = nullptr;
				DMK_VULKAN_ASSERT(vkMapMemory(GetDevice(), GetDeviceMemory(), offset, size, 0, &pData), "Failed to map device memory!");

				return pData;
			}

			void VulkanMemoryHandle::UnmapMemory()
			{
				// Unmap the mapped memory. 
				vkUnmapMemory(GetDevice(), GetDeviceMemory());
			}

			/**
			 * Get Vulkan Memory Property Flags from Memory Properties.
			 *
			 * @param properties: The Dynamik graphcis memory property flags.
			 */
			VkMemoryPropertyFlags GetVkMemoryPropertyFlags(MemoryProperty properties)
			{
				VkMemoryPropertyFlags flagBits = 0;

				if (Cast<UI32>(properties) & Cast<UI32>(DMK::GraphicsCore::MemoryProperty::MEMORY_PROPERTY_DEVICE_LOCAL))
					flagBits = flagBits | VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

				if (Cast<UI32>(properties) & Cast<UI32>(DMK::GraphicsCore::MemoryProperty::MEMORY_PROPERTY_HOST_VISIBLE))
					flagBits = flagBits | VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

				if (Cast<UI32>(properties) & Cast<UI32>(DMK::GraphicsCore::MemoryProperty::MEMORY_PROPERTY_HOST_COHERENT))
					flagBits = flagBits | VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

				if (Cast<UI32>(properties) & Cast<UI32>(DMK::GraphicsCore::MemoryProperty::MEMORY_PROPERTY_HOST_CACHED))
					flagBits = flagBits | VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_CACHED_BIT;

				if (Cast<UI32>(properties) & Cast<UI32>(DMK::GraphicsCore::MemoryProperty::MEMORY_PROPERTY_PROTECTED))
					flagBits = flagBits | VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_PROTECTED_BIT;

				return flagBits;
			}

			/**
			 * Get memory flag bits.
			 *
			 * @param vPhysicalDevice: The physical device.
			 * @param size: The size of the allocation.
			 * @param properties: The memory properties.
			 * @param flagBits: Property flag bits.
			 */
			UI32 GetMemoryFlagBits(VkPhysicalDevice vPhysicalDevice, UI64 size, VkMemoryPropertyFlags properties, UI32 flagBits)
			{
				// Get physical device memory properties. 
				VkPhysicalDeviceMemoryProperties memProperties = {};
				vkGetPhysicalDeviceMemoryProperties(vPhysicalDevice, &memProperties);

				// Check and get the required memory flag bits. 
				for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
					if ((flagBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
						return i;

				// Return if memory flag bits were not found.
				ErrorHandler::Logger::LogError(TEXT("Failed to find memory flag bits!"));
				return 0;
			}

			VkDeviceMemory VulkanMemoryHandle::CreateDeviceMemory(VkPhysicalDevice vPhysicalDevice, VkDevice vLogicalDevice, UI64 size, VkMemoryPropertyFlags propertyFlags, UI32 memoryPropertyBits, UI64 alignment)
			{
				// Memory allocation information structure. 
				VkMemoryAllocateInfo allocInfo = {};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = size;
				allocInfo.memoryTypeIndex = GetMemoryFlagBits(vPhysicalDevice, size, propertyFlags, memoryPropertyBits);

				// Allocate the memory.
				VkDeviceMemory vDeviceMemory = VK_NULL_HANDLE;
				DMK_VULKAN_ASSERT(vkAllocateMemory(vLogicalDevice, &allocInfo, nullptr, &vDeviceMemory), "Failed to allocate buffer memory!");
				
				return vDeviceMemory;
			}
		}
	}
}