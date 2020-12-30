// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_MESH_HANDLE_H
#define _DYNAMIK_GRAPHICS_MESH_HANDLE_H

#include "GraphicsCore/Backend/Objects/VertexBuffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		using namespace GraphicsCore;

		/**
		 * Mesh handle for the Dynamik Engine.
		 * This object stores information about mesh objects.
		 */
		class MeshHandle {
		public:
			/**
			 * Default constructor.
			 */
			MeshHandle() {}

			/**
			 * Default destructor.
			 */
			virtual ~MeshHandle() {}

			VertexBufferRef vertexBufferRef = {};	// Vertex buffer reference object.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_MESH_HANDLE_H
