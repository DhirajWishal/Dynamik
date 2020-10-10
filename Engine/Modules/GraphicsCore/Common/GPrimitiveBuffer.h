// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H

#include "GBuffer.h"

namespace DMK
{
	/**
	 * Graphics primitive buffer for the Dynamik Engine.
	 * These buffers stores multiple entries of a known value eg: Vertex, Index. 
	 */
	class DMK_API GPrimtiveBuffer : public GBuffer {
	public:
		/**
		 * Default constructor.
		 */
		GPrimtiveBuffer() {}

		/**
		 * Default destructor.
		 */
		virtual ~GPrimtiveBuffer() {}

		/**
		 * Set the stride of the vertex buffer.
		 * The stride is the number of bytes to the next vertex or the size of a single vertex.
		 *
		 * @param stride: The stride of the vertex buffer.
		 */
		void SetStride(UI64 stride) { this->stride = stride; }

		/**
		 * Get the stride of the buffer.
		 */
		UI64 GetStride() const { return stride; }

	protected:
		UI64 stride = 0;
	};

	typedef GPrimtiveBuffer GVertexBuffer;
	typedef GPrimtiveBuffer GIndexBuffer;
}

#endif // !_DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H
