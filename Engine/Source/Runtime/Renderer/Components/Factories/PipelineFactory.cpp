#include "dmkafx.h"
#include "PipelineFactory.h"

namespace Dynamik
{
	void DMKPipelineFactory::setDefaults(DMKRenderingAPI api, POINTER<RCoreObject> pCoreObject)
	{
		myRenderingAPI = api;
		myCoreObject = pCoreObject;
	}

	POINTER<RPipelineObject> DMKPipelineFactory::createGraphicsPipeline(RPipelineCreateInfo createInfo)
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

		return POINTER<RPipelineObject>();
	}

	POINTER<RPipelineObject> DMKPipelineFactory::createComputePipeline(RPipelineCreateInfo createInfo)
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
		
		return POINTER<RPipelineObject>();
	}
}
