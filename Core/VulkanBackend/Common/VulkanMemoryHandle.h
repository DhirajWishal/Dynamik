// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H
#define _DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H

#include "GraphicsCore/Common/MemoryHandle.h"
#include "VulkanBackend/Primitives/VulkanObject.h"

#include "GraphicsCore/Common/Defines.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Memory Handle object for the Dynamik Engine.
			 */
			class DMK_API VulkanMemoryHandle :
				public MemoryHandle,
				public VulkanObject
			{
			public:
				/**
				 * Default constructor.
				 */
				VulkanMemoryHandle() {}

				/**
				 * Default destructor.
				 */
				~VulkanMemoryHandle() {}

				/**
				 * Map the graphics memory to the local address space.
				 *
				 * @param size: The number of bytes to be mapped.
				 * @param offset: The offset of the memory block.
				 */
				virtual void* MapToLocal(UI64 size, UI64 offset) override final;

				/**
				 * Unmap the mapped memory from the local address space.
				 */
				virtual void UnmapMemory() override final;

				/**
				 * Set the vulkan device memory object.
				 *
				 * @param vMemory: The device memory object.
				 */
				void SetDeviceMemory(const VkDeviceMemory& vMemory) { deviceMemory = vMemory; }

				/**
				 * Get the vulkan device memory object.
				 */
				VkDeviceMemory GetDeviceMemory() const { return deviceMemory; }

				/* Data */
			private:
				VkDeviceMemory deviceMemory = VK_NULL_HANDLE;

				/* Static Utilities */
			public:
				/**
				 * Static method to create the Vulkan Device Memory object.
				 *
				 * @param vLogicalDevice: The Vulkan logical device.
				 * @param vPhysicalDevice: The Vulkan physical device.
				 * @param size: The size of the allocation.
				 * @param propertyFlags: The Vulkan memory property flags.
				 * @param memoryPropertyBits: Vulkan memory property bits submitted by the physical device.
				 * @param alignment: The memory alignment. Default is 0.
				 */
				static VkDeviceMemory CreateDeviceMemory(VkPhysicalDevice vPhysicalDevice, VkDevice vLogicalDevice, UI64 size, VkMemoryPropertyFlags propertyFlags, UI32 memoryPropertyBits, UI64 alignment = 0);
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H
