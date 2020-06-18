// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PIPELINE_FACTORY_H
#define _DYNAMIK_PIPELINE_FACTORY_H

/*
 Author:	Dhiraj Wishal
 Date:		17/06/2020
*/
#include "../RPipelineObject.h"

namespace Dynamik
{
	/*
	 Dynamik Pipeline Factory
	*/
	class DMK_API DMKPipelineFactory {
	public:
		DMKPipelineFactory() {}
		~DMKPipelineFactory() {}

		void setDefaults(DMKRenderingAPI api, POINTER<RCoreObject> pCoreObject);

		POINTER<RPipelineObject> createGraphicsPipeline(RPipelineCreateInfo createInfo);
		POINTER<RPipelineObject> createComputePipeline(RPipelineCreateInfo createInfo);

	private:
		DMKRenderingAPI myRenderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
		POINTER<RCoreObject> myCoreObject;
	};
}

#endif // !_DYNAMIK_PIPELINE_FACTORY_H
