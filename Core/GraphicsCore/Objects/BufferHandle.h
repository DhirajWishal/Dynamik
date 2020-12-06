// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
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
		 * Buffer Handle object.
		 * This object holds the buffer handle and some basic information about it.
		 */
		class BufferHandle {
		public:
			BufferHandle() {}

			/**
			 * Construct the handle using the type, handle, size and optionally the offset.
			 * 
			 * @param type: The type of the buffer.
			 * @param handle: The buffer handle.
			 * @param size: The size of the buffer.
			 * @param offset: The offset of the buffer. Default is 0.
			 */
			BufferHandle(BufferType type, UI64 handle, UI64 size, UI64 offset = 0)
				: mType(type), mHandle(handle), mSize(size), mOffset(offset) {}

			~BufferHandle() {}

			UI64 GetHandle() const { return mHandle; }
			UI64 GetSize() const { return mSize; }
			UI64 GetOffset() const { return mOffset; }
			BufferType GetType() const { return mType; }

			UI64 mHandle = 0;
			UI64 mSize = 0;
			UI64 mOffset = 0;
			BufferType mType = BufferType::UNDEFINED;
		};
	}
}