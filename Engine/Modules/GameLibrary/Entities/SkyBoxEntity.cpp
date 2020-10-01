// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "SkyBoxEntity.h"

void DMKSkyBoxEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.push_back(sModule);
}

void DMKSkyBoxEntity::setShaderModules(std::vector<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKSkyBoxEntity::getShaderModule(I32 index)
{
	return &shaders.at(index);
}

std::vector<DMKShaderModule> DMKSkyBoxEntity::getShaders()
{
	return shaders;
}

void DMKSkyBoxEntity::setMeshObject(const DMKMeshObject& meshData)
{
	meshObject = meshData;
}

DMKMeshObject* DMKSkyBoxEntity::getMeshObject() const
{
	return Cast<DMKMeshObject*>(&meshObject);
}
