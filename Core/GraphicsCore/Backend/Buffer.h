// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsObject.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class Device;

		/**
		 * Buffer Type enum.
		 */
		enum class BufferType : UI8 {
			UNDEFINED,		// Undefined buffer type.
			VERTEX,			// Vertex data buffer.
			INDEX,			// Index data buffer.
			UNIFORM_DATA,	// Uniform data buffer.
			STAGGING,		// Stagging buffer. Used to transfer data to the GPU.
		};

		/**
		 * Buffer object.
		 * This object stores data in the GPU.
		 */
		class Buffer : public GraphicsObject {
		public:
			Buffer(BufferType type = BufferType::UNDEFINED) : mType(type) {}
			virtual ~Buffer() {}

			/**
			 * Get the size of the buffer.
			 *
			 * @return The size in bytes.
			 */
			UI64 Size() const { return mSize; }

			/**
			 * Initialize the buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param size: The size of the buffer in bytes.
			 */
			virtual void Initialize(Device* pDevice, UI64 size) {}

			/**
			 * Terminate the buffer.
			 */
			virtual void Terminate(Device* pDevice) {}

			/**
			 * Map the device memory to the local address space.
			 *
			 * @param pDevice: The device pointer.
			 * @param size: The size in bytes to be mapped.
			 * @param offset: The offset of the buffer. Default is 0.
			 */
			virtual void* MapMemory(Device* pDevice, UI64 size, UI64 offset = 0) { return nullptr; }

			/**
			 * Unmap the mapped memory.
			 *
			 * @param pDevice: The device pointer.
			 */
			virtual void UnmapMemory(Device* pDevice) {}

		public:
			/**
			 * Copy data to this buffer.
			 * Make sure that the buffer is allocated.
			 *
			 * @param pDevice: The device pointer.
			 * @param pData: The data pointer to copy data from.
			 * @param size: The size of the data to be copied in bytes.
			 */
			void CopyData(Device* pDevice, const void* pData, UI64 size, UI64 offset = 0);

			/**
			 * Move data to this buffer.
			 * Make sure that the buffer is allocated.
			 *
			 * @param pDevice: The device pointer.
			 * @param pData: The data pointer to copy data from.
			 * @param size: The size of the data to be copied in bytes.
			 */
			void MoveData(Device* pDevice, const void* pData, UI64 size, UI64 offset = 0);

			/**
			 * Copy data to this buffer using another buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param pBuffer: The other buffer pointer.
			 */
			virtual void CopyBuffer(Device* pDevice, const Buffer* pBuffer) {}

			/**
			 * Move data to this buffer using another buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param pBuffer: The other buffer pointer.
			 */
			virtual void MoveBuffer(Device* pDevice, const Buffer* pBuffer) {}

			/**
			 * Extend the buffer by a new size.
			 * The contents of this buffer will be copied to the other buffer.
			 *
			 * @param pDevice: The device pointer.
			 * @param size: The size to be extended to (mSize = mSize + size).
			 */
			virtual void Extend(Device* pDevice, UI64 size) {}

		public:
			UI64 mSize = 0;
			BufferType mType = BufferType::UNDEFINED;
		};

		/**
		 * Buffer Ref object.
		 * This object stores information about a single buffer data block.
		 */
		class BufferRef {
		public:
			BufferRef(BufferType type = BufferType::UNDEFINED, UI64 handle = 0, UI64 size = 0, UI64 offset = 0)
				: mType(type), mHandle(handle), mSize(size), mOffset(offset) {}
			~BufferRef() {}

			UI64 GetHandle() const { return mHandle; }
			UI64 GetSize() const { return mSize; }
			UI64 GetOffset() const { return mOffset; }

			BufferType GetType() const { return mType; }

		public:
			UI64 mHandle = 0;
			UI64 mSize = 0;
			UI64 mOffset = 0;

			BufferType mType = BufferType::UNDEFINED;
		};
	}
}