// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Buffer.h"

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Vertex Buffer object.
		 * This object stores vertex information.
		 */
		class VertexBuffer : public Buffer {
		public:
			/**
			 * Default constructor.
			 */
			VertexBuffer() {}

			/**
			 * Default destructor.
			 */
			~VertexBuffer() {}

			/**
			 * Initailize the buffer.
			 *
			 * @param vDevice: The Vulkan device object.
			 * @param size: The size of the buffer in bytes.
			 */
			virtual void Initialize(const VulkanDevice& vDevice, UI64 size) override final;

			/**
			 * Map the buffer's device memory to the local address space and return its address.
			 * If the size or the offset is invalid, nullptr will be returned with an error logged to the console.
			 *
			 * @param vDevice: The device the buffer is bound to.
			 * @param size: The size of the mapping.
			 * @param offset: The offset of the buffer data to be mapped. Default is 0.
			 * @return The data pointer.
			 */
			virtual void* MapMemory(const VulkanDevice& vDevice, UI64 size, UI64 offset = 0) override final;

			/**
			 * Unmap the mapped buffer memory.
			 *
			 * @param vDevice: The device the buffer is bound to.
			 */
			virtual void UnmapMemory(const VulkanDevice& vDevice) override final;
		};
	}
}