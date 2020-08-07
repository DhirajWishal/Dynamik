// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EnvironmentMap.h"

#include "Utilities/MeshFactory.h"

namespace Dynamik
{
	void DMKEnvironmentMap::setSkyBox(const DMKStaticMeshComponent& component)
	{
		skyBox = component;
	}

	void DMKEnvironmentMap::setShaders(ARRAY<DMKShaderModule> shaderModules)
	{
		this->shaderModules = shaderModules;
	}
	
	void DMKEnvironmentMap::addShaderModule(const DMKShaderModule& sModule)
	{
		shaderModules.pushBack(sModule);
	}
}