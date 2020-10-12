// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_MESH_HANDLE_H
#define _DYNAMIK_GRAPHICS_CORE_MESH_HANDLE_H

#include "GraphicsCore/Objects/Primitives.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Mesh Handle for the Dynamik Engine.
		 * This object is used to store information about a single mesh object.
		 * 
		 * Each mesh contains one Vertex and Index buffer. There can be multiple uniform buffers. 
		 */
		class DMK_API MeshHandle {
		public:
			/**
			 * Default constructor.
			 */
			MeshHandle() {}

			/**
			 * Default destructor.
			 */
			virtual ~MeshHandle() {}

			/**
			 * Users are to submit vertex data using this method.
			 */
			virtual PrimitveBuffer GetVertexBuffer() {}

			/**
			 * Users are to submit index data using this method.
			 */
			virtual PrimitveBuffer GetIndexBuffer() {}

			/**
			 * Users are to submit uniform buffers using this method.
			 * The number of uniform buffers must be equal to the available uniform buffers in the shaders.
			 * And the uniform buffers should match with the uniforms in the shaders.
			 */
			virtual std::vector<UniformBuffer> GetUniformBuffers() {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_MESH_HANDLE_H
