// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EnvironmentMap.h"

#include "Utilities/MeshFactory.h"

namespace Dynamik
{
	void DMKEnvironmentMap::addShaderModule(const DMKShaderModule& sModule)
	{
		shaders.pushBack(sModule);
	}

	void DMKEnvironmentMap::setShaderModules(ARRAY<DMKShaderModule> sModules)
	{
		shaders = std::move(sModules);
	}

	DMKShaderModule* DMKEnvironmentMap::getShaderModule(I32 index)
	{
		return shaders.location(index);
	}
	
	ARRAY<DMKShaderModule> DMKEnvironmentMap::getShaders()
	{
		return shaders;
	}
}