// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_MEMORY_HANDLE_H
#define _DYNAMIK_GRAPHICS_CORE_MEMORY_HANDLE_H

#include "Object.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Memory Handle object.
		 * This object stored information of a memory block in the GPU memory.
		 */
		class DMK_API MemoryHandle : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			MemoryHandle() {}

			/**
			 * Default destructor.
			 */
			virtual ~MemoryHandle() {}

			/**
			 * Map the graphics memory to the local address space.
			 *
			 * @param size: The number of bytes to be mapped.
			 * @param offset: The offset of the memory block.
			 */
			virtual void* MapToLocal(UI64 size, UI64 offset) { return nullptr; }

			/**
			 * Unmap the mapped memory from the local address space.
			 */
			virtual void UnmapMemory() {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_MEMORY_HANDLE_H
