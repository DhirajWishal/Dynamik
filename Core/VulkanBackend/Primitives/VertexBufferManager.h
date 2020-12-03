// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Buffers/VertexBuffer.h"
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
			/**
			 * Default constructor.
			 */
			VertexBufferManager() {}

			/**
			 * Default destructor.
			 */
			~VertexBufferManager() {}

			/**
			 * Try and create a new Vertex Buffer.
			 * This method checks if the vertex buffer requires a seperate buffer to store its data. If true, a new
			 * buffer is created and if not, an exsisting buffer is used.
			 *
			 * @param vDevice: The Vulkan device which the buffer is bound to.
			 * @param vertexBuffer: The vertex buffer object to initialize the data with.
			 * @return Vertex Buffer Handle.
			 */
			GraphicsCore::VertexBufferHandle TryCreateBuffer(const VulkanDevice& vDevice, GraphicsCore::VertexBufferObject&& vertexBuffer);

			std::unordered_map<UI64, VertexBuffer> mBufferMap;	// The vertex buffer map.
		};
	}
}