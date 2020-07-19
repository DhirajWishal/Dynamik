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
		isMatrixUpdated = true;
	}

	void DMKStaticMeshComponent::update(const MAT4& matrix)
	{
		modelMatrix = matrix;
		isMatrixUpdated = true;
	}

	MAT4 DMKStaticMeshComponent::getMatrix()
	{
		return modelMatrix;
	}

	UI64 DMKStaticMeshComponent::getUniformByteSize()
	{
		return sizeof(MAT4);
	}

	B1 DMKStaticMeshComponent::isUpdated() const
	{
		return isMatrixUpdated;
	}

	void DMKStaticMeshComponent::resetUpdateNotice()
	{
		isMatrixUpdated = false;
	}

	void DMKStaticMeshComponent::setPosition(Vector3F position)
	{
		this->position = position;
		translate(Matrix4F::Identity, position);
	}

	void DMKStaticMeshComponent::setScale(Vector3F scale)
	{
		this->scale = scale;
		modelMatrix *= DMathLib::scale(Matrix4F::Identity, scale);
	}

	void DMKStaticMeshComponent::setRotation(Quaternion rotation)
	{
		this->rotation = rotation;
		modelMatrix *= DMathLib::toRotationalMatrix(rotation);
	}

	void DMKStaticMeshComponent::translate(const MAT4& mat, const VEC3& vec)
	{
		modelMatrix *= DMKMathFunctions::translate(mat, vec);
	}

	void DMKStaticMeshComponent::rotate(const VEC3& direction, const F32& radians)
	{
		modelMatrix = DMKMathFunctions::rotate(modelMatrix, radians, direction);
	}

	void DMKStaticMeshComponent::addTexture(const STRING& path, const DMKTextureType& type)
	{
		addMaterial(DMKMaterial::createDefaultTexture(path, type));
	}

	void DMKStaticMeshComponent::clearVertexBuffer()
	{
		vertexBuffer.clear();
	}

	void DMKStaticMeshComponent::clearIndexBuffer()
	{
		indexBuffer.clear();
	}

	DMKStaticMeshComponent::operator MAT4() const
	{
		return this->modelMatrix;
	}
}