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

namespace Dynamik
{
	/*
	 Renderable Mesh Object
	*/
	class DMK_API RMeshObject {
	public:
		RMeshObject() {}
		virtual ~RMeshObject() {}

		UI64 vertexCount = 0;
		UI64 vertexOffset = 0;
		UI64 indexCount = 0;
		UI64 indexOffset = 0;

		RTexture* pTexture;
	};
}

#endif // !_DYNAMIK_RENDERER_MESH_COMPONENT_H
