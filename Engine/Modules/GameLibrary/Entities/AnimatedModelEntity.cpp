// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimatedModelEntity.h"

void DMKAnimatedModelEntity::addShaderModule(const DMKShaderModule& sModule)
{
	shaders.push_back(sModule);
}

void DMKAnimatedModelEntity::setShaderModules(std::vector<DMKShaderModule> sModules)
{
	shaders = std::move(sModules);
}

DMKShaderModule* DMKAnimatedModelEntity::getShaderModule(I32 index)
{
	return Cast<DMKShaderModule*>(&shaders.at(index));
}

std::vector<DMKShaderModule> DMKAnimatedModelEntity::getShaders()
{
	return shaders;
}

void DMKAnimatedModelEntity::addResourceRequest(const DMKResourceRequest& request)
{
	resourceRequests.push_back(request);
}

void DMKAnimatedModelEntity::setResourceRequests(std::vector<DMKResourceRequest> requests)
{
	resourceRequests = std::move(requests);
}

DMKResourceRequest DMKAnimatedModelEntity::getResourceRequest(I64 index)
{
	return resourceRequests[index];
}

std::vector<DMKResourceRequest> DMKAnimatedModelEntity::getResourceRequests() const
{
	return resourceRequests;
}
