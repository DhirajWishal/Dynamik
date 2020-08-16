// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MeshImporter.h"

#include "Wrappers/AssimpWrapper.h"

namespace Dynamik
{
	ARRAY<DMKMeshObject> DMKMeshImporter::loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout)
	{
		AssimpWrapper _wrapper;
		return _wrapper.loadStaticModelEntity(path, vertexLayout).meshObjects;
	}

	void DMKMeshImporter::unloadMesh(const ARRAY<DMKMeshObject>& meshes)
	{
		for (UI32 index = 0; index < meshes.size(); index++)
			Cast<DMKVertexBuffer>(meshes[index].vertexBuffer).clear();
	}
}