// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshComponent.h"

#include "Core/Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"
#include "Core/Object/Resource/TextureFactory.h"
#include "Core/Math/MathFunctions.h"

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

	void DMKMeshComponent::setMatrix(const MAT4& matrix)
	{
		modelMatrix = matrix;
	}

	void DMKMeshComponent::update(const MAT4& matrix)
	{
		modelMatrix = matrix;
	}

	MAT4 DMKMeshComponent::getMatrix()
	{
		return modelMatrix;
	}

	UI64 DMKMeshComponent::getUniformByteSize()
	{
		return sizeof(MAT4);
	}

	void DMKMeshComponent::translate(const MAT4& mat, const VEC3& vec)
	{
		modelMatrix = DMKMathFunctions::translate(mat, vec);
	}

	void DMKMeshComponent::rotate(const VEC3& direction, const F32& radians)
	{
		modelMatrix = DMKMathFunctions::rotate(modelMatrix, radians, direction);
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

	DMKMeshComponent::operator MAT4() const
	{
		return this->modelMatrix;
	}
}