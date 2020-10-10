// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_BUFFER_H

#include "GMemoryHandle.h"

namespace DMK
{
	/**
	 * Buffer base class for the Dynamik Engine.
	 */
	class DMK_API GBuffer : public GObject {
	public:
		/**
		 * Default constructor.
		 */
		GBuffer() {}

		/**
		 * Default destructor.
		 */
		virtual ~GBuffer() {}

		/**
		 * Set the memory handle of the buffer.
		 *
		 * @param pMemoryHandle: The memory handle to be set.
		 */
		void SetMemoryHandle(GMemoryHandle* pMemoryHandle) { this->pMemoryHandle = pMemoryHandle; }

		/**
		 * Get the memory handle of the buffer.
		 */
		GMemoryHandle* GetMemoryHandle() const { return pMemoryHandle; }

		/**
		 * Set the buffer size.
		 *
		 * @param size: The buffer size in bytes.
		 */
		void SetSize(UI64 size) { this->size = size; }

		/**
		 * Get the buffer size.
		 */
		UI64 GetSize() const { return size; }

	protected:
		GMemoryHandle* pMemoryHandle = nullptr;
		UI64 size = 0;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_BUFFER_H
