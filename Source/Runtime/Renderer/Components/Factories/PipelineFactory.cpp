#include "dmkafx.h"
#include "PipelineFactory.h"

namespace Dynamik
{
	void DMKPipelineFactory::setDefaults(DMKRenderingAPI api, RCoreObject* pCoreObject)
	{
		myRenderingAPI = api;
		myCoreObject = pCoreObject;
	}

	RPipelineObject* DMKPipelineFactory::createGraphicsPipeline(RPipelineCreateInfo createInfo)
	{
		switch (myRenderingAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			break;
		}

		return nullptr;
	}

	RPipelineObject* DMKPipelineFactory::createComputePipeline(RPipelineCreateInfo createInfo)
	{
		switch (myRenderingAPI)
		{
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
			break;
		case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
			break;
		default:
			break;
		}
		
		return nullptr;
	}
}
