// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_MESH_COMPONENT_H
#define _DYNAMIK_RENDERER_MESH_COMPONENT_H

#include "RCoreObject.h"
#include "Core/Objects/Resources/MeshObject.h"
#include "Primitives/RTexture.h"
#include "RPipelineObject.h"

/* Renderer Uniform Container */
struct DMK_API RUniformContainer {
	DMKUniformBuffer* pParent = nullptr;
	RBuffer* pUniformBuffer = nullptr;
};

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
	UI64 resourceIndex = 0;

	UI64 vertexCount = 0;
	UI64 vertexOffset = 0;
	UI64 indexCount = 0;
	UI64 indexOffset = 0;

	RPipelineResource* pResourceObject = nullptr;

public:		/* Parent Mesh Component*/
	DMKMeshObject* pParentObject = nullptr;
};

#endif // !_DYNAMIK_RENDERER_MESH_COMPONENT_H
