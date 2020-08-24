// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimatedModelEntity.h"

namespace Dynamik
{
	void DMKAnimatedModelEntity::addShaderModule(const DMKShaderModule& sModule)
	{
		shaders.pushBack(sModule);
	}

	void DMKAnimatedModelEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
	{
		shaders = std::move(sModules);
	}

	DMKShaderModule* DMKAnimatedModelEntity::getShaderModule(I32 index)
	{
		return Cast<DMKShaderModule*>(shaders.location(index));
	}

	ARRAY<DMKShaderModule> DMKAnimatedModelEntity::getShaders()
	{
		return shaders;
	}

	void DMKAnimatedModelEntity::addResourceRequest(const DMKResourceRequest& request)
	{
		resourceRequests.pushBack(request);
	}

	void DMKAnimatedModelEntity::setResourceRequests(ARRAY<DMKResourceRequest> requests)
	{
		resourceRequests = std::move(requests);
	}

	DMKResourceRequest DMKAnimatedModelEntity::getResourceRequest(I64 index)
	{
		return resourceRequests[index];
	}

	ARRAY<DMKResourceRequest> DMKAnimatedModelEntity::getResourceRequests() const
	{
		return resourceRequests;
	}
}
