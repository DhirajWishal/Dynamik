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
		return indexBuffer.byteSize();
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
}