// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_BUFFER_FACTORY_H
#define _DYNAMIK_GRAPHICS_CORE_BUFFER_FACTORY_H

#include "GraphicsCore/Backend/Objects/VertexBuffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Buffer Factory for the Dynamik Engine.
		 * This object is the base class for all the buffer factories implemented by the different backend APIs.
		 */
		class BufferFactory : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			BufferFactory() {}

			/**
			 * Default destructor.
			 */
			virtual ~BufferFactory() {}

			/**
			 * Create a raw buffer.
			 *
			 * @param size: The size of the buffer in bytes.
			 * @return: The created raw buffer pointer.
			 */
			virtual Buffer* CreateRawBuffer(UI64 size) { return nullptr; }

			/**
			 * Create a vertex buffer using the Vertex and the vertex count.
			 *
			 * @param vertex: The vertex structure defining the structure of a single vertex.
			 * @param vertexCount: The total number of vertexes that will be stored.
			 * @return: The created vertex buffer pointer.
			 */
			virtual VertexBuffer* CreateVertexBuffer(const Vertex& vertex, UI64 vertexCount) { return nullptr; }

			/**
			 * Create a vertex buffer using the Vertex and the total buffer size.
			 *
			 * @param vertex: The vertex structure defining the structure of a single vertex.
			 * @param size: The total size of the buffer.
			 * @return: The created vertex buffer pointer.
			 */
			virtual VertexBuffer* CreateVertexBuffer(const Vertex& vertex, UI64 size) { return nullptr; }

			/**
			 * Destroy a created buffer object.
			 *
			 * @param pBuffer: The buffer to be destroyed.
			 */
			virtual void DestroyBuffer(Buffer* pBuffer) {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_BUFFER_FACTORY_H
