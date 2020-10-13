// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_STATIC_MESH_H
#define _DYNAMIK_GRAPHICS_CORE_STATIC_MESH_H

#include "MeshHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Static Mesh for the Dynamik Engine.
		 * These mesh objects only contains vertex, index, texture and uniform data and cannot be animated.
		 */
		class DMK_API StaticMesh : public MeshHandle {
		public:
			/**
			 * Default constructor.
			 */
			StaticMesh() {}

			/**
			 * Default destructor.
			 */
			~StaticMesh() {}

			/**
			 * Submit the vertex data.
			 */
			virtual PrimitveBuffer GetVertexBuffer() override final;

			/**
			 * Submit the index data.
			 */
			virtual PrimitveBuffer GetIndexBuffer() override final;

			/**
			 * Add a uniform buffer to the mesh.
			 */
			void AddUniformBuffer(const UniformBuffer& uBuffer);

			/**
			 * Get a uniform buffer from the array.
			 *
			 * @param index: The index of the uniform buffer.
			 * @return: The pointer to the requested uniform buffer.
			 */
			UniformBuffer* GetUniformBuffer(UI64 index) const;

			/**
			 * Get all the stored uniform buffers.
			 *
			 * @return: Pointer to the uniform buffers.
			 */
			std::vector<UniformBuffer>* GetUniformBuffers() const { return Cast<std::vector<UniformBuffer>*>(&uniformBuffers); }

		private:
			std::vector<UniformBuffer> uniformBuffers;
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_STATIC_MESH_H
