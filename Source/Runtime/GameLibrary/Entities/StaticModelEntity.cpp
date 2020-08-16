// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "StaticModelEntity.h"

namespace Dynamik
{
	void DMKStaticModelEntity::addShaderModule(const DMKShaderModule& sModule)
	{
		shaders.pushBack(sModule);
	}

	void DMKStaticModelEntity::setShaderModules(ARRAY<DMKShaderModule> sModules)
	{
		shaders = std::move(sModules);
	}

	DMKShaderModule* DMKStaticModelEntity::getShaderModule(I32 index)
	{
		return Cast<DMKShaderModule*>(shaders.location(index));
	}

	ARRAY<DMKShaderModule> DMKStaticModelEntity::getShaders()
	{
		return shaders;
	}

	void DMKStaticModelEntity::addResourceRequest(const DMKResourceRequest& request)
	{
		resourceRequests.pushBack(request);
	}

	void DMKStaticModelEntity::setResourceRequests(ARRAY<DMKResourceRequest> requests)
	{
		resourceRequests = std::move(requests);
	}

	DMKResourceRequest DMKStaticModelEntity::getResourceRequest(I64 index)
	{
		return resourceRequests[index];
	}

	ARRAY<DMKResourceRequest> DMKStaticModelEntity::getResourceRequests() const
	{
		return resourceRequests;
	}
}
