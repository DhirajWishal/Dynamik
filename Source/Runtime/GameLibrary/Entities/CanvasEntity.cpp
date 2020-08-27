// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "CanvasEntity.h"

namespace Dynamik
{
	void DMKCanvasEntity::addShaderModule(const DMKShaderModule& sModule)
	{
		shaders.pushBack(sModule);
	}

	void DMKCanvasEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
	{
		shaders = std::move(sModules);
	}

	DMKShaderModule* DMKCanvasEntity::getShaderModule(I32 index)
	{
		return shaders.location(index);
	}

	ARRAY<DMKShaderModule> DMKCanvasEntity::getShaders()
	{
		return shaders;
	}

	void DMKCanvasEntity::setFrameMesh(const DMKMeshObject& meshObject)
	{
		frameMesh = meshObject;
	}

	DMKMeshObject* DMKCanvasEntity::getFrameMesh() const
	{
		return Cast<DMKMeshObject*>(&frameMesh);
	}
}
