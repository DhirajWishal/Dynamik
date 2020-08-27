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

#include "Core/Objects/Resources/ShaderModule.h"

class DMK_API RCoreObject;
class DMK_API RSwapChain;
class DMK_API RRenderTarget;
class DMK_API RTexture;

/*
 Renderer Pipeline Resource
 In Vulkan, this translates to Descriptor Sets.
*/
struct DMK_API RPipelineResource {
	/*
	 Update Render Resource.
	*/
	virtual void update(RCoreObject* pCoreObject, ARRAY<RBuffer*> pBuffers, ARRAY<RTexture*> pTextures) = 0;
};

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

	/* Pipeline Cache */
	VPTR* pPipelineCache = { nullptr };

	/* Render Resource Count */
	UI64 resourceCount = 0;

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

	virtual void initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, DMKViewport viewport) = 0;
	virtual void reCreate(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	virtual void createPipelineCache(RCoreObject* pCoreObject, UI64 byteSize, VPTR pData) = 0;
	virtual ARRAY<RPipelineResource*> allocateResources(RCoreObject* pCoreObject) = 0;

	RPipelineSpecification mySpecification = {};
	RPipelineUsage myUsage = RPipelineUsage::PIPELINE_USAGE_GRAPHICS;

public:		/* Constant Block */
	struct DMK_API PConstantBlock {
		PConstantBlock() = default;
		PConstantBlock(VPTR data, UI64 size, DMKShaderLocation location, UI64 offset)
			: data(data), byteSize(size), location(location), offset(offset) {}
		~PConstantBlock() = default;

		VPTR data = nullptr;
		UI64 byteSize = 0;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT;
		UI64 offset = 0;
	};

	DMK_FORCEINLINE virtual void submitConstantData(VPTR data, UI64 blockIndex)
	{
		if (constantBlocks.size())
			constantBlocks[blockIndex].data = data;
	}

	ARRAY<PConstantBlock> constantBlocks;

public:		/* Resource Check */
	B1 isResourceAvailable = false;
};

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H
