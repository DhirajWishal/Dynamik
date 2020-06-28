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
#include "RRenderTarget.h"

#include "Core/Object/Resource/ShaderModule.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RSwapChain;

	/* Renderer Pipeline Usage */
	enum class DMK_API RPipelineUsage {
		PIPELINE_USAGE_GRAPHICS,
		PIPELINE_USAGE_COMPUTE,
	};

	/*
	 Renderer Pipeline Create Info
	*/
	struct DMK_API RPipelineCreateInfo {
		ARRAY<DMKShaderModule> shaders;
		RRenderTarget* pRenderTarget = nullptr;
		RSwapChain* pSwapChain = nullptr;

		/* Primitive Assembly */
		RPipelinePrimitiveAssemblyInfo primitiveAssemblyInfo;

		/* Tessellation Control */
		RPipelineTessellationStateControlInfo tessellationStateControlInfo;

		/* Scissor */
		ARRAY<RPipelineScissorInfo> scissorInfos;

		/* Rasterizer */
		RPipelineRasterizerInfo rasterizerInfo;

		/* Multi Sampling */
		RPipelineMultiSamplingInfo multiSamplingInfo;

		/* Depth Stencil */
		RPipelineDepthStencilInfo depthStencilInfo;

		/* Color Blend */
		RPipelineColorBlendInfo colorBlendInfo;

		/* Dynamic State */
		ARRAY<RDynamicState> dynamicStates;
	};

	/*
	 Renderer Pipeline Object
	 Pipeline objects consists all the necessary data to be passed to the shader (Vertex inputs, resource 
	 descriptors).
	*/
	class DMK_API RPipelineObject {
	public:
		RPipelineObject() {}
		virtual ~RPipelineObject() {}

		virtual void initialize(RCoreObject* pCoreObject, RPipelineCreateInfo createInfo, RPipelineUsage usage) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H
