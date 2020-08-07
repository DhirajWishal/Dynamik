// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_COMPONENT_H
#define _DYNAMIK_MESH_COMPONENT_H

/*
 Dynamik Mesh Component.
 This component contains all the necessary variables to store all the available mesh data of an imported
 mesh.
 This also contains all the functionalities to manipulate a mesh object.
*/
#include "../RenderableComponent.h"
#include "Core/Utilities/ShaderFactory.h"
#include "Core/Utilities/TextureFactory.h"
#include "Core/Objects/Resources/VertexBuffer.h"

namespace Dynamik
{
	/*
	 Mesh Component for the Dynamik Engine.
	*/
	class DMK_API DMKStaticMeshComponent : public DMKRenderableComponent {
	public:
		DMKStaticMeshComponent() = default;
		~DMKStaticMeshComponent() = default;

		/*
		 Get the total byte size of the vertex buffer object
		*/
		UI64 getVertexBufferObjectByteSize();

		/*
		 Get the total byte size of the index buffer object
		*/
		UI64 getIndexBufferObjectByteSize();

		/*
		 Add a texture to the mesh.

		 @param path: Path to the texture file.
		 @param type: Texture type.
		*/
		void addTexture(const STRING& path, const DMKTextureType& type);

		/*
		 Clear the vertex buffer.
		*/
		void clearVertexBuffer();

		/*
		 Clear the index buffer.
		*/
		void clearIndexBuffer();

	public:		/* Public Data Store */
		DMKVertexBuffer vertexBuffer;
		DMKIndexBuffer indexBuffer;
	};
}

#endif // !_DYNAMIK_MESH_COMPONENT_H
