// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_PIPELINE_OBJECT_H
#define _DYNAMIK_RENDERER_PIPELINE_OBJECT_H

#include "RCoreObject.h"
#include "PipelineTypeDefs.h"
#include "RRenderTarget.h"
#include "Primitives/RTexture.h"
#include "Primitives/RBuffer.h"

#include "Core/Objects/Resource/ShaderModule.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RSwapChain;
	class DMK_API RTexture;

	/* Renderer Pipeline Usage */
	enum class DMK_API RPipelineUsage {
		PIPELINE_USAGE_GRAPHICS,
		PIPELINE_USAGE_COMPUTE,
	};

	/*
	 Renderer Pipeline Create Info
	*/
	struct DMK_API RPipelineSpecification {
		ARRAY<DMKShaderModule> shaders;

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

		virtual void initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain) = 0;
		virtual void reCreate(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, RSwapChain* pSwapChain) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		virtual void initializeResources(RCoreObject* pCoreObject, ARRAY<RBuffer*> pBuffers, ARRAY<RTexture*> pTextures) = 0;
	
		RPipelineSpecification mySpecification = {};
		RPipelineUsage myUsage = RPipelineUsage::PIPELINE_USAGE_GRAPHICS;
		B1 isResourceAvailable = false;
	};
}

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H
