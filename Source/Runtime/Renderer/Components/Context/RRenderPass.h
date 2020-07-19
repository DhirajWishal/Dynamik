// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_PASS_H
#define _DYNAMIK_RENDERER_RENDER_PASS_H

#include "RSwapChain.h"
#include "../ContextTypeDefs.h"
#include "../PrimitiveTypeDefs.h"

namespace Dynamik
{
	class DMK_API RCoreObject;
	class DMK_API RSwapChain;

	/* Subpasses */
	enum class DMK_API RSubPasses {
		SUBPASSES_SWAPCHAIN,
		SUBPASSES_DEPTH,
		SUBPASSES_COLOR,
		SUBPASSES_OVERLAY,
	};

	/* Subpass Dependency */
	struct DMK_API RSubpassDependency {
		RSubpassDependency(
			UI32 srcSubpassIndex = (~0U),
			UI32 dstSubpassIndex = 0,
			RPipelineStage srcPipelineStage = RPipelineStage::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT,
			RPipelineStage dstPipelineStage = RPipelineStage::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT,
			RMemoryAccessType srcMemoryAccessType = Cast<RMemoryAccessType>(0),
			RMemoryAccessType dstMemoryAccessType = Cast<RMemoryAccessType>(MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_READ | MEMORY_ACCESS_TYPE_COLOR_ATTACHMENT_WRITE),
			RPipelineDependency pipelineDependency = Cast<RPipelineDependency>(0)
		) :
			srcSubpassIndex(srcSubpassIndex),
			dstSubpassIndex(dstSubpassIndex),
			srcPipelineStage(srcPipelineStage),
			dstPipelineStage(dstPipelineStage),
			srcMemoryAccessType(srcMemoryAccessType),
			dstMemoryAccessType(dstMemoryAccessType),
			pipelineDependency(pipelineDependency) {}
		~RSubpassDependency() {}

		UI32 srcSubpassIndex = 0;
		UI32 dstSubpassIndex = 0;
		RPipelineStage srcPipelineStage;
		RPipelineStage dstPipelineStage;
		RMemoryAccessType srcMemoryAccessType;
		RMemoryAccessType dstMemoryAccessType;
		RPipelineDependency pipelineDependency;
	};

	/*
	 Renderer Render Pass
	*/
	class DMK_API RRenderPass {
	public:
		RRenderPass() {}
		RRenderPass(ARRAY<RSubPasses> aSubPasses) : subPasses(aSubPasses) {}
		virtual ~RRenderPass() {}

		virtual void initialize(RCoreObject* pCoreObject, ARRAY<RSubPasses> aSubPasses, ARRAY<RSubpassDependency> dependencies, RSwapChain* pSwapChain, DMKFormat overrideFormat = DMKFormat::DMK_FORMAT_UNDEFINED) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		ARRAY<RSubPasses> subPasses;
	};
}

#endif // !_DYNAMIK_RENDERER_RENDER_PASS_H
