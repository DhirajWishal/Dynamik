// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

//#include "GraphicsCore/Backend/Objects/VertexBuffer.h"
//#include "GraphicsCore/Backend/Objects/IndexBuffer.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class GameEntity;

		/**
		 * Static Mesh Object.
		 * This object stores information about a single mesh.
		 *
		 * This object contains,
		 * - Vertex Buffer.
		 * - Index Buffer.
		 * - Materials. (textures, materials, ...)
		 */
		class StaticMeshObject {
			friend GameEntity;

		public:
			StaticMeshObject() {}
			~StaticMeshObject() {}

			/**
			 * Get the parent entity pointer.
			 *
			 * @return Pointer of the parent entity.
			 */
			GameEntity* GetParent() const { return pParentEntity; }

		public:
			//VertexBufferRef mVertexBufferRef;	// Vertex buffer reference.
			GameEntity* pParentEntity = nullptr;	// The entity which created the static mesh.
		};
	}
}
