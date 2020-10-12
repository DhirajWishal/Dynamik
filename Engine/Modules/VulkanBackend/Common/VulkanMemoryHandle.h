// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H
#define _DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H

#include "GraphicsCore/Common/MemoryHandle.h"
#include "VulkanBackend/Primitives/VulkanObject.h"

namespace DMK
{
	using namespace GraphicsCore;

	namespace VulkanBackend
	{
		/**
		 * Vulkan Memory Handle object for the Dynamik Engine.
		 */
		class DMK_API VulkanMemoryHandle :
			public GraphicsCore::MemoryHandle,
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
		};
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_MEMORY_HANDLE_H
