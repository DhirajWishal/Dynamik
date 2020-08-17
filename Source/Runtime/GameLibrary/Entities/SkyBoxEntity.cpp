// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "SkyBoxEntity.h"

namespace Dynamik
{
	void DMKSkyBoxEntity::addShaderModule(const DMKShaderModule& sModule)
	{
		shaders.pushBack(sModule);
	}

	void DMKSkyBoxEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
	{
		shaders = std::move(sModules);
	}

	DMKShaderModule* DMKSkyBoxEntity::getShaderModule(I32 index)
	{
		return shaders.location(index);
	}

	ARRAY<DMKShaderModule> DMKSkyBoxEntity::getShaders()
	{
		return shaders;
	}

	void DMKSkyBoxEntity::setMeshObject(const DMKMeshObject& meshData)
	{
		meshObject = meshData;
	}

	DMKMeshObject* DMKSkyBoxEntity::getMeshObject() const
	{
		return &meshObject;
	}
}
