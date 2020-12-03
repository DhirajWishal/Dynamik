// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include <vulkan/vulkan.h>

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
			/**
			 * Default constructor.
			 */
			BufferHandle() {}

			/**
			 * Default destructor.
			 */
			~BufferHandle() {}

			/**
			 * Get the handle.
			 *
			 * @return The handle.
			 */
			UI64 GetHandle() const { return mHandle; }

			/**
			 * Get the size of the buffer.
			 *
			 * @return The size in bytes.
			 */
			UI64 GetSize() const { return mSize; }

			/**
			 * Get the type of the buffer.
			 *
			 * @return The buffer type.
			 */
			BufferType GetType() const { return mType; }

			UI64 mHandle = 0;	// The buffer handle.
			UI64 mSize = 0;	// The size of the buffer.
			BufferType mType = BufferType::UNDEFINED;	// The buffer type.
		};
	}
}