// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_VERTEX_BUFFER_H
#define _DYNAMIK_VULKAN_BACKEND_VERTEX_BUFFER_H

#include "VulkanBackend/Common/VulkanObject.h"
#include "VulkanBuffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Vertex Buffer object.
			 */
			class VulkanVertexBuffer : public VulkanBuffer, public VertexBuffer {
			public:
				/**
				 * Default constructor.
				 */
				VulkanVertexBuffer() {}

				/**
				 * Default destructor.
				 */
				~VulkanVertexBuffer() {}

				/**
				 * Map the GPU address space of the buffer to the local address space.
				 *
				 * @param size: The size in bytes to be exposed.
				 * @param offset: The offset in the memory block. Default is 0.
				 * @return: Void pointer to the mapped address space.
				 */
				virtual void* MapToLocal(UI64 size, UI64 offset = 0) override final;

				/**
				 * Unmap the mapped address space from local.
				 */
				virtual void UnmapFromLocal() override final;

				/**
				 * Copy data to this buffer from another buffer.
				 *
				 * @param pBuffer: The buffer from which the data is copied from.
				 */
				virtual void CopyFrom(Buffer* pBuffer) override final;

				/**
				 * Move data to this buffer from another buffer.
				 *
				 * @param pBuffer: The buffer from which the data is moved from.
				 */
				virtual void MoveFrom(Buffer* pBuffer) override final;
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_VERTEX_BUFFER_H
