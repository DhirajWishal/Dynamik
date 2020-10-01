// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_RENDER_PASS_H
#define _DYNAMIK_RENDERER_RENDER_PASS_H

#include "RSwapChain.h"
#include "../ContextTypeDefs.h"
#include "../PrimitiveTypeDefs.h"

class DMK_API RCoreObject;
class DMK_API RSwapChain;

/* Subpasses */
enum class DMK_API RSubPasses {
	SUBPASSES_UNDEFINED,
	SUBPASSES_SWAPCHAIN,
	SUBPASSES_DEPTH,
	SUBPASSES_COLOR,
	SUBPASSES_OVERLAY,
};

/* Subpass Attachment */
struct DMK_API RSubpassAttachment {
	RSubPasses subpass;
	DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
	DMKSampleCount samples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
	RSubpassAttachmentLoadOp loadOp;
	RSubpassAttachmentStoreOp storeOp;
	RSubpassAttachmentLoadOp stencilLoadOp;
	RSubpassAttachmentStoreOp stencilStoreOp;
	RImageLayout initialLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
	RImageLayout finalLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;

	static RSubpassAttachment createSwapChain(RSwapChain* pSwapChain);
	static RSubpassAttachment createDepth(RCoreObject* pCoreObject);
	static RSubpassAttachment createColor(DMKFormat format, DMKSampleCount samples);
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
	RRenderPass(std::vector<RSubpassAttachment> aSubPasses) : subPasses(aSubPasses) {}
	virtual ~RRenderPass() {}

	virtual void initialize(RCoreObject* pCoreObject, std::vector<RSubpassAttachment> aSubPasses, std::vector<RSubpassDependency> dependencies, RSwapChain* pSwapChain, DMKFormat overrideFormat = DMKFormat::DMK_FORMAT_UNDEFINED) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	std::vector<RSubpassAttachment> subPasses;
};

#endif // !_DYNAMIK_RENDERER_RENDER_PASS_H
