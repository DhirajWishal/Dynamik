// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/BufferHandle.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Vulkan Buffer object.
		 * This object is the base class for all the buffers in the Vulkan Backend.
		 */
		class Buffer {
		public:
			Buffer() {}
			virtual ~Buffer() {}

			/**
			 * Get the size of the buffer.
			 *
			 * @return The size in bytes.
			 */
			UI64 Size() const { return mSize; }

			/**
			 * Terminate the buffer.
			 *
			 * @return vDevice: The Vulkan device object.
			 */
			void Terminate(const VulkanDevice& vDevice);

		public:
			/**
			 * Initailize the buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param size: The size of the buffer in bytes.
			 */
			virtual void Initialize(const VulkanDevice& vDevice, UI64 size) {}

			/**
			 * Map the buffer's device memory to the local address space and return its address.
			 * If the size or the offset is invalid, nullptr will be returned with an error logged to the console.
			 *
			 * @param vDevice: The device the buffer is bound to.
			 * @param size: The size of the mapping.
			 * @param offset: The offset of the buffer data to be mapped. Default is 0.
			 * @return The data pointer.
			 */
			virtual void* MapMemory(const VulkanDevice& vDevice, UI64 size, UI64 offset = 0) { return nullptr; }

			/**
			 * Unmap the mapped buffer memory.
			 *
			 * @param vDevice: The device the buffer is bound to.
			 */
			virtual void UnmapMemory(const VulkanDevice& vDevice) {}

		public:
			/**
			 * Copy data to this buffer.
			 * Make sure that the buffer is allocated.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param pData: The data pointer to copy data from.
			 * @param size: The size of the data to be copied in bytes.
			 */
			void CopyData(const VulkanDevice& vDevice, const void* pData, UI64 size, UI64 offset = 0);

			/**
			 * Move data to this buffer.
			 * Make sure that the buffer is allocated.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param pData: The data pointer to copy data from.
			 * @param size: The size of the data to be copied in bytes.
			 */
			void MoveData(const VulkanDevice& vDevice, const void* pData, UI64 size, UI64 offset = 0);

			/**
			 * Copy data to this buffer using another buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param pBuffer: The other buffer pointer.
			 */
			void CopyBuffer(VulkanDevice& vDevice, const Buffer* pBuffer);

			/**
			 * Move data to this buffer using another buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param pBuffer: The other buffer pointer.
			 */
			void MoveBuffer(const VulkanDevice& vDevice, const Buffer* pBuffer);

			/**
			 * Extend the buffer by a new size.
			 * The contents of this buffer will be copied to the other buffer.
			 *
			 * @param vDevice: The device which owns the buffer.
			 * @param size: The size to be extended to (mSize = mSize + size).
			 */
			void Extend(const VulkanDevice& vDevice, UI64 size);

		protected:
			/**
			 * Create a Vulkan Buffer handle.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param size: The size of the buffer in bytes.
			 * @param usageFlags: The buffer usage flags.
			 * @return VkBuffer handle.
			 */
			VkBuffer CreateBuffer(const VulkanDevice& vDevice, UI64 size, VkBufferUsageFlags usageFlags);

			/**
			 * Create a Vulakn Device Memory handle for the buffer.
			 *
			 * @param vDevice: The Vulakn device object.
			 * @param vBuffer: The Vulkan buffer handle.
			 * @param memoryProperties: The buffer memory properties.
			 * @return VkDeviceMemory handle.
			 */
			VkDeviceMemory CreateBufferMemory(const VulkanDevice& vDevice, VkBuffer vBuffer, VkMemoryPropertyFlags memoryProperties);

		protected:
			VkBuffer vBuffer = VK_NULL_HANDLE;	// Vulkan buffer handle.
			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE; // Vulkan device memory handle.
			UI64 mSize = 0;	// The size of the buffer.
		};
	}
}