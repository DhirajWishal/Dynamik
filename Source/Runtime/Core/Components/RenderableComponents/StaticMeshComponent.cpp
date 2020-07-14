// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticMeshComponent.h"

#include "Core/Memory/MemoryFunctions.h"
#include "Importer/Asset/MeshImporter.h"
#include "Core/Utilities/TextureFactory.h"
#include "Core/Math/MathFunctions.h"

namespace Dynamik
{
	/* Get the vertex buffer object byte size */
	UI64 DMKStaticMeshComponent::getVertexBufferObjectByteSize()
	{
		return vertexBuffer.byteSize();
	}

	/* Get the index buffer object byte size */
	UI64 DMKStaticMeshComponent::getIndexBufferObjectByteSize()
	{
		return (UI64)indexBufferType * indexBuffer.size();
	}

	/* Pack data to a given location. That location must be pre allocated */
	void DMKStaticMeshComponent::packData(VPTR location)
	{
	}

	void DMKStaticMeshComponent::setMatrix(const MAT4& matrix)
	{
		modelMatrix = matrix;
	}

	void DMKStaticMeshComponent::update(const MAT4& matrix)
	{
		modelMatrix = matrix;
	}

	MAT4 DMKStaticMeshComponent::getMatrix()
	{
		return modelMatrix;
	}

	UI64 DMKStaticMeshComponent::getUniformByteSize()
	{
		return sizeof(MAT4);
	}

	void DMKStaticMeshComponent::translate(const MAT4& mat, const VEC3& vec)
	{
		modelMatrix = DMKMathFunctions::translate(mat, vec);
	}

	void DMKStaticMeshComponent::rotate(const VEC3& direction, const F32& radians)
	{
		modelMatrix = DMKMathFunctions::rotate(modelMatrix, radians, direction);
	}

	void DMKStaticMeshComponent::addTexture(const STRING& path, const DMKTextureType& type)
	{
		pTextures.pushBack(DMKTextureFactory::create(type, path));
	}

	void DMKStaticMeshComponent::clearVertexBuffer()
	{
		vertexBuffer.clear();
	}

	void DMKStaticMeshComponent::clearIndexBuffer()
	{
		indexBuffer.clear();
	}

	void DMKStaticMeshComponent::addMaterial(const DMKMaterial& material)
	{
		materials.pushBack(material);
	}

	DMKStaticMeshComponent::operator MAT4() const
	{
		return this->modelMatrix;
	}
}