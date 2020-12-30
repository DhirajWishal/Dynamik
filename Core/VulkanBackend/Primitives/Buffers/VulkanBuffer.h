// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/BufferHandle.h"
#include "GraphicsCore/Backend/Buffer.h"
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
		class VulkanBuffer : public GraphicsCore::Buffer {
		public:
			VulkanBuffer(GraphicsCore::BufferType type) : Buffer(type) {}
			virtual ~VulkanBuffer() {}

			/**
			 * Terminate the buffer.
			 */
			virtual void Terminate(GraphicsCore::Device* pDevice) override final;

		public:
			/**
			 * Copy data to this buffer using another buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param pBuffer: The other buffer pointer.
			 */
			virtual void CopyBuffer(GraphicsCore::Device* pDevice, const Buffer* pBuffer) override final;

			/**
			 * Move data to this buffer using another buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param pBuffer: The other buffer pointer.
			 */
			virtual void MoveBuffer(GraphicsCore::Device* pDevice, const Buffer* pBuffer) override final;

			/**
			 * Extend the buffer by a new size.
			 * The contents of this buffer will be copied to the other buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param size: The size to be extended to (mSize = mSize + size).
			 */
			virtual void Extend(GraphicsCore::Device* pDevice, UI64 size) override final;

		protected:
			/**
			 * Create a Vulkan Buffer handle.
			 *
			 * @param vDevice: The Vulkan device handle.
			 * @param size: The size of the buffer in bytes.
			 * @param usageFlags: The buffer usage flags.
			 * @return VkBuffer handle.
			 */
			VkBuffer CreateBuffer(VkDevice vDevice, UI64 size, VkBufferUsageFlags usageFlags);

			/**
			 * Create a Vulakn Device Memory handle for the buffer.
			 *
			 * @param vDevice: The Vulakn device handle.
			 * @param vPhysicalDevice: The Vulkan physical device handle.
			 * @param vBuffer: The Vulkan buffer handle.
			 * @param memoryProperties: The buffer memory properties.
			 * @return VkDeviceMemory handle.
			 */
			VkDeviceMemory CreateBufferMemory(VkDevice vDevice, VkPhysicalDevice vPhysicalDevice, VkBuffer vBuffer, VkMemoryPropertyFlags memoryProperties);

		protected:
			VkBuffer vBuffer = VK_NULL_HANDLE;	// Vulkan buffer handle.
			VkDeviceMemory vBufferMemory = VK_NULL_HANDLE; // Vulkan device memory handle.
		};
	}
}