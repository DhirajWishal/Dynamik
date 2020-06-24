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

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "../RenderableComponent.h"
#include "Core/Object/Resource/ShaderFactory.h"
#include "Core/Object/Resource/Textures/TextureFactory.h"
#include "Core/Object/Resource/VertexBuffer.h"
#include "Core/Object/Resource/IndexBuffer.h"

namespace Dynamik
{
	/*
	 Usage of the mesh component
	*/
	enum class DMKMeshComponentUsage {
		DMK_MESH_COMPONENT_USAGE_STATIC,
		DMK_MESH_COMPONENT_USAGE_ANIMATED,
		DMK_MESH_COMPONENT_USAGE_SKYBOX,
	};

	/*
	 Mesh Component for the Dynamik Engine.
	*/
	class DMK_API DMKMeshComponent : public DMKRenderableComponent {
	public:
		DMKMeshComponent() = default;
		DMKMeshComponent(const DMKMeshComponentUsage& usage) : usage(usage) {}
		DMKMeshComponent(const DMKMeshComponentUsage& usage, const DMKVertexLayout& descriptor, const DMKDataType& type)
			: usage(usage), vertexLayout(descriptor), indexBufferType(type) {}
		~DMKMeshComponent() {}

		/* Get the total byte size of the vertex buffer object */
		UI64 getVertexBufferObjectByteSize();

		/* Get the total byte size of the index buffer object */
		UI64 getIndexBufferObjectByteSize();

		/*
		 Pack all vertex data into a location.

		 @warn: The pre allocated memory location must be allocated to fit the whole vertex buffer object.
				To ensure this, use getVertexBufferObjectByteSize() to allocate the buffer precisely.
		*/
		void packData(VPTR location);

		void setMatrix(const MAT4F& matrix);
		void update(const MAT4F& matrix);
		MAT4F getMatrix();

	public:		/* Public Data Store */
		ARRAY<UI32> indexBuffer;
		VPTR vertexBuffer = nullptr;
		UI64 vertexCount = 0;

	public:		/* Matrix */
		MAT4F modelMatrix;

		operator MAT4F() const;

	public:		/* Descriptors */
		DMKVertexLayout vertexLayout;
		DMKDataType indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;
		DMKMeshComponentUsage usage = DMKMeshComponentUsage::DMK_MESH_COMPONENT_USAGE_STATIC;
	};
}

#endif // !_DYNAMIK_MESH_COMPONENT_H