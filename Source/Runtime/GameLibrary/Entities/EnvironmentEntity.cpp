// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EnvironmentEntity.h"

#include "../Utilities/MeshFactory.h"

void DMKEnvironmentEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.pushBack(sModule);
}

void DMKEnvironmentEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKEnvironmentEntity::getShaderModule(I32 index)
{
	return shaders.location(index);
}

ARRAY<DMKShaderModule> DMKEnvironmentEntity::getShaders()
{
	return shaders;
}

void DMKEnvironmentEntity::clearEnvironmentMap()
{
	skyBoxMesh.clearVertexAndIndexBuffers();

	for (UI32 index = 0; index < skyBoxMesh.getMaterial().textureContainers.size(); index++)
	{
		skyBoxMesh.getMaterial().textureContainers[index].pTexture->clear();
		StaticAllocator<DMKTexture>::deallocate(skyBoxMesh.getMaterial().textureContainers[index].pTexture, 0);
	}

	skyBoxMesh.getMaterial().textureContainers.clear();
}
