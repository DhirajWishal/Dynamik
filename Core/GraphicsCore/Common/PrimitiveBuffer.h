// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H

#include "Buffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics primitive buffer for the Dynamik Engine.
		 * These buffers stores multiple entries of a known value eg: Vertex, Index.
		 */
		class DMK_API PrimtiveBuffer : public Buffer {
		public:
			/**
			 * Default constructor.
			 */
			PrimtiveBuffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~PrimtiveBuffer() {}

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

		typedef PrimtiveBuffer VertexBuffer;
		typedef PrimtiveBuffer IndexBuffer;
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_PRIMITIVE_BUFFER_H
