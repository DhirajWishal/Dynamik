// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "PipelineFactory.h"

void DMKPipelineFactory::setDefaults(DMKRenderingAPI api, RCoreObject* pCoreObject)
{
	myRenderingAPI = api;
	myCoreObject = pCoreObject;
}

RPipelineObject* DMKPipelineFactory::createGraphicsPipeline(RPipelineSpecification createInfo)
{
	switch (myRenderingAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}

RPipelineObject* DMKPipelineFactory::createComputePipeline(RPipelineSpecification createInfo)
{
	switch (myRenderingAPI)
	{
	case DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
		break;
	case DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
		break;
	default:
		break;
	}

	return nullptr;
}
