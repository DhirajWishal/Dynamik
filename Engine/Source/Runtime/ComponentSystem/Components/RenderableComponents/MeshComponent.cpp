// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshComponent.h"

#include "Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	/* Get the vertex buffer object byte size */
	UI64 DMKMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexDescriptor.getVertexSize() * vertexBuffer->size();
	}

	/* Get the index buffer object byte size */
	UI64 DMKMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI64)indexBufferType * indexBuffer->size();
	}

	/* Pack data to a given location. That location must be pre allocated */
	void DMKMeshComponent::packData(VPTR location)
	{
	}

	void DMKMeshComponent::setMatrix(const MAT4F& matrix)
	{
		modelMatrix = matrix;
	}

	void DMKMeshComponent::update(const MAT4F& matrix)
	{
		modelMatrix = matrix;
	}

	MAT4F DMKMeshComponent::getMatrix()
	{
		return modelMatrix;
	}

	DMKMeshComponent::operator MAT4F() const
	{
		return this->modelMatrix;
	}
}