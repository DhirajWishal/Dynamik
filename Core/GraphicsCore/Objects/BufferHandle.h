// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace VulkanBackend
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