// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Graphics/Mesh/MeshHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Component object for the Dynamik Engine.
		 * This object contains methods and information required by the Dynamik Graphics engine to render a given
		 * object.
		 */
		class GraphicsComponent {
		public:
			/**
			 * Default constructor.
			 */
			GraphicsComponent() {}

			/**
			 * Default destructor.
			 */
			virtual ~GraphicsComponent() {}

			/**
			 * Load a mesh from an asset file.
			 *
			 * @param pAsset: The asset path.
			 * @param vertex: The vertex description.
			 * @param indexSize: The size of the index in bytes.
			 * @return The pointer to the created mesh handle.
			 */
			MeshHandle* LoadMeshFromFile(const char* pAsset, Vertex vertex, UI8 indexSize);
		};
	}
}
