// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RRenderPass.h"

namespace Dynamik
{
	RSubpassAttachment RSubpassAttachment::createSwapChain(RSwapChain* pSwapChain)
	{
		RSubpassAttachment attachment = {};
		attachment.subpass = RSubPasses::SUBPASSES_SWAPCHAIN;
		attachment.samples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
		attachment.format = pSwapChain->format;
		attachment.loadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.storeOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
		attachment.finalLayout = RImageLayout::IMAGE_LAYOUT_PRESENT_SRC;

		return attachment;
	}

	RSubpassAttachment RSubpassAttachment::createDepth(RCoreObject* pCoreObject)
	{
		RSubpassAttachment attachment = {};
		attachment.subpass = RSubPasses::SUBPASSES_DEPTH;
		attachment.samples = pCoreObject->sampleCount;
		attachment.format = pCoreObject->getDepthFormat();
		attachment.loadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_CLEAR;
		attachment.storeOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
		attachment.finalLayout = RImageLayout::IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT;

		return attachment;
	}

	RSubpassAttachment RSubpassAttachment::createColor(DMKFormat format, DMKSampleCount samples)
	{
		RSubpassAttachment attachment = {};
		attachment.subpass = RSubPasses::SUBPASSES_COLOR;
		attachment.samples = samples;
		attachment.format = format;
		attachment.loadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_CLEAR;
		attachment.storeOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = RSubpassAttachmentLoadOp::SUBPASS_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = RSubpassAttachmentStoreOp::SUBPASS_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = RImageLayout::IMAGE_LAYOUT_UNDEFINED;
		attachment.finalLayout = RImageLayout::IMAGE_LAYOUT_PRESENT_SRC;

		return attachment;
	}
}
