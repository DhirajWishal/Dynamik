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
	virtual void update(RCoreObject* pCoreObject, std::vector<RBuffer*> pBuffers, std::vector<RTexture*> pTextures) = 0;
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
	std::vector<DMKShaderModule> shaders;

	/* Pipeline Cache */
	void** pPipelineCache = { nullptr };

	/* Render Resource Count */
	UI64 resourceCount = 0;

	/* Primitive Assembly */
	RPipelinePrimitiveAssemblyInfo primitiveAssemblyInfo;

	/* Tessellation Control */
	RPipelineTessellationStateControlInfo tessellationStateControlInfo;

	/* Scissor */
	std::vector<RPipelineScissorInfo> scissorInfos;

	/* Rasterizer */
	RPipelineRasterizerInfo rasterizerInfo;

	/* Multi Sampling */
	RPipelineMultiSamplingInfo multiSamplingInfo;

	/* Depth Stencil */
	RPipelineDepthStencilInfo depthStencilInfo;

	/* Color Blend */
	RPipelineColorBlendInfo colorBlendInfo;

	/* Dynamic State */
	std::vector<RDynamicState> dynamicStates;
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

	/*
	 For graphics pipeline creation. 
	*/
	virtual void initialize(RCoreObject* pCoreObject, RPipelineSpecification createInfo, RPipelineUsage usage, RRenderTarget* pRenderTarget, DMKViewport viewport) {}
	
	/*
	 For ray tracing pipeline creation.
	*/
	virtual void initialize(RCoreObject* pCoreObject) {}
	virtual void reCreate(RCoreObject* pCoreObject, RRenderTarget* pRenderTarget, DMKViewport viewport) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	virtual void createPipelineCache(RCoreObject* pCoreObject, UI64 byteSize, void* pData) = 0;
	virtual std::vector<RPipelineResource*> allocateResources(RCoreObject* pCoreObject) = 0;
	virtual void deallocateResources(std::vector<RPipelineResource*> resources) = 0;

	RPipelineSpecification mySpecification = {};
	RPipelineUsage myUsage = RPipelineUsage::PIPELINE_USAGE_GRAPHICS;

public:		/* Constant Block */
	struct DMK_API PConstantBlock {
		PConstantBlock() = default;
		PConstantBlock(void* data, UI64 size, DMKShaderLocation location, UI64 offset)
			: data(data), byteSize(size), location(location), offset(offset) {}
		~PConstantBlock() = default;

		void* data = nullptr;
		UI64 byteSize = 0;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT;
		UI64 offset = 0;
	};

	DMK_FORCEINLINE virtual void submitConstantData(void* data, UI64 blockIndex)
	{
		if (constantBlocks.size())
			constantBlocks[blockIndex].data = data;
	}

	std::vector<PConstantBlock> constantBlocks;

public:		/* Resource Check */
	bool isResourceAvailable = false;
};

#endif // !_DYNAMIK_RENDERER_PIPELINE_OBJECT_H