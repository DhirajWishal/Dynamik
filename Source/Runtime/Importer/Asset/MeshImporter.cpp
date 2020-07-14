// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "Core/Components/RenderableComponents/StaticMeshComponent.h"

#include "Wrappers/AssimpWrapper.h"

namespace Dynamik
{
	ARRAY<DMKStaticMeshComponent> DMKMeshImporter::loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout)
	{
		AssimpWrapper _wrapper;
		return _wrapper.loadStaticModel(path, vertexLayout);
	}

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKStaticMeshComponent>& meshes)
	{
		for (UI32 index = 0; index < meshes.size(); index++)
			Cast<DMKVertexBuffer>(meshes[index].vertexBuffer).clear();
	}
}