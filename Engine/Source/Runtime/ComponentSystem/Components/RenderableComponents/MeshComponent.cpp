// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshComponent.h"

#include "Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"
#include "Core/Object/Resource/TextureFactory.h"

namespace Dynamik
{
	/* Get the vertex buffer object byte size */
	UI64 DMKMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexCount * vertexLayout.getVertexSize();
	}

	/* Get the index buffer object byte size */
	UI64 DMKMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI64)indexBufferType * indexBuffer.size();
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

	void DMKMeshComponent::addTexture(const STRING& path, const DMKTextureType& type)
	{
		pTextures.pushBack(DMKTextureFactory::create(type, path));
	}

	void DMKMeshComponent::clearVertexBuffer()
	{
		StaticAllocator<BYTE>::deallocate(vertexBuffer, getVertexBufferObjectByteSize());
	}

	void DMKMeshComponent::clearIndexBuffer()
	{
		indexBuffer.clear();
	}

	DMKMeshComponent::operator MAT4F() const
	{
		return this->modelMatrix;
	}
}