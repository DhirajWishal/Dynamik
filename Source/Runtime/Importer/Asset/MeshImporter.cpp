// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "Core/Components/RenderableComponents/MeshComponent.h"
#include "Core/Objects/Resource/Primitives.h"

#include "Wrappers/AssimpWrapper.h"

namespace Dynamik
{
	ARRAY<DMKMeshComponent> DMKMeshImporter::loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout)
	{
		AssimpWrapper wrapper;
		return wrapper.loadStaticModel(path, vertexLayout);
	}

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKMeshComponent>& meshes)
	{
		for (UI32 index = 0; index < meshes.size(); index++)
			StaticAllocator<BYTE>::deallocate(meshes[index].vertexBuffer, meshes[index].vertexCount * meshes[index].vertexLayout.getVertexSize());
	}
}