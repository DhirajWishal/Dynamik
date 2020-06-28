// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_MESH_COMPONENT_H
#define _DYNAMIK_RENDERER_MESH_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		17/06/2020
*/
#include "RCoreObject.h"
#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"
#include "Primitives/RTexture.h"
#include "RPipelineObject.h"

namespace Dynamik
{
	/*
	 Renderer Mesh Object
	 This object contains all the necessary information required to render a mesh.

	 The engine allocates one huge buffer for each vertex and index data. Mesh objects contain offsets which
	 points to where its data are stored in the buffer.
	*/
	class DMK_API RMeshObject {
	public:
		RMeshObject() = default;
		virtual ~RMeshObject() = default;

	public:		/* Vertex and Index Data */
		UI64 vertexBufferOffset = 0;
		UI64 indexBufferOffset = 0;

	public:		/* Resource Data */
		ARRAY<RTexture*> pTextures;
		RPipelineObject* pPipeline = nullptr;
		RBuffer* pUniformBuffer = nullptr;

	public:		/* Parent Mesh Component*/
		DMKMeshComponent* pMeshComponent = nullptr;
	};
}

#endif // !_DYNAMIK_RENDERER_MESH_COMPONENT_H
