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
#include "Core/Objects/Resources/Material.h"
#include "Core/Objects/Resources/VertexBuffer.h"

namespace Dynamik
{
	/*
	 Mesh Component for the Dynamik Engine.
	*/
	class DMK_API DMKStaticMeshComponent : public DMKRenderableComponent {
	public:
		DMKStaticMeshComponent() = default;
		DMKStaticMeshComponent(const DMKDataType& type)
			: indexBufferType(type) {}
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
		 Pack all vertex data into a location.

		 @warn: The pre-allocated memory location must be allocated to fit the whole vertex buffer object.
				To ensure this, use getVertexBufferObjectByteSize() to allocate the buffer precisely.
		*/
		void packData(VPTR location);

		void setMatrix(const MAT4& matrix);
		void update(const MAT4& matrix);
		MAT4 getMatrix();

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

	public:		/* Materials */
		void addMaterial(const DMKMaterial& material);

		ARRAY<DMKMaterial> materials;

	public:		/* Matrix */
		/*
		 Model matrix of the mesh component.
		 By default this is passed to the vertex shader with the binding 0.
		*/
		MAT4 modelMatrix = MAT4(1.0f);

		operator MAT4() const;

		UI64 getUniformByteSize();

		/*
		 Checks if the matrix is updated. This way the engine doesn't need to update all the matrices which
		 may include matrices which weren't updated.
		*/
		B1 isUpdated() const;

		/*
		 Reset the update notice. This function is called automatically by the engine once the mesh matrix has
		 been updates internally.
		*/
		void resetUpdateNotice();

	public:		/* Public Data Store */
		DMKVertexBuffer vertexBuffer;
		ARRAY<UI32> indexBuffer;
		UI64 indexCount = 0;
		B1 isMatrixUpdated = false;

	public:		/* Descriptors */
		DMKDataType indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;

	public:		/* Matrix Manipulation */
		void translate(const MAT4& mat, const VEC3& vec) override final;

		void rotate(const VEC3& direction, const F32& radians) override final;
	};
}

#endif // !_DYNAMIK_MESH_COMPONENT_H
