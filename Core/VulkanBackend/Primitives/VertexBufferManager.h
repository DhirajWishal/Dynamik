// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Buffers/VertexBuffer.h"
#include "GraphicsCore/Objects/BufferHandle.h"
#include "GraphicsCore/Objects/VertexBufferObject.h"

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Vertex Buffer Manager object.
		 * This object manages the vertex buffer creation and other aspects of it.
		 */
		class VertexBufferManager {
		public:
			VertexBufferManager() {}
			~VertexBufferManager() {}

			/**
			 * Try and create a new Vertex Buffer.
			 * This method checks if the vertex buffer requires a seperate buffer to store its data. If true, a new
			 * buffer is created and if not, an exsisting buffer is used.
			 *
			 * @param vDevice: The Vulkan device which the buffer is bound to.
			 * @param vertexBuffer: The vertex buffer object to initialize the data with.
			 * @return Buffer Handle.
			 */
			GraphicsCore::BufferHandle TryCreateBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer);

		private:
			/**
			 * Create a new buffer to store data.
			 *
			 * @param vDevice: The Vulkan Device object.
			 * @param vertexBuffer: The vertex buffer object to move data from.
			 * @return The buffer handle.
			 */
			GraphicsCore::BufferHandle CreateNewBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer);

			/**
			 * Extend an existing buffer and insert data to it and return a handle.
			 * 
			 * @param vDevice: The Vulkan device object.
			 * @param vertexBuffer: The vertex buffer object to move data from.
			 * @param pBuffer: The vertex buffer pointer.
			 * @return BufferHandle.
			 */
			GraphicsCore::BufferHandle ExtendInsert(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer, VertexBuffer* pBuffer);

			std::unordered_map<UI64, VertexBuffer> mBufferMap;	// The vertex buffer map.
		};
	}
}