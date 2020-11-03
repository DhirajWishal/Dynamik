// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_MESH_HANDLE_H
#define _DYNAMIK_GRAPHICS_MESH_HANDLE_H

#include "GraphicsCore/Backend/Objects/VertexBuffer.h"

namespace DMK
{
	namespace Graphics
	{
		using namespace GraphicsCore;

		/**
		 * Mesh handle for Dynamik.
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
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_MESH_HANDLE_H
