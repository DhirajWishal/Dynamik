// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_BUFFER_H

#include "GraphicsCore/Backend/Common/GObject.h"
#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Buffer object for Dynamik.
		 * This object is the base class for all the graphics and compute buffers.
		 */
		class Buffer : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			Buffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~Buffer() {}

			/**
			 * Set the size of the buffer.
			 *
			 * @param size: The size of the buffer in bytes.
			 */
			void SetSize(UI64 size) { this->size = size; }

			/**
			 * Get the size of the buffer.
			 *
			 * @return Unsigned 64 bit integer.
			 */
			UI64 GetSize() const { return size; }

			/**
			 * Map the GPU address space of the buffer to the local address space.
			 *
			 * @param size: The size in bytes to be exposed.
			 * @param offset: The offset in the memory block. Default is 0.
			 * @return Void pointer to the mapped address space.
			 */
			virtual void* MapToLocal(UI64 size, UI64 offset = 0) {}

			/**
			 * Unmap the mapped address space from local.
			 */
			virtual void UnmapFromLocal() {}

			/**
			 * Copy data to this buffer from another buffer.
			 *
			 * @param pBuffer: The buffer from which the data is copied from.
			 */
			virtual void CopyFrom(Buffer* pBuffer) {}

			/**
			 * Move data to this buffer from another buffer.
			 *
			 * @param pBuffer: The buffer from which the data is moved from.
			 */
			virtual void MoveFrom(Buffer* pBuffer) {}

		protected:
			UI64 size = 0;	// Size of the buffer in bytes.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_BUFFER_H
