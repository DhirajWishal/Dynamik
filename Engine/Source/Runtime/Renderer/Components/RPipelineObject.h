// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_PIPELINE_OBJECT_H
#define _DYNAMIK_RENDERER_PIPELINE_OBJECT_H

/*
 Author:	Dhiraj Wishal
 Date:		17/06/2020
*/
#include "RCoreObject.h"
#include "PipelineTypeDefs.h"

namespace Dynamik
{
	/* Renderer Pipeline Usage */
	enum class DMK_API RPipelineUsage {
		PIPELINE_USAGE_GRAPHICS,
		PIPELINE_USAGE_COMPUTE,
	};

	/*
	 Renderer Pipeline Create Info
	*/
	struct DMK_API RPipelineCreateInfo {

	};

	/*
	 Renderer Pipeline Object
	*/
	class DMK_API RPipelineObject {
	public:
		RPipelineObject() {}
		virtual ~RPipelineObject() {}
	};
}

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H
